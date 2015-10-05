#include <stdio.h>
#include <math.h>

#include "main.hpp"

Ai::Ai(bool canDoActions, bool alreadyTalked) :
	canDoActions(canDoActions),
	alreadyTalked(alreadyTalked),
	beggingForMercy(false)
{
}

OrcAi::OrcAi(bool canDoActions, bool alreadyTalked) :
	Ai(canDoActions, alreadyTalked)
{
}

void
OrcAi::Update(Actor* owner) {
    if(owner->destructible && owner->destructible->IsDead()) {
        return;
    }

    if(owner->traits) {
        owner->traits->HandleTraits(owner);
    }

	MoveOrAttack(owner, e->player->x, e->player->y);
    alreadyTalked = false;
}

void
OrcAi::MoveOrAttack(Actor* owner, int targetX, int targetY) {
    int dx = targetX - owner->x;
    int dy = targetY - owner->y;

    int stepdx = (dx > 0 ? 1 : -1);
    int stepdy = (dy > 0 ? 1 : -1);

    float distance = FastSqrtf((float)(dx * dx + dy * dy));

    if(distance >= 2) {
        dx = (int)(FastRoundf(dx / distance));
        dy = (int)(round(dy / distance));

        if(e->map->CanWalk(owner->x + dx, owner->y + dy)) {
            owner->x += dx;
            owner->y += dy;
        }
        else if(e->map->CanWalk(owner->x + stepdx, owner->y)) {
            owner->x += stepdx;
        }
        else if(e->map->CanWalk(owner->x, owner->y + stepdy)) {
            owner->y += stepdy;
        }
    }
    else if(owner->leftHandWeapon) {
		//TODO: For now.
        Attack(owner, owner->leftHandWeapon, e->player, GetRandomTargetPart(), ATTACK_TYPE_SLASH);
    }
}

OrcAiBegForMercy::OrcAiBegForMercy(Ai* oldAi) :
    OrcAi(false, false),
    oldAi(oldAi),
    canBehave(0)
{
	beggingForMercy = true;
}

void
OrcAiBegForMercy::Update(Actor* owner) {
    if(!owner->destructible || !owner->destructible->IsDead()) {
        canBehave++;

        if(canBehave >= UPDATES_UNTIL_BEHAVIOUR_FEAR_MERCY) {
            int randomMessageIndex = RandomNumberInRange(0, ArrayCount(BEHAVIOUR_FEAR_MERCY_M_TEST) - 1);
            e->gui->Message(TCODColor::white, "%s: %s",
                                owner->name, BEHAVIOUR_FEAR_MERCY_M_TEST[randomMessageIndex]);

            canBehave = 0;
        }
    }

    if(owner->traits) {
        owner->traits->HandleTraits(owner);
    }   

    alreadyTalked = false;
}

PlayerAi::PlayerAi() :
	Ai(true, false)
{
}

void
PlayerAi::Update(Actor* owner) {
    if(owner->destructible && owner->destructible->IsDead()) {
        return;
    }

    int dx = 0;
    int dy = 0;

    switch(e->lastKey.vk) {
		case TCODK_UP:
		case TCODK_KP8:
		{
			dy = -1;
		} break;

		case TCODK_DOWN:
		case TCODK_KP2:
		{
			dy = 1;
		} break;

		case TCODK_LEFT:
		case TCODK_KP4:
		{
			dx = -1;
		} break;

		case TCODK_RIGHT:
		case TCODK_KP6:
		{
			dx = 1;
		} break;

		case TCODK_KP7:
		{
			dx = -1;
			dy = -1;
		} break;

		case TCODK_KP9:
		{
			dx = 1;
			dy = -1;
		} break;

		case TCODK_KP1:
		{
			dx = -1;
			dy = 1;
		} break;

		case TCODK_KP3:
		{
			dx = 1;
			dy = 1;
		} break;

		case TCODK_KP5:
		{
			if(e->inSandbox) {
				e->gameStatus = Engine::GAME_STATUS_ARENA_SANDBOX_NEW_TURN;
			}
			else {
				e->gameStatus = Engine::GAME_STATUS_ARENA_NEW_TURN;
			}
		} break;

		case TCODK_CHAR:
		{
			HandleActionKey(owner, e->lastKey.c);
		} break;

		default:
		{
		} break;
	}
	
	if(e->mouse.lbutton_pressed) {
		if(e->map->IsInFov(e->mouse.cx, e->mouse.cy)) {
			DisplayStats(owner);
		}
	}

	if(dx != 0 || dy != 0) {
		if(e->inSandbox) {
			e->gameStatus = Engine::GAME_STATUS_ARENA_SANDBOX_NEW_TURN;
		}
		else {
			e->gameStatus = Engine::GAME_STATUS_ARENA_NEW_TURN;
		}

		if(MoveOrAttack(owner, owner->x + dx, owner->y + dy)) {
			e->map->ComputeFov();
		}
	}
}

