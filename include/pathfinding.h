#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <stdio.h>
#include <iostream>
#include <math.h>

const float DIAGONAL_NEIGHBOUR = sqrt(2);

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
	friend std::ostream & operator << (std::ostream &out, const location &l);	// Print location
	friend bool operator == (const location &rhs, const location &lhs);		// Check for equality.
	friend bool operator != (const location &rhs, const location &lhs);		// Check for inequality.
	friend location operator + (const location &rhs, const location &lhs);		// Sum locations
	friend location operator - (const location &rhs, const location &lhs);		// Subtract locations
	friend float find_euc(location rhs, location lhs);				// Find distance between locations
};

int find_euc(int x, int y, int h);	// Find euclidean distance between two points.
float find_euc(location rhs, location lhs);

#endif
