#include "include/tile.h"
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

	// Create x (tile) and y (new_line) iterators.
	Tile *new_line = this;
	Tile *tile;

	// Fill in map one line at a time.
	for (int i = 0; i < y; ++i)
	{
		tile = new_line;
		for (int j = 1; j < x; ++j)
		{
			tile->east = new Tile();
			tile->east->west = tile;
			if (tile->south != NULL)
			{
				tile->east->south = tile->south->east;
			}
			if (tile->north != NULL)
			{
				tile->east->north = tile->north->east;
			}
			tile = tile->east;
		}
		
		// If last line, don't add new south.
		// May be better solution for this.
		if (i < (y - 1))
		{
			new_line->south = new Tile();
			new_line = new_line->south;
		}
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
		contents = Contents;
		return 0;
	}
	// If tile occupied, return -1 and preserve original contents.
	else
	{
		return -1;
	}
}

void test_map()
{
	Tile* origin = new Tile(10,5);	// Segfault in here.

	origin->print_from();
	std::cout << std::endl;

	Tile* sample = origin->get(2,3);
	sample->setContents(new object());

	origin->print_from();
}
