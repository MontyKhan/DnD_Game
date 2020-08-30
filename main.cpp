#include "include/csv_reader.h"
#include "include/combatant.h"
#include "include/tools.h"
#include "include/load_file.h"
#include "include/monster.h"
#include "include/tile.h"

using namespace std;

Tile *map;

/* brief: 	Roll initiative for all players and monsters involved, then have each perform an action
	  	on their turn.
	  	Currently only supports melee attacks against random opponents.
   param: 	players - vector of pointers to players and monsters involved in encounter.
   returns: 	nothing
*/
void run_encounter(std::vector <combatant*> players)
{
	node * active_player = new node();		// Create initialisation node for players.
	int i = 0;					// Initialise counter to 0.

	active_player = initiative_round(players);	// Create circular list of players sorted by intiative. Point active_player at head.

	cout << endl;					// Add line break for readability.

	// Repeat until only one player is left.
	while (active_player->next != active_player)
	{
		// Make move and take attack
		active_player->player->take_turn(active_player);

		// Progress iterator node to the next one.
		active_player = active_player->next;
	}

	// Debug code. State last fighter standing.
	cout << active_player->player->getName() << " wins!" << endl;
}

/* brief: 	main function. Loads players and monsters from .csv file with hardcoded address.
	  	Then prints each to screen, and runs an encounter with them.
   param: 	none
   returns: 	0
*/
int main() {

	srand(time(NULL));							// Generate random seed.

	std::vector<combatant*> players; 					// Create vector of players and monsters.

	players = interpret_nodes("./stats/encounter1.enctr");

	map = new Tile(125,35);

	// Range based for loop. Print stats of each player to screen.
	// Also adds players to map.
	for(combatant* C : players) {
		C->print_stats();
		Tile *tile = map->get(C->getCoordinates());
		tile->setContents(C);
	}

	map->print_map();

	std::cout << std::endl;

	Tile* test_map = new Tile(4,4);

	test_map->print_map();

	Tile* test1 = test_map->get(0,0);
	std::cout << "test1: " << test1->getEast()->getCoordinates() << std::endl;
	Tile* test2 = test_map->get(0,2);
	std::cout << "test2: " << test2->getCoordinates() << std::endl;

	std::cout << std::endl;

	test1->print_map();

	std::cout << std::endl;

	std::cout << "distance: " << test1->findMinimumPath(test2, 0) << endl;

	// Loop for combat.
	run_encounter(players);

	delete(map);

    	return 0;
};
