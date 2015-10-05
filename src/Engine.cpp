#include <math.h>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include "main.hpp"

Engine::Engine(int screenWidth, int screenHeight) :
	gameStatus(GAME_STATUS_BOOTING),
	c(nullptr),
	runningTournament(nullptr), runningMatch(nullptr),
	gui(nullptr), map(nullptr), player(nullptr),
	fovRadius(200), fovRadiusSquared(fovRadius * fovRadius),
    screenWidth(screenWidth), screenHeight(screenHeight),
	inSandbox(false), leaveGame(false)
{
    TCODConsole::initRoot(screenWidth, screenHeight, "0.0.0.1 - Maximus", false);
}

Engine::~Engine() {
	Close();
}

void
Engine::Init() {
	c = new DODContent();
	gui = new Gui();
	map = new Map(screenWidth, screenHeight - 7);
	map->Init(true);

	player = CreateActorPlayer();
	player->x = (screenWidth / 2) - 5;
	player->y = (screenHeight / 2);

    AddActorToArena(player);

    int numberOfTours = RandomNumberInRange(2, 8);

    for(int n = 0; n < numberOfTours; ++n) {
		Tournament* tour = GenerateRandomTournament();

    	tours.push(tour);
	}

    gameStatus = GAME_STATUS_MAIN;
}

void
Engine::Close() {
    allActors.clearAndDelete();
    arenaActors.clear();
    deadActors.clear();

    tours.clearAndDelete();
    historyTours.clearAndDelete();

	if(gui) {
		delete gui;
		gui = nullptr;
	}
	if(map) {
		delete map;
		map = nullptr;
	}
	if(c) {
		delete c;
		c = nullptr;
	}

	fovRadius = 0;
	fovRadiusSquared = 0;

	screenWidth = 0;
	screenHeight = 0;

	inSandbox = 0;
	
	gameStatus = GAME_STATUS_EXIT;
}

void
Engine::Update() {
    TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS | TCOD_EVENT_MOUSE, &lastKey, &mouse);

	if(gameStatus == GAME_STATUS_MAIN) {
		MainScreen();
	}
	else if(gameStatus == GAME_STATUS_TOURNAMENT_MAIN) {
		TournamentMainScreen();
	}
	//Arena
	else if(gameStatus == GAME_STATUS_ARENA_STARTUP) {
		map->ComputeFov();
		gameStatus = GAME_STATUS_ARENA_IDLE;
	}
	else if(gameStatus == GAME_STATUS_ARENA_IDLE) {
	    player->Update();

	    if(gameStatus == GAME_STATUS_ARENA_NEW_TURN) {
	        for(Actor** it = arenaActors.begin(); it != arenaActors.end(); ++it) {
	            Actor* actor = *it;

	            if(actor != player) {
	                actor->Update();
	            }
	        }

			int matchStatus = CheckForEndOfRunningMatch();

	        if(matchStatus == -1) {
	        	gameStatus = GAME_STATUS_GAME_OVER;
	        }
			else if(matchStatus == 1) {
				ArenaMatchWonScreen();
			}
	    }

	    if(gameStatus == GAME_STATUS_ARENA_NEW_TURN) {
	    	gameStatus = GAME_STATUS_ARENA_IDLE;
		}
	}
	//Testing Arena
	else if(gameStatus == GAME_STATUS_ARENA_SANDBOX_STARTUP) {
		map->ComputeFov();
		gameStatus = GAME_STATUS_ARENA_SANDBOX_IDLE;
		inSandbox = true;
	}
	else if(gameStatus == GAME_STATUS_ARENA_SANDBOX_IDLE) {
		player->Update();
	    UpdateSandbox();

	    if(gameStatus == GAME_STATUS_ARENA_SANDBOX_NEW_TURN) {
	        for(Actor** it = arenaActors.begin(); it != arenaActors.end(); ++it) {
	            Actor* actor = *it;

	            if(actor != player) {
	                actor->Update();
	            }
	        }
	    }

	    if(gameStatus == GAME_STATUS_ARENA_SANDBOX_NEW_TURN) {
	    	gameStatus = GAME_STATUS_ARENA_SANDBOX_IDLE;
		}
	}
	else if(gameStatus == GAME_STATUS_GAME_OVER) {
		GameOverScreen();
	}
	else if(gameStatus == GAME_STATUS_EXIT) {
		e->leaveGame = true;
	}
}

