#ifndef RL_ENGINE_HPP
#define RL_ENGINE_HPP

class Engine {
public:
    enum game_status {
    	GAME_STATUS_BOOTING,		//Booting the game, should only appear when the game in launched.
        GAME_STATUS_MAIN,			//In the main menu, selecting tournaments, stats, etc.
        GAME_STATUS_TOURNAMENT_MAIN,//In a tournament, can only leave when it's over or you die.
        GAME_STATUS_ARENA_STARTUP,	//First time it enters gameplay and needs to compute FOV, prepare, etc.
        GAME_STATUS_ARENA_IDLE,		//In the gameplay, waiting for the users input.
        GAME_STATUS_ARENA_NEW_TURN,	//The player did something, process all entities and world.
        GAME_STATUS_ARENA_SANDBOX_STARTUP,	//Like arena but for testing.
        GAME_STATUS_ARENA_SANDBOX_IDLE,		//Like arena but for testing.
        GAME_STATUS_ARENA_SANDBOX_NEW_TURN,	//Like arena but for testing.
        GAME_STATUS_GAME_OVER,		//Player is dead, show little menu with restart option.
        GAME_STATUS_EXIT			//Leave the game.
    } gameStatus;

    //NOTE: Contains all actors, including the player and every entity.
	TCODList<Actor*> allActors;
    //NOTE: Contains all the actors currently in the arena.
	TCODList<Actor*> arenaActors;
	//NOTE: All orcs that died will be stored here and eventually put into a file.
	TCODList<Actor*> deadActors;
	Actor* player;

	int numberOfActorsInArena;

	TCODList<Tournament*> tours;
	TCODList<Tournament*> historyTours;
	Tournament* runningTournament;	//NOTE: Pointer to the tournament the player is currently in.
	Match* runningMatch;			//NOTE: Current match the player is in, if not in match, it's null.

	Gui* gui;
	Map* map;

	//NOTE: All DODContent has to be condensed in this class.
	DODContent* c;

    TCOD_key_t lastKey;
    TCOD_mouse_t mouse;

	int fovRadius;
	int fovRadiusSquared;

    int screenWidth;
    int screenHeight;

    bool inSandbox;
	bool leaveGame;

	Engine(int screenWidth, int screenHeight);
	~Engine();

	void
	Init();

	void
	Close();

    void
    Update();

    //NOTE: Called only when gameStatus == GAME_STATUS_ARENA_SANDBOX_IDLE
    void
    UpdateSandbox();

    void
    MainScreen();

    void
    TournamentMainScreen();

    void
    ArenaMatchWonScreen();

    void
    GameOverScreen();

	void
	Render();

	void
	Save();

	void
	Load(bool pause = false);

	//NOTE: Returns -1 if player died, Returns 0 if it's ongoing, Returns 1 if player is victorious.
	int
	CheckForEndOfRunningMatch();

	Tournament*
	GenerateRandomTournament();

	//NOTE: If maxRange = 0, then the whole map is pickable.
	bool
	PickATile(int* x, int* y, float maxRange = 0.0f);

    Actor*
    GetDestructibleActor(int x, int y);

	Actor*
	GetClosestDestructibleActor(int x, int y, int range);

	void
	SendToBackWorld(Actor *actor);

	void
	SendToBackArena(Actor *actor);

	void
	AddActorToWorld(Actor* actor);

	void
	RestActorFromWorld(Actor* actor);

	void
	AddActorToArena(Actor* actor);

	void
	RestActorFromArena(Actor* actor);

	void
	SetRunningMatch(Match* match);

	void
	SetRunningTournament(Tournament* tour);

	void
	StoreRunningTournament(Tournament* tour);
};

extern Engine* e;

#endif