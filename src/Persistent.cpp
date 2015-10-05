#include "main.hpp"

void
Map::Save(TCODZip& zip) {
	zip.putInt(seed);

	for(int i = 0; i < width * height; ++i) {
		zip.putInt(tiles[i].explored);
	}
}

void
Map::Load(TCODZip& zip) {
    seed = zip.getInt();

    Init(false);

    for(int i = 0; i < width * height; ++i) {
        tiles[i].explored = (zip.getInt() != 0);
    }
}

void
Actor::Save(TCODZip& zip) {
	zip.putInt(x);
	zip.putInt(y);

	zip.putInt(code);
	zip.putColor(&color);

	zip.putString(name);

	zip.putInt(blocks);
	zip.putInt(fovOnly);

	zip.putInt(destructible != nullptr);
	zip.putInt(ai != nullptr);
	zip.putInt(pickable != nullptr);
	zip.putInt(container != nullptr);

	if(destructible) {
		destructible->Save(zip);
	}

	if(ai) {
		ai->Save(zip);
	}

	if(pickable) {
		pickable->Save(zip);
	}

	if(container) {
		container->Save(zip);
	}
}

void
Actor::Load(TCODZip& zip) {
    x = zip.getInt();
    y = zip.getInt();

    code = zip.getInt();
    color = zip.getColor();

    name = _strdup(zip.getString());

	blocks = zip.getInt() != 0;
	fovOnly = zip.getInt() != 0;

	bool hasDestructible = (zip.getInt() != 0);
	bool hasAi = (zip.getInt() != 0);
	bool hasPickable = (zip.getInt() != 0);
	bool hasContainer = (zip.getInt() != 0);

    if(hasDestructible) {
        destructible = Destructible::Create(zip);
    }

    if(hasAi) {
        ai = Ai::Create(zip);
    }

    if(hasPickable) {
        pickable = Pickable::Create(zip);
    }

    if(hasContainer) {
        container = new Container(0);
        container->Load(zip);
    }
}

void
Container::Save(TCODZip& zip) {
	zip.putInt(size);
	zip.putInt(inventory.size());

	for(Actor** it = inventory.begin(); it != inventory.end(); ++it) {
		(*it)->Save(zip);
	}
}

void
Container::Load(TCODZip& zip) {
    size = zip.getInt();
    int numberOfallActors = zip.getInt();

    while(numberOfallActors > 0) {
        Actor* actor = new Actor(0, 0);
        actor->Load(zip);

        inventory.push(actor);

        numberOfallActors--;
    }
}

void
Destructible::Save(TCODZip& zip) {
	zip.putInt(maxHP);
	zip.putInt(curHP);
	zip.putFloat(defense);
}

void
Destructible::Load(TCODZip& zip) {
    maxHP = zip.getInt();
    curHP = zip.getInt();
    defense = zip.getFloat();
}

void
PlayerDestructible::Save(TCODZip& zip) {
    zip.putInt(DESTRUCTIBLE_TYPE_PLAYER);

    Destructible::Save(zip);
}

void
OrcDestructible::Save(TCODZip& zip) {
	zip.putInt(DESTRUCTIBLE_TYPE_ORC);

    Destructible::Save(zip);
}

Destructible*
Destructible::Create(TCODZip& zip) {
    destructible_type type = (destructible_type)zip.getInt();
    Destructible* destructible = nullptr;

    switch(type) {
		case DESTRUCTIBLE_TYPE_ORC:
		{
			destructible = new OrcDestructible(0, 0);
		} break;

		case DESTRUCTIBLE_TYPE_PLAYER:
		{
			destructible = new PlayerDestructible(0, 0);
		} break;
	}

    destructible->Load(zip);

    return(destructible);
}

void
OrcAi::Save(TCODZip& zip) {
	zip.putInt(AI_TYPE_ORC);
}

void
OrcAi::Load(TCODZip& zip) {
}

void
OrcAiBegForMercy::Save(TCODZip& zip) {
	zip.putInt(AI_TYPE_ORC_BEG_FOR_MERCY);

	oldAi->Save(zip);
}

void
OrcAiBegForMercy::Load(TCODZip& zip) {
    oldAi = Ai::Create(zip);
}

void
PlayerAi::Save(TCODZip& zip) {
	zip.putInt(AI_TYPE_PLAYER);
}

void
PlayerAi::Load(TCODZip& zip) {
}

Ai*
Ai::Create(TCODZip& zip) {
    ai_type type = (ai_type)zip.getInt();
    Ai* ai = nullptr;

    switch(type) {
		case AI_TYPE_PLAYER:
		{
			ai = new PlayerAi();
		} break;

		case AI_TYPE_ORC:
		{
			ai = new OrcAi();
		} break;

		case AI_TYPE_ORC_BEG_FOR_MERCY:
		{
			ai = new OrcAiBegForMercy(nullptr);
		} break;
    }

    ai->Load(zip);

    return(ai);
}