bool
PlayerAi::MoveOrAttack(Actor* owner, int targetX, int targetY) {
	if(e->map->IsWall(targetX, targetY)) {
		return(false);
	}

    for(Actor** it = e->arenaActors.begin(); it != e->arenaActors.end(); ++it) {
        Actor* actor = *it;

        if(actor->destructible && !actor->destructible->IsDead() &&
       	   actor->x == targetX && actor->y == targetY)
		{
			Attack(owner, owner->leftHandWeapon, actor, GetRandomTargetPart(), ATTACK_TYPE_SLASH);

            return(false);
        }
    }

    //Look for corpses or items.
    for(Actor** it = e->arenaActors.begin(); it != e->arenaActors.end(); ++it) {
        Actor* actor = *it;

        bool corpseOrItem = ((actor->destructible && actor->destructible->IsDead()) || actor->pickable);

        if(corpseOrItem && actor->x == targetX && actor->y == targetY) {
            e->gui->Message(TCODColor::lightGrey, "There's a %s here.", actor->name);
        }
    }

    owner->x = targetX;
    owner->y = targetY;

    return(true);
}

//TODO: Put all usable keys into a class that handles the input and configures it.
void
PlayerAi::HandleActionKey(Actor* owner, char ascii) {
    switch(ascii) {
		//Drop an item.
		case 'd':
		{
			Actor* actor = ChooseFromInventory(owner);

			if(actor) {
				actor->pickable->Drop(actor, owner);

				if(e->inSandbox) {
					e->gameStatus = Engine::GAME_STATUS_ARENA_SANDBOX_NEW_TURN;
				}
				else {
					e->gameStatus = Engine::GAME_STATUS_ARENA_NEW_TURN;
				}
			}
		} break;

		//Pickup item.
		case 'g':
		{
			bool found = false;

			for(Actor** it = e->arenaActors.begin(); it != e->arenaActors.end(); ++it) {
				Actor* actor = *it;

				if(actor->pickable && actor->x == owner->x && actor->y == owner->y) {
					if(actor->pickable->Pick(actor, owner)) {
						found = true;
						e->gui->Message(TCODColor::lightGrey, "You pick the %s.", actor->name);

						break;
					}
					else if(!found) {
						found = true;
						e->gui->Message(TCODColor::red, "Your inventory is full.");
					}
				}
			}

			if(!found) {
				e->gui->Message(TCODColor::lightGrey, "There's nothing here that you can pick.");
			}

			if(e->inSandbox) {
				e->gameStatus = Engine::GAME_STATUS_ARENA_SANDBOX_NEW_TURN;
			}
			else {
				e->gameStatus = Engine::GAME_STATUS_ARENA_NEW_TURN;
			}
		} break;

		//Display inventory.
		case 'i':
		{
			Actor* actor = ChooseFromInventory(owner);

			if(actor) {
				actor->pickable->Use(actor, owner);

				if(e->inSandbox) {
					e->gameStatus = Engine::GAME_STATUS_ARENA_SANDBOX_NEW_TURN;
				}
				else {
					e->gameStatus = Engine::GAME_STATUS_ARENA_NEW_TURN;
				}
			}
		} break;
    }
}

Actor*
PlayerAi::ChooseFromInventory(Actor* owner) {
    TCODConsole* console = &GUI_CONSOLE_INVENTORY;

    console->setDefaultForeground(TCODColor(200, 180, 50));
    console->printFrame(0, 0, GUI_INVENTORY_WIDTH, GUI_INVENTORY_HEIGHT, true, TCOD_BKGND_DEFAULT, "Inventory");
    console->setDefaultForeground(TCODColor::white);

    int shortcut = 'a';
    int y = 2;

    for(Actor** it = owner->container->inventory.begin(); it != owner->container->inventory.end(); ++it) {
        Actor* actor = *it;

        console->print(2, y, "(%c) %s", shortcut, actor->name);

        y++;
        shortcut++;
    }

    TCODConsole::blit(console, 0, 0, GUI_INVENTORY_WIDTH, GUI_INVENTORY_HEIGHT, TCODConsole::root, 
                      e->screenWidth / 2 - GUI_INVENTORY_WIDTH / 2,
                      e->screenHeight / 2 - GUI_INVENTORY_HEIGHT / 2);
    TCODConsole::flush();

    TCOD_key_t key;
    TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL, true);

    if(key.vk == TCODK_CHAR) {
        int actorIndex = key.c - 'a';
        
        if(actorIndex >= 0 && actorIndex < owner->container->inventory.size()) {
            return(owner->container->inventory.get(actorIndex));
        }
    }

    return(nullptr);
}

//TODO: This method should not be in the ai, obviously!
void
PlayerAi::DisplayStats(Actor* owner) {
    TCODConsole* console = &GUI_CONSOLE_STATS;
    Actor* actor = nullptr;

    for(Actor** it = e->arenaActors.begin(); it != e->arenaActors.end(); ++it) {
        if((*it)->x == e->mouse.cx && (*it)->y == e->mouse.cy) {
            actor = *it;

			if(!actor->ai && !actor->destructible && !actor->leftHandWeapon) {
				actor = nullptr;

				break;
			}
        }
    }

	if(actor) {
		e->gui->PrintActor(actor, console, 2, 2, GUI_STATS_WIDTH, GUI_STATS_HEIGHT, actor->name);

		TCODConsole::blit(console, 0, 0, GUI_STATS_WIDTH, GUI_STATS_HEIGHT, TCODConsole::root,
			e->screenWidth / 2 - GUI_STATS_WIDTH / 2,
			e->screenHeight / 2 - GUI_STATS_HEIGHT / 2);
		TCODConsole::flush();

		TCOD_key_t key;
		TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL, true);
	}
}