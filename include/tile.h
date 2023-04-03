#ifndef TILE_H
#define TILE_H

#include "pathfinding.h"

// Forward class declarations
class Object;

class Tile {
private:
	Object *contents;
	Location coordinates;
	Tile *north;
	Tile *east;
	Tile *south;
	Tile *west;
	Tile *origin;
public:
	// Constructors
	Tile() : contents(nullptr), north(nullptr), east(nullptr), south(nullptr), west(nullptr), origin(nullptr) {};	// Default
	Tile(int x, int y);										// Rectangle
	~Tile();

	// Print entire tile grid to screen, each tile represented by "x"
	void print_map();
	// Print map starting Tile, each tile represented by "x"
	void print_from();
	// Get specific tile by map reference, Location.
	Tile* get(Location coordinates);
	// Get specific tile by map reference, individual ints.
	Tile* get(int x, int y);
	// Get specific tile by contents.
	Tile* get(Object *toFind);
	// Finds distance to another tile.
	int findMinimumPath(Tile* target);			// Accessor for when calling within code.
	int findMinimumPath(Tile* target, int hops);		// Recursive function.
	// Find closest point to target that can be reached in a set number of hops.
	Tile* findMidPoint(Tile* target, int moves);
	// Return size of tile map.
	int width();
	int height();

	// Getters/setters
	Object* getContents() { return contents; };
	int setContents(Object* Contents);			// Defined in file
	Location getCoordinates() { return coordinates; };
	int setCoordinates(int x, int y, int z) { coordinates = Location(x,y,z); return 0; };
	int setCoordinates(Location Coordinates) { coordinates = Coordinates; return 0; };
	Object* clearContents() { contents = NULL; return contents; };
	Tile* getNorth() { return north; };
	int setNorth(Tile* North) { north = North; return 0;};
	Tile* getEast() { return east; };
	int setEast(Tile* East) { east = East; return 0;};
	Tile* getSouth() { return south; };
	int setSouth(Tile* South) { south = South; return 0;};
	Tile* getWest() { return west; };
	int setWest(Tile* West) { west = West; return 0;};
};

#endif
