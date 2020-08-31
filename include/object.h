#ifndef OBJECT_H
#define OBJECT_H

#include "pathfinding.h"
#include <string>
#include <vector>

#define MAX_VALUE 32767

class Tile;

class object {
protected:
	std::string name;
	location coordinates;
	Tile* parent;
public:
	// Constructors
	object() : name(""), coordinates(location(0,0,0)), parent(NULL) {};
	object(location Coordinates) : name(""), coordinates(Coordinates), parent(NULL) {};

	// Get a list of vacant neighbouring tiles.
	std::vector<Tile*> getFreeNeighbours();

	// Getters/setters
	virtual std::string getName() { return name; };
	virtual int setName(std::string Name) { name = Name; return 0; };
	location getCoordinates() { return coordinates; };
	int setCoordinates(location Coordinates) { coordinates = Coordinates; return 0; };
	Tile* getParent() { return parent; };
	int setParent( Tile* Parent ) { parent = Parent; return 0; };
};

#endif
