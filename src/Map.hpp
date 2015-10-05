#ifndef RL_MAP_HPP
#define RL_MAP_HPP

global_variable TCODColor MAP_COLOR_DARK_WALL(0, 0, 100);
global_variable TCODColor MAP_COLOR_DARK_GROUND(50, 50, 150);
global_variable TCODColor MAP_COLOR_LIGHT_WALL(130, 110, 50);
global_variable TCODColor MAP_COLOR_LIGHT_GROUND(200, 180, 50);

struct Tile {
    bool explored;

    Tile() :
		explored(false)
	{
	}
};

class Map : public Persistent {

	friend class BspListener;

public:
	int	width;
	int	height;

    Map(int width, int height);
    ~Map();

	void
	Init(bool withActors);

	void
	Save(TCODZip& zip);

	void
	Load(TCODZip& zip);

	void
	Render();

    void
    ComputeFov();

	bool
	IsWall(int x, int y);

	bool
	IsInFov(int x, int y);

	bool
	IsExplored(int x, int y);

	bool
	CanWalk(int x, int y);

protected:
    Tile* tiles;
	TCODMap* map;
	TCODRandom* rng;
	TCODNoise* torchNoise;

    long seed;

	float playerTorchX;
	float playerTorchY;
	float playerTorchVariation;
	float playerTorchIntensity;

    void
    Dig(int x1, int y1, int x2, int y2);

    void
    CreateRoom(int x1, int y1, int x2, int y2, bool withActors);

    void
    AddMonster(int x, int y);

    void
    AddItem(int x, int y);
};

#endif