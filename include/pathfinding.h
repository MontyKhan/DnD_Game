#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <stdio.h>
#include <iostream>
#include <math.h>

class location {
private:
	int x;
	int y;
	int z;
public:
	// Default constructor
	location() :
		x(0), y(0), z(0) {};
	// Constructor for each argument seperately.
	location(int X, int Y, int Z) :
		x(X), y(Y), z(Z) {};
	// Constructor for string, defined in file.
	location(std::string str);

	// Find euclidean distance to other point.
	int find_distance(location coords);

	// Getters/setters
	int getX() const { return x; };
	void setX(int X) { x = X; };
	int getY() const { return y; };
	void setY(int Y) { y = Y; };
	int getZ() const { return z; };
	void setZ(int Z) { z = Z; };

	// Friend functions
	friend std::ostream & operator << (std::ostream &out, const location &l);
	friend bool operator == (const location &rhs, const location &lhs);
	friend float find_euc(location rhs, location lhs);
};

int find_euc(int x, int y, int h);	// Find euclidean distance between two points.
float find_euc(location rhs, location lhs);

#endif
