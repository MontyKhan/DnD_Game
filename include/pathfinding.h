#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <stdio.h>
#include <iostream>
#include <math.h>

const float DIAGONAL_NEIGHBOUR = sqrt(2);

class Location {
private:
	int x;
	int y;
	int z;
public:
	// Default constructor
	Location() :
		x{ 0 }, y{ 0 }, z{ 0 } {};
	// Constructor for each argument seperately.
	Location(int X, int Y, int Z) :
		x{ X }, y{ Y }, z{ Z } {};
	// Constructor for string, defined in file.
	Location(std::string str);
	// Copy constructor
	Location(Location &l) :
		x{ l.x }, y{ l.y }, z(l.z) {};

	// Find euclidean distance to other point.
	int find_distance(Location coords);

	// Getters/setters
	int getX() const { return x; };
	void setX(int X) { x = X; };
	int getY() const { return y; };
	void setY(int Y) { y = Y; };
	int getZ() const { return z; };
	void setZ(int Z) { z = Z; };

	// Friend functions
	friend std::ostream & operator << (std::ostream &out, const Location &l);	// Print location
	friend bool operator == (const Location &rhs, const Location &lhs);		// Check for equality.
	friend bool operator != (const Location &rhs, const Location &lhs);		// Check for inequality.
	friend Location operator + (const Location &rhs, const Location &lhs);		// Sum locations
	friend Location operator - (const Location &rhs, const Location &lhs);		// Subtract locations
	friend float find_euc(Location rhs, Location lhs);				// Find distance between locations
};

float find_euc(Location rhs, Location lhs);

#endif
