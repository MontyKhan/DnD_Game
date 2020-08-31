#include "include/object.h"
#include "include/tile.h"

/* brief:	Get a list of all neighbouring cells with no contents.
   params:	None.
   returns:	A vector containing the empty neighbouring cells.
*/
std::vector<Tile*> object::getFreeNeighbours()
{
	// Vector to contain neighbouring vacant tiles.
	std::vector<Tile*> free_tiles;
	
	// Check neighbouring tiles, clockwise starting at North.
	if (this->parent->north->contents == NULL)
		free_tiles.push_back(this->parent->north);
	if (this->parent->north->east->contents == NULL)
		free_tiles.push_back(this->parent->north->east);
	if (this->parent->east->contents == NULL)
		free_tiles.push_back(this->parent->east);
	if (this->parent->east->south->contents == NULL)
		free_tiles.push_back(this->parent->east->south);
	if (this->parent->south->contents == NULL)
		free_tiles.push_back(this->parent->south);
	if (this->parent->south->west->contents == NULL)
		free_tiles.push_back(this->parent->south->west);
	if (this->parent->west->contents == NULL)
		free_tiles.push_back(this->parent->west);
	if (this->parent->west->north->contents == NULL)
		free_tiles.push_back(this->parent->west->north);

	return free_tiles;
}
