#ifndef OBJECT_H
#define OBJECT_H

#include "pathfinding.h"
#include <string>

class object {
protected:
	std::string name;
	location coordinates;
public:
	// Constructors
	object() : coordinates(location(0,0,0)) {};
	object(location Coordinates) : coordinates(Coordinates) {};

	// Getters/setters
	virtual std::string getName() { return name; };
	virtual int setName(std::string Name) { name = Name; return 0; };
};

#endif
