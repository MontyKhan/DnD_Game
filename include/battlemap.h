#pragma once
#include "tile.h"
#include "object.h"

#include <list>

class BattleMap
{
	Tile *origin;

public:
	BattleMap(uint8_t x, uint8_t y, std::vector<Object*> objects);

	void print_map() { origin->print_map(); };
	void assignInitiativeOrder();

	// Get specific tile by map reference, Location.
	Tile* get(Location coordinates);
	// Get specific tile by map reference, individual ints.
	Tile* get(int x, int y);
	// Get specific tile by contents.
	Tile* get(Object* toFind);

	// Map charateristics
	uint8_t width() { return origin->width(); };
	uint8_t height() { return origin->height(); };

	// Public variables
	std::vector<Object*> objects;
	std::list<Object*> initiative_order;
};

