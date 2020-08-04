#ifndef OBJECT_H
#define OBJECT_H

#include "pathfinding.h"

class object {
protected:
	location coordinates;
public:
	// Constructors
	object() : coordinates(location(0,0,0)) {};
	object(location Coordinates) : coordinates(Coordinates) {};
};

#endif
