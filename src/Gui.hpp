#ifndef RL_GUI_HPP
#define RL_GUI_HPP

global_variable int GUI_INVENTORY_WIDTH = 50;
global_variable int GUI_INVENTORY_HEIGHT = 28;

global_variable int GUI_MAIN_WIDTH = 100;
global_variable int GUI_MAIN_HEIGHT = 30;

global_variable int GUI_STATS_WIDTH = 50;
global_variable int GUI_STATS_HEIGHT = 52;

global_variable int GUI_PLAYER_STATS_MENU_WIDTH = 50;
global_variable int GUI_PLAYER_STATS_MENU_HEIGHT = 50;

global_variable int GUI_AVAILABLE_TOURNAMENTS_WIDTH = 50;
global_variable int GUI_AVAILABLE_TOURNAMENTS_HEIGHT = 50;

global_variable int GUI_VIEW_TOURNAMENT_WIDTH = 40;
global_variable int GUI_VIEW_TOURNAMENT_HEIGHT = 40;

global_variable TCODConsole GUI_CONSOLE_INVENTORY(GUI_INVENTORY_WIDTH, GUI_INVENTORY_HEIGHT);
global_variable TCODConsole GUI_CONSOLE_MAIN(GUI_MAIN_WIDTH, GUI_MAIN_HEIGHT);
global_variable TCODConsole GUI_CONSOLE_STATS(GUI_STATS_WIDTH, GUI_STATS_HEIGHT);
global_variable TCODConsole GUI_CONSOLE_PLAYER_STATS_MENU(GUI_PLAYER_STATS_MENU_WIDTH, GUI_PLAYER_STATS_MENU_HEIGHT);
global_variable TCODConsole GUI_CONSOLE_AVAILABLE_TOURNAMENTS(GUI_AVAILABLE_TOURNAMENTS_WIDTH, GUI_AVAILABLE_TOURNAMENTS_HEIGHT);
global_variable TCODConsole GUI_CONSOLE_VIEW_TOURNAMENT(GUI_VIEW_TOURNAMENT_WIDTH, GUI_VIEW_TOURNAMENT_HEIGHT);

//NOTE: Log.
global_variable int GUI_LOG_HEIGHT = 7;
global_variable int GUI_LOG_MSG_X = 25;
global_variable int GUI_LOG_MSG_HEIGHT = 6;

global_variable int GUI_LOG_MOUSELOOK_X = 1;
global_variable int GUI_LOG_MOUSELOOK_Y = 0;

global_variable int GUI_PLAYER_HP_BAR_X = 1;
global_variable int GUI_PLAYER_HP_BAR_Y = 1;
global_variable int GUI_PLAYER_HP_BAR_WIDTH = 20;
global_variable int GUI_PLAYER_HP_BAR_HEIGHT = 1;

class Menu {
public:
	//NOTE: MIC = Menu Item Code
	//NOTE: MS = Main Screen
	//NOTE: MTS = Main Tournament Screen
	//NOTE: AMWS = Arena MAtch Won Screen
	//NOTE: GOS = Game Over Screen
	enum menu_item_code {
		MIC_NONE = 0,						//Special options
		MIC_BACK,
        MIC_EXIT,
		MIC_NEW_GAME,						//Main menu options
		MIC_CONTINUE,
		MIC_MS_ENTER_TOURNAMENT,			//5 //Main Screen menu
		MIC_MS_TOURNAMENTS,
		MIC_MS_ARENA_TEST,
		MIC_MS_TOURNAMENTS_1,				//Main Screen menu - Tournaments
		MIC_MS_TOURNAMENTS_2,
		MIC_MS_TOURNAMENTS_3,				//10
		MIC_MS_TOURNAMENTS_4,
		MIC_MS_TOURNAMENTS_5,
		MIC_MS_TOURNAMENTS_6,
		MIC_MS_TOURNAMENTS_7,
		MIC_MS_TOURNAMENTS_8,				//15
		MIC_MS_TOURNAMENTS_9,
		MIC_MTS_SIMULATE,
		MIC_MTS_FIGHT,
		MIC_AMWS_BACK_TO_TOURNAMENT,
		MIC_GOS_BACK_TO_MAIN_MENU,			//20
        MIC_CONSTITUTION,					//Upgrades
        MIC_STRENGTH,
        MIC_AGILITY
    };

    enum display_mode {
        DISPLAY_MODE_MAIN,
        DISPLAY_MODE_PAUSE
    };

    ~Menu();

    void
    Clear();

    void
    AddItem(menu_item_code code, char* label);

    menu_item_code
    Pick(bool displayBakcgroundImage, int startX, int startY);

protected:
    struct menu_item {
        menu_item_code code;
        char* label;
    };

    TCODList<menu_item*> items;
};

class Gui : public Persistent {
public:
    Menu menu;

    Gui();
    ~Gui();

	void
	Save(TCODZip& zip);
	
	void
	Load(TCODZip& zip);

	void
	Render();

	void
	RenderIntroStory(char* text);

	void
	Clear();

	void
	Message(TCODColor color, char* text, ...);

	void
	HighlightOption(TCODConsole* console, int x, int y, char* optionText);

	void
	DisplayPlayerStatsMain();

	void
	DisplayTournamentsMain();

	int
	PrintArenaMatchWonScreen();

	int
	PrintGameOverScreen();

	void
	PrintActor(Actor* actor, TCODConsole* console, int startX, int startY, int frameSizeX, int frameSizeY, char* frameTitle);

	void
	PrintDestructible(Destructible* destructible, TCODConsole* console, int startX, int startY);

	void
	PrintWeapon(Weapon* armor, TCODConsole* console, char* side, char* weaponType, int startX, int startY);

	void
	PrintArmor(Armor* armor, TCODConsole* console, char* armorType, int startX, int startY);

protected:
    TCODConsole* console;

    struct message {
        char* text;
        TCODColor color;

		message(char* text, TCODColor color) :
			text(_strdup(text)),
			color(color)
		{
		}

		~message() {
			free(text);
		}
    };

    TCODList<message*> log;

    void
    RenderBar(int x, int y, int width, int height, char* name, int value, int maxValue,
			  TCODColor barColor, TCODColor backColor);

	void
	RenderMouseLook();
};

#endif