#include "object.h"
#include "tile.h"

using namespace std;

std::vector<Tile *>Object::getNeighbours()
{
	// Vector to contain neighbouring vacant tiles.
	std::vector<Tile *> tiles;
	tiles.resize(8);

	tiles[eNorth] = this->tile->getNorth();
	tiles[eNorthEast] = tiles[eNorth] ? tiles[eNorth]->getEast() : nullptr;
	tiles[eEast] = this->tile->getEast();
	tiles[eSouthEast] = tiles[eEast] ? tiles[eEast]->getSouth() : nullptr;
	tiles[eSouth] = this->tile->getSouth();
	tiles[eSouthWest] = tiles[eSouth] ? tiles[eSouth]->getWest() : nullptr;
	tiles[eWest] = this->tile->getWest();
	tiles[eNorthWest] = tiles[eWest] ? tiles[eWest]->getNorth() : nullptr;

	return tiles;
}

/* brief:	Get a list of all neighbouring cells with no contents.
   param:	None.
   returns:	A vector containing the empty neighbouring cells.
*/
std::vector<Tile*> Object::getFreeNeighbours()
{
	// Vector to contain neighbouring vacant tiles.
	std::vector<Tile*> free_tiles;
	std::vector<Tile *> tiles = this->getNeighbours();

	cout << "test_getFreeNeighbours_1" << endl;	
	// Check neighbouring tiles, clockwise starting at North.
	for (auto const &neighbour : tiles)
	{
		if (neighbour && neighbour->getContents() == nullptr)
			free_tiles.push_back(neighbour);
	}
	
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
	std::vector<Tile *> tiles = this->getNeighbours();

	cout << "test_getFreeNeighbours_1" << endl;
	// Check neighbouring tiles, clockwise starting at North.
	for (auto const &neighbour : tiles)
	{
		if (neighbour && neighbour->getContents() != nullptr)
			occupied_tiles.push_back(neighbour);
	}

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
