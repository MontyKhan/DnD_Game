#include "include/tile.h"
#include "include/tools.h"
#include <iostream>
#include <exception>
#include <stdlib.h>


/* brief:	Constructor for creating rectangle shaped maps.
   param:	x - Width of map
		y - Height of map
   returns:	Nothing, as constructor
*/
Tile::Tile(int x, int y)
{
	// Assign values of links to NULL, to be filled in later.
	// Could use simplifying?
	this->north = NULL;
	this->east = NULL;
	this->south = NULL;
	this->west = NULL;
	this->contents = NULL;
	this->coordinates = location(0,0,0);

	// Create first row
	Tile* x_iter = this;
	for (int i = 1; i < x; i++)
	{
		Tile* new_tile = new Tile();
		new_tile->west = x_iter;			// All else will be NULL by default.
		new_tile->setCoordinates(i,0,0);
		x_iter->east = new_tile;
		x_iter = x_iter->east;
	}

	// Create subsequent rows
	Tile* prev_y = this;
	Tile* y_iter = new Tile();
	for (int j = 1; j < y; j++)
	{
		y_iter = new Tile();
		y_iter->north = prev_y;
		prev_y->south = y_iter;

		Tile* x_iter = y_iter;
		for (int i = 0; i < x; i++)
		{
			Tile* new_tile = new Tile();
			new_tile->setCoordinates(i,j,0);
			new_tile->west = x_iter;
			new_tile->north = prev_y->east;
			x_iter->east = new_tile;
			
			prev_y = prev_y->east;
			x_iter = x_iter->east;
		}

		prev_y = y_iter;
		y_iter = y_iter->south;
	}
}

/* brief:	Prints entire map to console, starting from origin.
   param:	None.
   returns:	Nothing, just prints to console.
*/
void Tile::print_map()
{
	// Point to current tile
	Tile* origin = this;

	// Iterate upwards
	while (origin->north != NULL)
	{
		origin = origin->north;
	}

	// Iterate to the right
	while (origin->west != NULL)
	{
		origin = origin->west;
	}

	// Print from origin
	origin->print_from();
}

/* brief:	Prints map to console, with each tile represented by an "x" char.
   param:	None
   returns:	Nothing, just prints to console.
*/ 
void Tile::print_from()
{
	// Point to first neighbour
	Tile* tile = this;

	// Iterate through row, print "x" for each tile.
	while (tile != NULL)
	{
		if (tile->contents == NULL)
			std::cout << "x";
		else
			std::cout << "p";
		tile = tile->east;
	}

	// New line
	std::cout << std::endl;

	// If there's a row below, call self recursively.
	if (south != NULL)
		south->print_from();
}

/* brief:	Get a tile by x,y coordinates
   param:	x - x coordinate
		y - y coordinate
   returns:	The tile at (x,y)
*/
Tile* Tile::get(int x, int y)
{
	Tile * tile = this;
	try
	{
		// Iterate down column.
		for (int j = 0; j < y; j++)
		{
			if (tile->south == NULL)
				throw "Out of range!";
			tile = tile->south;
		}

		// Iterate across row
		for (int i = 0; i < x; i++)
		{	
			if (tile->east == NULL)
				throw "Out of range!";
			tile = tile->east;
		}
	}
	// Check if out of range error thrown. If so, exit.
	catch (const char* msg)
	{
		std::cerr << msg << std::endl;
		exit (EXIT_FAILURE);
	}

	return tile;
}

/* brief:	Get a tile by location
   param:	coordinates - coordinates of tile
   returns:	The tile at location
*/
Tile* Tile::get(location coordinates)
{
	Tile* tile = get(coordinates.getX(), coordinates.getY());

	return tile;
}

/* brief:	Get a tile from it's contents.
   param:	toFind - The object to find.
   returns:	The tile containing the object.
*/
Tile* Tile::get(object* toFind)
{
	Tile* tile = get(toFind->getCoordinates());

	return tile;
}

/* brief:	Check if tile is occupied, and if not add contents.
   param:	Contents, the object to store in the tile.
   returns:	0 if contents succesfully changed,
		-1 if tile already contains something.
*/
int Tile::setContents(object* Contents)
{
	// Don't want to accidentally clear occupied tile, so check if empty first.
	if (contents == NULL)
	{
		std::cout << "test1" << endl;
		if (Contents->getCoordinates() == this->coordinates)
		{
			this->contents = Contents;			// Assign contents to tile
			this->contents->setParent(this);		// Set parent as the current tile.
			return 0;
		}
		else
		{
			cout << "error" << endl;
			return -1;
		}
	}
	// If tile occupied, return -1 and preserve original contents.
	else
	{
		return -1;
	}
}

int Tile::distanceTo(Tile* target)
{
	// Check if any of neighbouring tiles.
	if (this->north == target)
		return 1;
	else if (this->east == target)
		return 1;
	else if (this->south == target)
		return 1;
	else if (this->west == target)
		return 1;

	// Assign to arbitarily large value.
	int north_dist, east_dist, south_dist, west_dist = MAX_VALUE;
	// Recursive function call to find otherwise.
	std::cout << "North" << std::endl;
	if (north != NULL)
	{
		north_dist = north->distanceTo(target);
		if (north_dist != MAX_VALUE)
			north_dist++;
	}
	std::cout << "East" << std::endl;
	if (east != NULL)
	{
		east_dist = east->distanceTo(target);
		if (east_dist != MAX_VALUE)
			east_dist++;
	}
	std::cout << "South" << std::endl;
	if (south != NULL)
	{
		south_dist = south->distanceTo(target);
		if (south_dist != MAX_VALUE)
			south_dist++;
	}
#if 0
	std::cout << "West" << std::endl;
	if (west != NULL)
	{
		west_dist = west->distanceTo(target);
		if (west_dist != MAX_VALUE)
			west_dist++;
	}
#endif

	int min_dist = north_dist;
	if (min_dist > east_dist)
		min_dist = east_dist;
	if (min_dist > south_dist)
		min_dist = south_dist;
	if (min_dist > west_dist)
		min_dist = west_dist;

	return min_dist;
}
