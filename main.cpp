#include "include/csv_reader.h"
#include "include/combatant.h"
#include "include/tools.h"
#include "include/load_file.h"
#include "include/monster.h"
#include "include/tile.h"

using namespace std;

/* brief: 	Roll initiative for all players and monsters involved, then have each perform an action
	  	on their turn.
	  	Currently only supports melee attacks against random opponents.
   param: 	players - vector of pointers to players and monsters involved in encounter.
   returns: 	nothing
*/
void run_encounter(std::vector <combatant*> players, Tile *map)
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

	Tile *map = new Tile(125,35);

	// Range based for loop. Print stats of each player to screen.
	// Also adds players to map.
	for(combatant* D : players) {
		D->print_stats();
		Tile *tile = map->get(D->getCoordinates());
		tile->setContents(D);
	}

	map->print_map();

	std::cout << std::endl;
	Tile* test = map->get(players[0]);
	test->clearContents();
	map->print_map();

	// Loop for combat.
	run_encounter(players, map);

    	return 0;
};
