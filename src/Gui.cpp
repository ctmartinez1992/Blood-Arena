#include <stdio.h>
#include <stdarg.h>
#include "main.hpp"

int PAUSE_MENU_WIDTH = 30;
int PAUSE_MENU_HEIGHT = 15;

Menu::~Menu() {
	Clear();
}

void
Menu::Clear() {
	items.clearAndDelete();
}

void
Menu::AddItem(menu_item_code code, char* label) {
	menu_item* item = (menu_item*)calloc(1, sizeof(menu_item));

	item->code = code;
	item->label = label;

	items.push(item);
}

Menu::menu_item_code
Menu::Pick(bool displayBakcgroundImage, int startX, int startY) {
	int selectedItem = 0;

	int menuX = startX;
	int menuY = startY;

	if(displayBakcgroundImage) {
		TCODImage img("res/menu_background.png");
		img.blit2x(TCODConsole::root, 80, 50);
	}

	while(!TCODConsole::isWindowClosed()) {
		int currentItem = 0;

		for(menu_item** it = items.begin(); it != items.end(); ++it) {
			if(currentItem == selectedItem) {
				TCODConsole::root->setDefaultForeground(TCODColor::lighterOrange);
			}
			else {
				TCODConsole::root->setDefaultForeground(TCODColor::lightGrey);
			}

			TCODConsole::root->print(menuX, menuY + currentItem * 3, (*it)->label);

			currentItem++;
		}

		TCODConsole::flush();

		TCOD_key_t key;
		TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);
		switch(key.vk) {
			case TCODK_UP:
			{
				selectedItem--;

				if(selectedItem < 0) {
					selectedItem = items.size() - 1;
				}
			} break;

			case TCODK_DOWN:
			{
				selectedItem = (selectedItem + 1) % items.size();
			} break;

			case TCODK_ENTER:
			{
				return(items.get(selectedItem)->code);
			} break;

			default:
			{
			} break;
		}
	}

	return(MIC_NONE);
}

Gui::Gui() {
    console = new TCODConsole(e->screenWidth, GUI_LOG_HEIGHT);
}

Gui::~Gui() {
    delete console;
    console = nullptr;

    Clear();
}

void
Gui::Render() {
	console->setDefaultBackground(TCODColor::black);
	console->clear();

	RenderBar(1, 1, GUI_PLAYER_HP_BAR_WIDTH, GUI_PLAYER_HP_BAR_HEIGHT, "HP", e->player->destructible->curHP,
			  e->player->destructible->maxHP, TCODColor::lightRed, TCODColor::darkerRed);

	int y = 1;
	float colorFadeOut = 0.4f;

	for(message** it = log.begin(); it != log.end(); ++it) {
		message* message = *it;

		console->setDefaultForeground(message->color * colorFadeOut);
		console->print(GUI_LOG_MSG_X, y, message->text);

		y++;

		if(colorFadeOut < 1.0f) {
			colorFadeOut += 0.3f;
		}
	}

	RenderMouseLook();

	TCODConsole::blit(console, 0, 0, e->screenWidth, GUI_LOG_HEIGHT, TCODConsole::root, 0, 
					  e->screenHeight - GUI_LOG_HEIGHT);
}

void
Gui::Clear() {
    log.clearAndDelete();
}

void
Gui::Message(TCODColor color, char* text, ...) {
	va_list ap;
	char buffer[512];

	va_start(ap, text);
	vsprintf_s(buffer, text, ap);
	va_end(ap);

	char* lineBegin = buffer;
	char* lineEnd;

	do {
		if(log.size() == GUI_LOG_MSG_HEIGHT) {
			message* toRemove = log.get(0);

			log.remove(toRemove);

			delete toRemove;
			toRemove = nullptr;
		}

		lineEnd = strchr(lineBegin, '\n');

		if(lineEnd) {
			*lineEnd = '\0';
		}

		message* msg = new message(lineBegin, color);

		log.push(msg);

		lineBegin = lineEnd + 1;
	} while(lineEnd);
}

void
Gui::HighlightOption(TCODConsole* console, int x, int y, char* optionText) {
	console->setDefaultForeground(TCODColor::green);
	console->print(x, y, &(optionText[0]));

	console->setDefaultForeground(TCODColor::white);
	console->print(x + 1, y, ++optionText);
}

void
Gui::DisplayPlayerStatsMain() {
	TCODConsole* console = &GUI_CONSOLE_PLAYER_STATS_MENU;

	e->gui->PrintActor(e->player, console, 2, 2,
						   GUI_PLAYER_STATS_MENU_WIDTH, GUI_PLAYER_STATS_MENU_HEIGHT, "Your Stats");
    
	TCODConsole::blit(console, 0, 0, GUI_PLAYER_STATS_MENU_WIDTH, GUI_PLAYER_STATS_MENU_HEIGHT, TCODConsole::root, 
                      2, e->screenHeight - GUI_PLAYER_STATS_MENU_HEIGHT - 2);
    TCODConsole::flush();
}

