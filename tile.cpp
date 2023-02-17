#include "tile.h"
#include "tools.h"
#include <iostream>
#include <exception>
#include <stdlib.h>
#include <sstream>


/* brief:	Constructor for creating rectangle shaped maps.
   param:	x - Width of map
		y - Height of map
   returns:	Nothing, as constructor
*/
Tile::Tile(int x, int y)
{
	// Assign values of links to nullptr, to be filled in later.
	// Could use simplifying?
	this->north = nullptr;
	this->east = nullptr;
	this->south = nullptr;
	this->west = nullptr;
	this->contents = new OutOfBoundsObject();
	this->coordinates = Location(0,0,0);
	this->origin = this;

	// Create first row
	Tile* x_iter = this;
	for (int i = 0; i < x; i++)
	{
		Tile* new_tile = new Tile();
		new_tile->origin = this->origin;
		new_tile->contents = new OutOfBoundsObject();
		new_tile->west = x_iter;			// All else will be nullptr by default.
		new_tile->setCoordinates(i+1,0,0);
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
		y_iter->setCoordinates(0,j,0);
		y_iter->contents = new OutOfBoundsObject();
		prev_y->south = y_iter;

		Tile* x_iter = y_iter;
		for (int i = 0; i < x; i++)
		{
			Tile* new_tile = new Tile();
			new_tile->origin = this->origin;
			new_tile->west = x_iter;
			new_tile->north = prev_y->east;
			if (prev_y->east != nullptr)
				prev_y->east->south = new_tile;
			new_tile->setCoordinates(i+1,j,0);

			if (i == x-1)
				new_tile->contents = new OutOfBoundsObject();

			if (j == y - 1)
				new_tile->contents = new OutOfBoundsObject();

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
	while (origin->north != nullptr)
	{
		origin = origin->north;
	}

	// Iterate to the right
	while (origin->west != nullptr)
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
	while (tile != nullptr)
	{
		if (tile->contents == nullptr)
			std::cout << "x";
		else if (tile->contents->getObjectType() == OutOfBounds)
			std::cout << "w";
		else
			std::cout << "p";
		tile = tile->east;
	}

	// New line
	std::cout << std::endl;

	// If there's a row below, call self recursively.
	if (south != nullptr)
		south->print_from();
}

/* brief:	Get a tile by x,y coordinates
   param:	x - x coordinate
		y - y coordinate
   returns:	The tile at (x,y)
*/
Tile* Tile::get(int x, int y)
{
	Tile * tile = origin;
	try
	{
		// Iterate down column.
		for (int j = 0; j < y; j++)
		{
			if (tile->south == nullptr)
				throw "Out of range!";
			tile = tile->south;
		}

		// Iterate across row
		for (int i = 0; i < x; i++)
		{	
			if (tile->east == nullptr)
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

/* brief:	Get a tile by Location
   param:	coordinates - coordinates of tile
   returns:	The tile at Location
*/
Tile* Tile::get(Location coordinates)
{
	Tile* tile = get(coordinates.getX(), coordinates.getY());

	return tile;
}

/* brief:	Get a tile from it's contents.
   param:	toFind - The object to find.
   returns:	The tile containing the object.
*/
Tile* Tile::get(Object* toFind)
{
	Tile* tile = get(toFind->getCoordinates());

	return tile;
}

/* brief:	Check if tile is occupied, and if not add contents.
   param:	Contents, the object to store in the tile.
   returns:	0 if contents succesfully changed,
		-1 if tile already contains something.
*/
int Tile::setContents(Object* Contents)
{
	try
	{
		// Don't want to accidentally clear occupied tile, so check if empty first.
		if (contents == nullptr)
		{
			if (Contents->getCoordinates() == this->coordinates)
			{
				this->contents = Contents;			// Assign contents to tile
				this->contents->setParent(this);		// Set parent as the current tile.
				return 0;
			}
			else
			{	
				std::stringstream err;
				std::cout << "test1" << endl;
				err << "Coordinates do not match! (" << Contents->getCoordinates() << " and " << this->coordinates << ")";
				std::cout << "test2" << endl;
				std::string str_err = err.str();
				throw str_err;
			}
		}
		// If tile occupied, return -1 and preserve original contents.
		else
		{
			throw std::string("Tile occupied!");
		}
	}
	catch (const std::string msg)
	{
		std::cerr << msg << std::endl;
		exit (EXIT_FAILURE);
	}
}

/* brief:	Accessor function for findMinimumPath without 0 as a magic number.
   param:	target - The tile you are measuring the distance to.
   returns:	The number of steps required.
*/
int Tile::findMinimumPath(Tile* target)
{
	return findMinimumPath(target, 0);
}

/* brief:	Returns the number of moves necessary to move to the target tile.
		Does not account for obstacles, improve to Djikstra's or A* later.
   param:	target - The tile you are measuring the distance to.
   		hops - The number of moves required to move to the target. Set to 0 when first calling.
   returns:	The number of steps required.
*/
int Tile::findMinimumPath(Tile* target, int hops)
{
	// Check if any of neighbouring tiles are the target.
	if (this->north == target)
		return 1;
	else if (this->east == target)
		return 1;
	else if (this->south == target)
		return 1;
	else if (this->west == target)
		return 1;
	
	// By default, set the minimum distance to an arbitarily large value. Will be overriden if a path is found.
	float north_dist = MAX_VALUE, east_dist = MAX_VALUE, south_dist = MAX_VALUE, west_dist = MAX_VALUE;
	if (this->north != nullptr)
		north_dist = find_euc(this->north->coordinates, target->coordinates);
	if (this->east != nullptr)
		east_dist = find_euc(this->east->coordinates, target->coordinates);
	if (this->south != nullptr)
		south_dist = find_euc(this->south->coordinates, target->coordinates);
	if (this->west != nullptr)
		west_dist = find_euc(this->west->coordinates, target->coordinates);

	// Check if any of the neighbouring tiles are closer to the target.
	float min_dist = north_dist;
	Tile* next_tile = this->north;
	if (east_dist < min_dist)
	{
		min_dist = east_dist;
		next_tile = this->east;
	}
	if (south_dist < min_dist)
	{
		min_dist = south_dist;
		next_tile = this->south;
	}
	if (west_dist < min_dist)
	{
		min_dist = west_dist;
		next_tile = this->west;
	}

	// Recursive function, check number of hops required from next closest step.
	hops = next_tile->findMinimumPath(target, hops) + 1;
	return hops;
}

/* brief: 	Find the closest point on the path to the target allowed by the speed.
   param:	target - The target you're trying to move to (but can't reach).
		moves - The maximum distance you're allowed to travel.
   returns:	The closest tile to the target you can reach.
*/
Tile* Tile::findMidPoint(Tile* target, int moves)
{
	// Check if any of neighbouring tiles are the target.
	if (this == target)
		return this;
	if (moves == 0)
		return this;
	
	// By default, set the minimum distance to an arbitarily large value. Will be overriden if a path is found.
	float north_dist = MAX_VALUE, east_dist = MAX_VALUE, south_dist = MAX_VALUE, west_dist = MAX_VALUE;
	if (this->north != nullptr)
		north_dist = find_euc(this->north->coordinates, target->coordinates);
	if (this->east != nullptr)
		east_dist = find_euc(this->east->coordinates, target->coordinates);
	if (this->south != nullptr)
		south_dist = find_euc(this->south->coordinates, target->coordinates);
	if (this->west != nullptr)
		west_dist = find_euc(this->west->coordinates, target->coordinates);

	// Check if any of the neighbouring tiles are closer to the target.
	float min_dist = north_dist;
	Tile* next_tile = this->north;
	if (east_dist < min_dist)
	{
		min_dist = east_dist;
		next_tile = this->east;
	}
	if (south_dist < min_dist)
	{
		min_dist = south_dist;
		next_tile = this->south;
	}
	if (west_dist < min_dist)
	{
		min_dist = west_dist;
		next_tile = this->west;
	}

	// Recursive function, keep going until remaining steps is zero or you reach the target.
	Tile* midpoint = next_tile->findMidPoint(target,--moves);
	return midpoint;
}

/* brief:	Return the width of the tile map.
   param:	None.
   returns:	The width of the tile map.
*/
int Tile::width()
{
	int i = 0;
	Tile *tile = this->origin;

	while (tile->getEast() != nullptr)
	{	
		tile = tile->getEast();
		i++;
	}

	return i;
}

/* brief:	Return the height of the tile map.
   param:	None.
   returns:	The height of the tile map.
*/
int Tile::height()
{
	int i = 0;
	Tile *tile = this->origin;

	while (tile->getSouth() != nullptr)
	{
		tile = tile->getSouth();
		i++;
	}

	return i;
}