void
Engine::UpdateSandbox() {
    switch(lastKey.vk) {
		case TCODK_CHAR:
		{
			switch(lastKey.c) {
				case 'q':
				{
					Actor* actor = CreateActorFullRandomOrc();

					if(actor) {
						actor->x = RandomNumberInRange(2, screenWidth - 2);
						actor->y = RandomNumberInRange(2, screenHeight - 2);
						AddActorToArena(actor);
					}
				} break;

				case 'w':
				{
					player->leftHandWeapon->durability = player->leftHandWeapon->maxDurability;
					player->headArmor->durability = player->headArmor->maxDurability;
					player->chestArmor->durability = player->chestArmor->maxDurability;
					player->legArmor->durability = player->legArmor->maxDurability;
					player->leftShoulderArmor->durability = player->leftShoulderArmor->maxDurability;
					player->rightShoulderArmor->durability = player->rightShoulderArmor->maxDurability;
					player->leftArmArmor->durability = player->leftArmArmor->maxDurability;
					player->rightArmArmor->durability = player->rightArmArmor->maxDurability;
					player->leftFootArmor->durability = player->leftFootArmor->maxDurability;
					player->rightFootArmor->durability = player->rightFootArmor->maxDurability;
				} break;
				case 'e':
				{
					player->destructible->curHP = player->destructible->maxHP;
				} break;
			}
		} break;

		default:
		{
		} break;
	}
}

void
Engine::MainScreen() {
	TCODConsole::root->clear();
	TCODConsole::setFade(255, TCODColor::black);

	gui->DisplayPlayerStatsMain();

	e->gui->menu.Clear();

	if(runningTournament) {
		e->gui->menu.AddItem(Menu::MIC_MS_ENTER_TOURNAMENT,
								 ToString("Enter: %s", runningTournament->name->fullName));
	}

	e->gui->menu.AddItem(Menu::MIC_MS_TOURNAMENTS, "View Tournaments");
	e->gui->menu.AddItem(Menu::MIC_MS_ARENA_TEST, "Arena Test");
	e->gui->menu.AddItem(Menu::MIC_EXIT, "Exit");

	Menu::menu_item_code menuItem = e->gui->menu.Pick(true, 2, 2);

	if(menuItem == Menu::MIC_EXIT) {
		gameStatus = GAME_STATUS_EXIT;
	}
	else if (menuItem == Menu::MIC_MS_ENTER_TOURNAMENT) {
		if(runningTournament) {
			gameStatus = GAME_STATUS_TOURNAMENT_MAIN;

			runningTournament->PopulateTournament(true);
		}
	}
	else if(menuItem == Menu::MIC_MS_TOURNAMENTS) {
		gui->DisplayTournamentsMain();
	}
	else if(menuItem == Menu::MIC_MS_ARENA_TEST) {
		allActors.remove(player);
		arenaActors.clear();
		AddActorToArena(player);
		e->gameStatus = GAME_STATUS_ARENA_SANDBOX_STARTUP;
	}
}

void
Engine::TournamentMainScreen() {
	int lastY;
	bool isTourRunning = true;

	do {
		TCODConsole::root->clear();
		TCODConsole::setFade(255, TCODColor::black);

		gui->menu.Clear();

		lastY = runningTournament->PrintTournamentCurrentStandings();

		if(player->code != runningTournament->nextMatch->contender1->code &&
		   player->code != runningTournament->nextMatch->contender2->code)
		{
			gui->menu.AddItem(Menu::MIC_MTS_SIMULATE, "Simulate");
		}
		else {
			gui->menu.AddItem(Menu::MIC_MTS_FIGHT, "Fight");
		}

		Menu::menu_item_code menuItem = e->gui->menu.Pick(true, 2, lastY + 4);

		if(menuItem == Menu::MIC_MTS_SIMULATE) {
			bool isLastMatch = runningTournament->SimulateMatch();
			isTourRunning = !isLastMatch;
		}
		else if(menuItem == Menu::MIC_MTS_FIGHT) {
			if(runningTournament->nextMatch) {
				if(runningTournament->nextMatch->contender1) {
					if(runningTournament->nextMatch->contender1->code != '@') {
						runningTournament->nextMatch->contender1->x = (e->screenWidth / 2) + 5;
						runningTournament->nextMatch->contender1->y = (e->screenHeight / 2);
						AddActorToArena(runningTournament->nextMatch->contender1);
					}
				}
				if(runningTournament->nextMatch->contender2) {
					if(runningTournament->nextMatch->contender2->code != '@') {
						runningTournament->nextMatch->contender2->x = (e->screenWidth / 2);
						runningTournament->nextMatch->contender2->y = (e->screenHeight / 2) - 5;
						AddActorToArena(runningTournament->nextMatch->contender2);
					}
				}
				if(runningTournament->nextMatch->contender3) {
					if(runningTournament->nextMatch->contender3->code != '@') {
						runningTournament->nextMatch->contender3->x = (e->screenWidth / 2);
						runningTournament->nextMatch->contender3->y = (e->screenHeight / 2) + 5;
						AddActorToArena(runningTournament->nextMatch->contender3);
					}
				}

				gameStatus = GAME_STATUS_ARENA_STARTUP;

				SetRunningMatch(runningTournament->nextMatch);

				//TODO: Ugly.
				return;
			}
		}
	} while(isTourRunning);

	TCODConsole::root->print(2, lastY + 8, "Winner: %s", runningTournament->first->name);
	TCODConsole::root->print(2, lastY + 10, "Press any key to continue...");

	TCODConsole::root->flush();

	TCOD_key_t key;
	TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL, false);

	gameStatus = GAME_STATUS_MAIN;

	StoreRunningTournament(runningTournament);
	runningTournament = nullptr;
}

