#include "include/tile.h"
#include <iostream>


/* brief:	Constructor for creating rectangle shaped maps.
   param:	x - Width of map
		y - Height of map
   returns:	Nothing, as constructor
*/
Tile::Tile(int x, int y)
{
	// If only one more row requested, end it here.
	if (y == 1)
		south = NULL;
	else
	{
		// Recursive call to create bottom neighbour
		south = new Tile(x, y-1);
		
		// Connect east tile to neighbours, and vice versa.
		if (east != NULL)
		{
			south->east = east->south;
			if (east->south != NULL)
				east->south->west = south;
		}

		// Connect west tile to neighbours, and vice versa.
		if (west != NULL)
		{
			south->west = west->south;
			if (west->south != NULL)
				west->south->east = south;
		}

		// Connect new neighbour to self.
		south->north = this;
	}

	if (x == 1)
		east = NULL;
	else
	{
		// Recursive call to create right neighbour
		east = new Tile(x-1,y);

		// Connect new neighbour to self.
		east->west = this;

		// Connect north tile to neighbours, and vice versa.
		if (north != NULL)
		{
			east->north = north->east;
			if (north->east != NULL)
				north->east->south = east;
		}

		// Connect south tile to neighbours, and vice versa.
		if (south != NULL)
		{
			east->south = south->east;
			if (south->east != NULL)
				south->east->north = east;
		}	
	}
}
/* brief:	Prints map to console, with each tile represented by an "x" char.
   param:	None
   returns:	Nothing, just prints to console.
*/ 
void Tile::print_map()
{
	// Point to first neighbour
	Tile* neighbour = east;

	// Print x for origin tile.
	std::cout << "x";

	// Iterate through row, print "x" for each tile.
	while (neighbour != NULL)
	{
		std::cout << "x";
		neighbour = neighbour->east;
	}

	// New line
	std::cout << "\n";

	// If there's a row below, call self recursively.
	if (south != NULL)
		south->print_map();
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