void
Gui::DisplayTournamentsMain() {
	bool exitMenu = false;

	do {
		TCODConsole::root->clear();
		TCODConsole::setFade(255, TCODColor::black);

		menu.Clear();

		int index = (int)Menu::MIC_MS_TOURNAMENTS_1;
		Tournament* tour = nullptr;

		for(Tournament** it = e->tours.begin(); it != e->tours.end(); ++it, ++index) {
			tour = *it;

			menu.AddItem((Menu::menu_item_code)index, tour->name->fullName);
		}

		menu.AddItem(Menu::MIC_BACK, "Back");

		int menuCode = menu.Pick(true, 2, 2);

		if(menuCode == Menu::MIC_BACK) {
			exitMenu = true;
		}
		else if(menuCode >= Menu::MIC_MS_TOURNAMENTS_1 && menuCode <= Menu::MIC_MS_TOURNAMENTS_9){
			exitMenu = e->tours.get(((int)menuCode) - ((int)Menu::MIC_MS_TOURNAMENTS_1))->PrintTournamentInformation();
		}
	} while(!exitMenu);
}

int
Gui::PrintArenaMatchWonScreen() {
	TCODConsole::root->setDefaultForeground(TCODColor::lightGrey);
	TCODConsole::root->print(2, 2, "You won the match!");

	TCODConsole::flush();

	return(2);
}

int
Gui::PrintGameOverScreen() {
	TCODConsole::root->setDefaultForeground(TCODColor::lightGrey);
	TCODConsole::root->print(2, 2, "You died!");

	TCODConsole::flush();

	return(2);
}

void
Gui::PrintActor(Actor* actor, TCODConsole* console, int startX, int startY, int frameSizeX, int frameSizeY, char* frameTitle) {
	if(actor && console) {
		console->setDefaultForeground(TCODColor(200, 180, 50));
		console->printFrame(0, 0, GUI_STATS_WIDTH, GUI_STATS_HEIGHT, true, TCOD_BKGND_DEFAULT, frameTitle);

		console->setDefaultForeground(TCODColor::white);
		console->print(2, 2, "%s", actor->fullName);

		PrintDestructible(actor->destructible, console, 2, 4);
	        
		PrintWeapon(actor->leftHandWeapon, console, "Left", "Head", 2, 7);

		PrintArmor(actor->headArmor, console, "Head", 2, 12);
		PrintArmor(actor->chestArmor, console, "Chest", 2, 16);
		PrintArmor(actor->legArmor, console, "Legs", 2, 20);
		PrintArmor(actor->leftShoulderArmor, console, "Left Shoulder", 2, 24);
		PrintArmor(actor->rightShoulderArmor, console, "Right Shoulder", 2, 28);
		PrintArmor(actor->leftArmArmor, console, "Left Arm", 2, 32);
		PrintArmor(actor->rightArmArmor, console, "Right Arm", 2, 36);
		PrintArmor(actor->leftFootArmor, console, "Left Foot", 2, 40);
		PrintArmor(actor->rightFootArmor, console, "Right Foot", 2, 44);

		console->print(2, 48, "Gold: %.0f", actor->gold);

		console->print(26, 50, "...Press ENTER to close");
	}
}

void
Gui::PrintDestructible(Destructible* destructible, TCODConsole* console, int startX, int startY) {
	if(destructible) {
		console->print(startX, startY, "HP: %d/%d", destructible->curHP, destructible->maxHP);
		console->print(startX, startY + 1, "Defense: %.2f", destructible->defense);
	}
}

void
Gui::PrintWeapon(Weapon* weapon, TCODConsole* console, char* side, char* weaponType, int startX, int startY) {
    if(weapon) {
        console->print(startX, startY, "%s Weapon: %s", side, weapon->name);
        console->print(startX + 4, startY + 1, "Damage: %.2f", weapon->baseDamage);
        console->print(startX + 4, startY + 2, "Defense: %.2f", weapon->defense);
        console->print(startX + 4, startY + 3, "Durability: %.2f/%.2f",
        			   weapon->durability, weapon->maxDurability);
    }
}

void
Gui::PrintArmor(Armor* armor, TCODConsole* console, char* armorType, int startX, int startY) {
	if(armor) {
        console->print(startX, startY, "%s: %s", armorType, armor->name);
        console->print(startX + 4, startY + 1, "Armor: %.2f", armor->baseArmor);
        console->print(startX + 4, startY + 2, "Durability: %.2f/%.2f", armor->durability, armor->maxDurability);
    }
}

void
Gui::RenderBar(int x, int y, int width, int height, char* name, int value, int maxValue,
			   TCODColor barColor, TCODColor backColor)
{
    console->setDefaultBackground(backColor);
    console->rect(x, y, width, height, false, TCOD_BKGND_SET);

    int barWidth = (int)((float)value / (float)maxValue * width);

    if(barWidth > 0) {
        console->setDefaultBackground(barColor);
        console->rect(x, y, barWidth, height, false, TCOD_BKGND_SET);
    }

    console->setDefaultForeground(TCODColor::white);
    console->printEx(x + width / 2, y, TCOD_BKGND_NONE, TCOD_CENTER, "%s : %d/%d", name, value, maxValue);
}

void
Gui::RenderMouseLook() {
    if(!e->map->IsInFov(e->mouse.cx, e->mouse.cy) && e->mouse.cx != 0 && e->mouse.cy != 0) {
        return;
    }

    bool first = true;
    char buffer[1024] = "";

    for(Actor** it = e->arenaActors.begin(); it != e->arenaActors.end(); ++it) {
        Actor* actor = *it;

        if(actor->x == e->mouse.cx && actor->y == e->mouse.cy) {
            if(!first) {
                strcat_s(buffer, ", ");
            }
            else {
				first = false;
            }

            strcat_s(buffer, actor->fullName);
        }
    }

    console->setDefaultForeground(TCODColor::lightGrey);
    console->print(GUI_LOG_MOUSELOOK_X, GUI_LOG_MOUSELOOK_Y, buffer);
}