void
Engine::ArenaMatchWonScreen() {
	TCODConsole::root->clear();
	TCODConsole::setFade(255, TCODColor::black);

	int lastY;

	lastY = gui->PrintArenaMatchWonScreen();

	e->gui->menu.Clear();
	e->gui->menu.AddItem(Menu::MIC_AMWS_BACK_TO_TOURNAMENT, "Back To Tournament");

	Menu::menu_item_code menuItem = e->gui->menu.Pick(true, 2, lastY + 2);

	if(menuItem == Menu::MIC_AMWS_BACK_TO_TOURNAMENT) {
		runningTournament->AdvanceMatch();
		runningMatch = nullptr;
		
		gameStatus = GAME_STATUS_TOURNAMENT_MAIN;
	}
}

void
Engine::GameOverScreen() {
	TCODConsole::root->clear();
	TCODConsole::setFade(255, TCODColor::black);

	int lastY;

	lastY = gui->PrintGameOverScreen();

	e->gui->menu.Clear();
	e->gui->menu.AddItem(Menu::MIC_GOS_BACK_TO_MAIN_MENU, "Back To Main Menu");

	Menu::menu_item_code menuItem = e->gui->menu.Pick(true, 2, lastY + 2);

	if(menuItem == Menu::MIC_GOS_BACK_TO_MAIN_MENU) {
		runningMatch = nullptr;
		gameStatus = GAME_STATUS_MAIN;
	}
}

void
Engine::Render() {
    TCODConsole::root->clear();

    map->Render();
	
	TCODConsole::root->setCharBackground(mouse.cx, mouse.cy, TCODColor::white);

    for(Actor** it = arenaActors.begin(); it != arenaActors.end(); it++) {
        Actor* actor = *it;

        if(actor != player && ((!actor->fovOnly && map->IsExplored(actor->x, actor->y)) ||
           map->IsInFov(actor->x, actor->y))) 
		{
            actor->Render();
        }
    }

    player->Render();
    gui->Render();

    if(gameStatus == GAME_STATUS_ARENA_SANDBOX_STARTUP ||
       gameStatus == GAME_STATUS_ARENA_SANDBOX_IDLE ||
       gameStatus == GAME_STATUS_ARENA_SANDBOX_NEW_TURN)
    {
		TCODConsole::root->setCharForeground(mouse.cx, mouse.cy, TCODColor::black);
		TCODConsole::root->print(2, 2, "q - Generates a random orc at a random position");
		TCODConsole::root->print(2, 3, "w - Repair Equipment");
		TCODConsole::root->print(2, 4, "e - Heal to full health");
	}
}

//TODO: Only working for 1v1
int
Engine::CheckForEndOfRunningMatch() {
	if(player->destructible->IsDead()) {
		match_result* result = (match_result*)malloc(sizeof(match_result));

		if(runningMatch->contender1->code == '@') {
			result->first = runningMatch->contender2;
		}
		else {
			result->first = runningMatch->contender1;
		}

		result->second = player;

		result->third = nullptr;
		result->fourth = nullptr;

		runningMatch->result = result;

		return(-1);
	}
	else {
		int destructibleActors = 0;
		int aliveDestructibleActors = 0;

		for(Actor** it = arenaActors.begin(); it != arenaActors.end(); ++it) {
	        Actor* actor = *it;

	        if(actor->code != '@' && actor->destructible && !actor->destructible->IsDead()) {
				aliveDestructibleActors++;
	    	}
    	}

    	if(aliveDestructibleActors == 0) {
			match_result* result = (match_result*)malloc(sizeof(match_result));

			result->first = player;

			if(runningMatch->contender1->code == '@') {
				result->second = runningMatch->contender2;
			}
			else {
				result->second = runningMatch->contender1;
			}

			result->third = nullptr;
			result->fourth = nullptr;

			runningMatch->result = result;

    		return(1);
    	}
	}

	return(0);
}

