#pragma once
#include "tile.h"

#include <list>
#include <vector>

class Object;

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

	// Game running
	void run_encounter(sf::RenderWindow &window));

	// Public variables
	std::vector<Object*> objects;
	std::list<Object*> initiative_order;
};

