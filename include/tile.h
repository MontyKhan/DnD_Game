#ifndef TILE_H
#define TILE_H

#include "object.h"
#include "pathfinding.h"

#define MAX_VALUE 32767

class Tile {
private:
	object* contents;
	location coordinates;
	Tile* north;
	Tile* east;
	Tile* south;
	Tile* west;
public:
	// Constructors
	Tile() : contents(NULL), north(NULL), east(NULL), south(NULL), west(NULL) {};	// Default
	Tile(int x, int y);								// Rectangle

	// Print entire tile grid to screen, each tile represented by "x"
	void print_map();
	// Print map starting Tile, each tile represented by "x"
	void print_from();
	// Get specific tile by map reference, location.
	Tile* get(location coordinates);
	// Get specific tile by map reference, individual ints.
	Tile* get(int x, int y);
	// Get specific tile by contents.
	Tile* get(object *toFind);
	// Finds distance to another tile.
	int findMinimumPath(Tile* target);			// Accessor for when calling within code.
	int findMinimumPath(Tile* target, int hops);		// Recursive function.

	// Getters/setters
	object* getContents() { return contents; };
	int setContents(object* Contents);			// Defined in file
	location getCoordinates() { return coordinates; };
	int setCoordinates(int x, int y, int z) { coordinates = location(x,y,z); return 0; };
	int setCoordinates(location Coordinates) { coordinates = Coordinates; return 0; };
	object* clearContents() { contents = NULL; return contents; };
	Tile* getNorth() { return north; };
	int setNorth(Tile* North) { north = North; };
	Tile* getEast() { return east; };
	int setEast(Tile* East) { east = East; };
	Tile* getSouth() { return south; };
	int setSouth(Tile* South) { south = South; };
	Tile* getWest() { return west; };
	int setWest(Tile* West) { west = West; };
};

#endif