void
Healer::Save(TCODZip& zip) {
	zip.putInt(PICKABLE_TYPE_HEALER);
	zip.putInt(amount);
}

void
Healer::Load(TCODZip& zip) {
    amount = zip.getInt();
}

void
LightningBolt::Save(TCODZip& zip) {
	zip.putInt(PICKABLE_TYPE_LIGHTNING_BOLT);
	zip.putInt(range);
	zip.putInt(damage);
}

void
LightningBolt::Load(TCODZip& zip) {
    range = zip.getInt();
    damage = zip.getInt();
}

void
Fireball::Save(TCODZip& zip) {
	zip.putInt(PICKABLE_TYPE_FIREBALL);
    zip.putInt(range);
    zip.putInt(damage);
}

Pickable*
Pickable::Create(TCODZip& zip) {
    pickable_type type = (pickable_type)zip.getInt();
    Pickable* pickable = nullptr;

    switch(type) {
		case PICKABLE_TYPE_HEALER:
		{
			pickable = new Healer(0);
		} break;

		case PICKABLE_TYPE_LIGHTNING_BOLT:
		{
			pickable = new LightningBolt(0, 0);
		} break;

		case PICKABLE_TYPE_FIREBALL:
		{
			pickable = new Fireball(0, 0);
		} break;
    }

    pickable->Load(zip);

    return(pickable);
}

void
Gui::Save(TCODZip& zip) {
	zip.putInt(log.size());

	for(message** it = log.begin(); it != log.end(); ++it) {
		zip.putString((*it)->text);
		zip.putColor(&(*it)->color);
	}
}

void
Gui::Load(TCODZip& zip) {
    int numberOfMessages = zip.getInt();

    while(numberOfMessages > 0) {
        char* text = (char*)zip.getString();
        TCODColor color = zip.getColor();

        Message(color, text);

        numberOfMessages--;
    }
}

int SAVEGAME_VERSION = 0x0001;

void
Engine::Save() {
	if(player->destructible->IsDead()) {
		TCODSystem::deleteFile("game.sav");
	}
	else {
		TCODZip zip;

		zip.putInt(SAVEGAME_VERSION);

		zip.putInt(map->width);
		zip.putInt(map->height);
		map->Save(zip);

		player->Save(zip);

		zip.putInt(allActors.size() - 2);

		for(Actor** it = allActors.begin(); it != allActors.end(); ++it) {
			if(*it != player) {
				(*it)->Save(zip);
			}
		}

		gui->Save(zip);

		zip.saveToFile("game.sav");
	}
}

void
Engine::Load(bool pause) {
	bool shouldLeave = false;

    TCODZip zip;

	while(!shouldLeave) {
		TCODConsole::root->clear();
		TCODConsole::setFade(255, TCODColor::black);

		e->gui->menu.Clear();
		e->gui->menu.AddItem(Menu::MIC_NEW_GAME, "New Game");

		if(TCODSystem::fileExists("game.sav")) {
			zip.loadFromFile("game.sav");

			int version = zip.getInt();

			if(version == SAVEGAME_VERSION) {
				e->gui->menu.AddItem(Menu::MIC_CONTINUE, "Continue");
			}
		}

		e->gui->menu.AddItem(Menu::MIC_EXIT, "Exit");

		Menu::menu_item_code menuItem = e->gui->menu.Pick(true, 2, 2);

		if(menuItem == Menu::MIC_EXIT || menuItem == Menu::MIC_NONE) {
			e->leaveGame = true;
			shouldLeave = true;
		}
		else if(menuItem == Menu::MIC_NEW_GAME) {
			shouldLeave = true;
		}
		else if(menuItem == Menu::MIC_CONTINUE) {
			shouldLeave = true;

			e->Close();

			int width = zip.getInt();
			int height = zip.getInt();
			map = new Map(width, height);
			map->Load(zip);

			player = new Actor(0, 0);
			e->AddActorToArena(player);
			player->Load(zip);

			int numberOfallActors = zip.getInt();

			while(numberOfallActors > 0) {
				Actor* actor = new Actor(0, 0);
				actor->Load(zip);

				e->AddActorToWorld(actor);

				numberOfallActors--;
			}

			gui->Load(zip);

			gameStatus = GAME_STATUS_MAIN;
		}
	}
}

void
Date::Save(TCODZip& zip) {
	//faz
	//zip.putFloat(maxHP);
	//zip.putFloat(curHP);
	//zip.putFloat(defense);
}

void
Date::Load(TCODZip& zip) {
	//faz
    //maxHP = zip.getFloat();
    //curHP = zip.getFloat();
    //defense = zip.getFloat();
}