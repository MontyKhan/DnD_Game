#include "battlemap.h"

BattleMap::BattleMap(uint8_t x, uint8_t y, std::vector<Object*> objects) :
	objects(objects)
{
	origin = new Tile(x, y);

	assignInitiativeOrder();
}

// Get specific tile by map reference, Location.
Tile* BattleMap::get(Location coordinates) {
	return origin->get(coordinates);
};
// Get specific tile by map reference, individual ints.
Tile* BattleMap::get(int x, int y) {
	return origin->get(x, y);
}
// Get specific tile by contents.
Tile* BattleMap::get(Object* toFind) {
	return origin->get(toFind);
}

/* brief: Create a circular doubly linked list sorted by initiative.
   param: players - A vector containing pointers to all monsters and players involved via downcasting.
   returns: 	Pointer to the head of the new circular doubly linked list.
*/
void BattleMap::assignInitiativeOrder()
{
	for (const auto& player : objects)
	{
		initiative_order.push_back(player);
		player->setBattlemap(this);
		player->roll_initiative();	// Set initiative value for head to RNGed value.
	}

	initiative_order.sort([](auto& first, auto& second) { return (first->getInitiative() > second->getInitiative()); });
}