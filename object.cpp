#include "include/object.h"
#include "include/tile.h"

/* brief:	Get a list of all neighbouring cells with no contents.
   param:	None.
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

/* brief:	Get a list of all neighbouring cells with contents.
   param:	None.
   returns:	A vector containing the occupied neighbouring cells.
*/
std::vector<Tile*> object::getOccupiedNeighbours()
{
	// Vector to contain neighbouring vacant tiles.
	std::vector<Tile*> occupied_tiles;
	
	// Check neighbouring tiles, clockwise starting at North.
	if ((this->parent->north->contents != NULL) && (this->parent->north->contents->getStatus() == alive))
		occupied_tiles.push_back(this->parent->north);
	if ((this->parent->north->east->contents != NULL) && (this->parent->north->east->contents->getStatus() == alive))
		occupied_tiles.push_back(this->parent->north->east);
	if ((this->parent->east->contents != NULL) && (this->parent->east->contents->getStatus() == alive))
		occupied_tiles.push_back(this->parent->east);
	if ((this->parent->east->south->contents != NULL) && (this->parent->east->south->contents->getStatus() == alive))
		occupied_tiles.push_back(this->parent->east->south);
	if ((this->parent->south->contents != NULL) && (this->parent->south->contents->getStatus() == alive))
		occupied_tiles.push_back(this->parent->south);
	if ((this->parent->south->west->contents != NULL) && (this->parent->south->west->contents->getStatus() == alive))
		occupied_tiles.push_back(this->parent->south->west);
	if ((this->parent->west->contents != NULL) && (this->parent->west->contents->getStatus() == alive))
		occupied_tiles.push_back(this->parent->west);
	if ((this->parent->west->north->contents != NULL) && (this->parent->west->north->contents->getStatus() == alive))
		occupied_tiles.push_back(this->parent->west->north);

	return occupied_tiles;
}

/* brief:	Print name and location to console.
   param:	None.
   returns:	Nothing.
*/
void object::print_stats()
{
	std::cout << "Name: " << this->name << std::endl;
	std::cout << "Coordinates: " << this->coordinates << std::endl;
}
