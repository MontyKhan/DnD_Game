#include "object.h"
#include "tile.h"

using namespace std;

std::vector<Tile *>Object::getNeighbours()
{
	return (tile ? tile->getNeighbours() : std::vector<Tile*>());
}

/* brief:	Get a list of all neighbouring cells with no contents.
   param:	None.
   returns:	A vector containing the empty neighbouring cells.
*/
std::vector<Tile*> Object::getFreeNeighbours()
{
	return (tile ? tile->getFreeNeighbours() : std::vector<Tile *>());
}

/* brief:	Get a list of all neighbouring cells with contents.
   param:	None.
   returns:	A vector containing the occupied neighbouring cells.
*/
std::vector<Tile*> Object::getOccupiedNeighbours()
{
	return (tile ? tile->getOccupiedNeighbours() : std::vector<Tile *>());
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