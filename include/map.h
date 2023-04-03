#pragma once
#include "tile.h"
#include "object.h"

class BattleMap :: public Tile
{
	Tile *origin;
	std::vector<Object*> objects;

public:
	BattleMap(uint8_t x, uint8_t y, std::vector<Object*> objects);
};

