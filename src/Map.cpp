#include "main.hpp"

Map::Map(int width, int height) :
	width(width), height(height),
	playerTorchX(0.0f), playerTorchY(0.0f),
	playerTorchVariation(0.0f), playerTorchIntensity(0.0f)
{
    seed = TCODRandom::getInstance()->getInt(0, 0x7FFFFFFF);
}

Map::~Map() {
	delete[] tiles;
	tiles = nullptr;

	delete map;
	map = nullptr;

	delete rng;
	rng = nullptr;

	delete torchNoise;
	torchNoise = nullptr;
}

void
Map::Init(bool withallActors) {
	tiles = new Tile[width * height];
	map = new TCODMap(width, height);
    rng = new TCODRandom(seed, TCOD_RNG_CMWC);
	torchNoise = new TCODNoise(1);
	
	CreateRoom(1, 1, width - 2, height - 2, true);
}

void
Map::Render() {
	for(int x = 0; x < width; ++x) {
		for(int y = 0; y < height; ++y) {
			if(IsInFov(x, y)) {
				bool wall = IsWall(x, y);

				TCODColor base = (wall ? MAP_COLOR_DARK_WALL : MAP_COLOR_DARK_GROUND);
				TCODColor light = (wall ? MAP_COLOR_LIGHT_WALL : MAP_COLOR_LIGHT_GROUND);

				float r = (float)((x - e->player->x + playerTorchX) * 
								  (x - e->player->x + playerTorchX) +
								  (y - e->player->y + playerTorchY) *
								  (y - e->player->y + playerTorchY));

				if(r < e->fovRadiusSquared) {
					float l = (e->fovRadiusSquared - r) / e->fovRadiusSquared + playerTorchIntensity;
					l = CLAMP(0.0f, 1.0f, l);
					base = TCODColor::lerp(base, light, l);
				}

				light = base;

				//TCODConsole::root->setCharBackground(x, y, light, TCOD_BKGND_SET);
				TCODConsole::root->setCharBackground(x, y, IsWall(x, y) ? MAP_COLOR_DARK_WALL : MAP_COLOR_DARK_GROUND);
			}
			else if(IsExplored(x, y)) {
				TCODConsole::root->setCharBackground(x, y, IsWall(x, y) ? MAP_COLOR_DARK_WALL : MAP_COLOR_DARK_GROUND);
			}
		}
	}
}

void
Map::ComputeFov() {
	map->computeFov(e->player->x, e->player->y, e->fovRadius, true, FOV_BASIC);

	playerTorchVariation += 0.2f;

	float tdx = playerTorchVariation + 20.0f;
	playerTorchX = torchNoise->get(&tdx) * 1.5f;

	tdx += 30.0f;

	playerTorchY = torchNoise->get(&tdx) * 1.5f;
	playerTorchIntensity = 0.2f * torchNoise->get(&playerTorchVariation);
}

bool
Map::IsWall(int x, int y) {
	return(!map->isWalkable(x, y));
}

bool
Map::CanWalk(int x, int y) {
	if(IsWall(x, y)) {
		return(false);
	}

	for(Actor** it = e->arenaActors.begin(); it != e->arenaActors.end(); ++it) {
		Actor* actor = *it;
		if(actor->blocks && actor->x == x && actor->y == y) {
			return(false);
		}
	}

	return(true);
}

bool
Map::IsExplored(int x, int y) {
	return(tiles[x + y * width].explored);
}

bool
Map::IsInFov(int x, int y) {
	if(x < 0 || x >= width || y < 0 || y >= height) {
		return(false);
	}

	if(map->isInFov(x, y)) {
		tiles[x + y * width].explored = true;
		return(true);
	}

	return(false);
}

void
Map::Dig(int x1, int y1, int x2, int y2) {
    if (x2 < x1) {
        int tmp = x2;
        x2 = x1;
        x1 = tmp;
    }

    if (y2 < y1) {
        int tmp = y2;
        y2 = y1;
        y1 = tmp;
    }

    for(int tileX = x1; tileX <= x2; ++tileX) {
        for(int tileY = y1; tileY <= y2; ++tileY) {
            map->setProperties(tileX, tileY, true, true);
        }
    }
}

void
Map::CreateRoom(int x1, int y1, int x2, int y2, bool withallActors) {
	Dig(x1, y1, x2, y2);

	if(!withallActors) {
		return;
	}

	TCODRandom* rng = TCODRandom::getInstance();

	int numberOfItems = 0;

	while(numberOfItems > 0) {
		int x = rng->getInt(x1, x2);
		int y = rng->getInt(y1, y2);

		if(CanWalk(x, y)) {
			AddItem(x, y);
		}

		numberOfItems--;
	}
}

void
Map::AddItem(int x, int y) {
	TCODRandom* rng = TCODRandom::getInstance();
	Actor* actor = nullptr;

    int dice = rng->getInt(0, 90);

    if (dice < 70) {
		actor = CreateActorItemPotionHealth(x, y);
    }
    else if (dice < 70 + 10) {
		actor = CreateActorItemScrollLightningBolt(x, y);
    }
    else {
		actor = CreateActorItemScrollFireball(x, y);
    }

	e->AddActorToArena(actor);
}