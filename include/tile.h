#ifndef TILE_H
#define TILE_H

#include <memory>
#include <vector>

#include "pathfinding.h"

// Forward class declarations
class Object;
class BattleMap;

class Tile {
private:
	BattleMap *map;
	Object *contents;
	Location coordinates;
	std::shared_ptr<Tile> north;
	std::shared_ptr<Tile> east;
	std::shared_ptr<Tile> south;
	std::shared_ptr<Tile> west;
	std::shared_ptr<Tile> origin;
public:
	// Constructors
	Tile() : map(nullptr), contents(nullptr), north(nullptr), east(nullptr), south(nullptr), west(nullptr), origin(nullptr) {};	// Default
	Tile(BattleMap *map, int x, int y);										// Rectangle
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
	int findMinimumPath(Tile* target, std::vector<Tile*>& visited);		// Recursive function.
	// Find closest point to target that can be reached in a set number of hops.
	Tile* findMidPoint(Tile* target, int moves);
	// Return size of tile map.
	int width();
	int height();

	// Utility functions
	bool isUnblocked() { return contents; };
	bool isDestination(Tile *dest) { return this == dest; };

	// Pathfinding functions
	double calculateHValue(Tile *dest);

	// Getters/setters
	Object* getContents() { return contents; };
	int setContents(Object* Contents);			// Defined in file
	Location getCoordinates() { return coordinates; };
	int setCoordinates(int x, int y, int z) { coordinates = Location(x,y,z); return 0; };
	int setCoordinates(Location Coordinates) { coordinates = Coordinates; return 0; };
	Object* clearContents() { contents = NULL; return contents; };
	Tile* getNorth() { return north.get(); };
	int setNorth(Tile* North) { north.reset(North); return 0;};
	Tile* getEast() { return east.get(); };
	int setEast(Tile* East) { east.reset(East); return 0;};
	Tile* getSouth() { return south.get(); };
	int setSouth(Tile* South) { south.reset(South); return 0;};
	Tile* getWest() { return west.get(); };
	int setWest(Tile* West) { west.reset(West); return 0;};
};

#endif
