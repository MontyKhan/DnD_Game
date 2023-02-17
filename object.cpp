#include "object.h"
#include "tile.h"

using namespace std;

/* brief:	Get a list of all neighbouring cells with no contents.
   param:	None.
   returns:	A vector containing the empty neighbouring cells.
*/
std::vector<Tile*> Object::getFreeNeighbours()
{
	// Vector to contain neighbouring vacant tiles.
	std::vector<Tile*> free_tiles;

	cout << "test_getFreeNeighbours_1" << endl;	
	// Check neighbouring tiles, clockwise starting at North.
	if (this->parent->north->contents == nullptr)
		free_tiles.push_back(this->parent->north);
	if (this->parent->north->east->contents == nullptr)
		free_tiles.push_back(this->parent->north->east);
	if (this->parent->east->contents == nullptr)
		free_tiles.push_back(this->parent->east);
	if (this->parent->east->south->contents == nullptr)
		free_tiles.push_back(this->parent->east->south);
	if (this->parent->south->contents == nullptr)
		free_tiles.push_back(this->parent->south);
	if (this->parent->south->west->contents == nullptr)
		free_tiles.push_back(this->parent->south->west);
	if (this->parent->west->contents == nullptr)
		free_tiles.push_back(this->parent->west);
	if (this->parent->west->north->contents == nullptr)
		free_tiles.push_back(this->parent->west->north);

	return free_tiles;
}

/* brief:	Get a list of all neighbouring cells with contents.
   param:	None.
   returns:	A vector containing the occupied neighbouring cells.
*/
std::vector<Tile*> Object::getOccupiedNeighbours()
{
	// Vector to contain neighbouring vacant tiles.
	std::vector<Tile*> occupied_tiles;
	
	// Check neighbouring tiles, clockwise starting at North.
	if ((this->parent->north->contents != nullptr) && (this->parent->north->contents->getStatus() == alive))
		occupied_tiles.push_back(this->parent->north);
	if ((this->parent->north->east->contents != nullptr) && (this->parent->north->east->contents->getStatus() == alive))
		occupied_tiles.push_back(this->parent->north->east);
	if ((this->parent->east->contents != nullptr) && (this->parent->east->contents->getStatus() == alive))
		occupied_tiles.push_back(this->parent->east);
	if ((this->parent->east->south->contents != nullptr) && (this->parent->east->south->contents->getStatus() == alive))
		occupied_tiles.push_back(this->parent->east->south);
	if ((this->parent->south->contents != nullptr) && (this->parent->south->contents->getStatus() == alive))
		occupied_tiles.push_back(this->parent->south);
	if ((this->parent->south->west->contents != nullptr) && (this->parent->south->west->contents->getStatus() == alive))
		occupied_tiles.push_back(this->parent->south->west);
	if ((this->parent->west->contents != nullptr) && (this->parent->west->contents->getStatus() == alive))
		occupied_tiles.push_back(this->parent->west);
	if ((this->parent->west->north->contents != nullptr) && (this->parent->west->north->contents->getStatus() == alive))
		occupied_tiles.push_back(this->parent->west->north);

	return occupied_tiles;
}

/* brief:	Print name and Location to console.
   param:	None.
   returns:	Nothing.
*/
void Object::print_stats()
{
	std::cout << "Name: " << this->name << std::endl;
	std::cout << "Coordinates: " << this->coordinates << std::endl;
}