//TODO: Consider a factory?
Tournament*
Engine::GenerateRandomTournament() {
	local_persist unsigned int nextId = 0;

	Tournament* result = nullptr;

	int typeOfTour = /*RandomNumberInRange(1, 2)*/1;

	switch (typeOfTour) {
	case 1:
	{
		result = new Tournament1V1();
		result->GenerateTournament();
	} break;

	case 2:
	{
		result = new Tournament1V1V1();
		result->GenerateTournament();
	} break;

	default:
	{
		result = new Tournament1V1();
		result->GenerateTournament();
	} break;
	}

	result->id = ++nextId;
	result->name = GenerateRandomTournamentName();

	result->gold = RandomNumberInRange(10, 100);

	return(result);
}

bool
Engine::PickATile(int* x, int* y, float maxRange) {
	while(!TCODConsole::isWindowClosed()) {
		Render();

		for(int cx = 0; cx < map->width; ++cx) {
			for(int cy = 0; cy < map->height; ++cy) {
				if(map->IsInFov(cx, cy) && (maxRange == 0 || player->GetDistance(cx, cy) <= maxRange)) {
					TCODColor color = TCODConsole::root->getCharBackground(cx, cy);
					TCODConsole::root->setCharBackground(cx, cy, color * 1.2f);
				}
			}
		}

		TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS | TCOD_EVENT_MOUSE, &lastKey, &mouse);

		if(map->IsInFov(mouse.cx, mouse.cy) &&
		   (maxRange == 0 || player->GetDistance(mouse.cx, mouse.cy) <= maxRange) &&
		   mouse.lbutton_pressed)
		{
			*x = mouse.cx;
			*y = mouse.cy;

			return(true);
		}

		if(mouse.rbutton_pressed || lastKey.vk != TCODK_NONE) {
			return(false);
		}

		TCODConsole::flush();
	}

	return(false);
}

Actor*
Engine::GetDestructibleActor(int x, int y) {
    for(Actor** it = allActors.begin(); it != allActors.end(); ++it) {
        Actor* actor = *it;

        if(actor->x == x && actor->y ==y && actor->destructible && !actor->destructible->IsDead()) {
            return(actor);
        }
    }

    return(nullptr);
}

Actor*
Engine::GetClosestDestructibleActor(int x, int y, int range) {
	Actor* closest = nullptr;
    float bestDistance = 1E6f;

    for(Actor** it = allActors.begin(); it != allActors.end(); ++it) {
        Actor* actor = *it;

        if(actor != player && actor->destructible && !actor->destructible->IsDead()) {
            float distance = actor->GetDistance(x, y);

            if(distance < bestDistance && (distance <= range || range == 0.0f)) {
                bestDistance = distance;
                closest = actor;
            }
        }
    }

    return(closest);
}

void
Engine::SendToBackWorld(Actor* actor) {
	if(actor) {
    	allActors.remove(actor);
    	allActors.insertBefore(actor, 0);
	}
}

void
Engine::SendToBackArena(Actor* actor) {
    SendToBackWorld(actor);

    if(actor) {
    	arenaActors.remove(actor);
   		arenaActors.insertBefore(actor, 0);
	}
}

void
Engine::AddActorToWorld(Actor* actor) {
	if(actor) {
		allActors.push(actor);
	}
}

void
Engine::RestActorFromWorld(Actor* actor) {
	if(actor) {
		allActors.remove(actor);
		deadActors.push(actor);
	}
}

void
Engine::AddActorToArena(Actor* actor) {
	AddActorToWorld(actor);

	if(actor) {
		numberOfActorsInArena++;
		arenaActors.push(actor);
	}
}

void
Engine::RestActorFromArena(Actor* actor) {
	RestActorFromWorld(actor);

	if(actor) {
		numberOfActorsInArena--;
		arenaActors.remove(actor);
	}
}

void
Engine::SetRunningMatch(Match* match) {
	runningMatch = match;
}

void
Engine::SetRunningTournament(Tournament* tour) {
	runningTournament = tour;
}

void
Engine::StoreRunningTournament(Tournament* tour) {
	tours.remove(tour);
	historyTours.push(tour);
}