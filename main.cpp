#include "include/csv_reader.h"
#include "include/combatant.h"
#include "include/tools.h"
#include "include/load_file.h"
#include "include/monster.h"

using namespace std;

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

	int potential_targets = players.size() - 1;	// Calculate number of available targets. Vector size minus self.

	// Repeat until only one player is left.
	while (active_player->next != active_player)
	{
		// Set target to start at attacker (origin).
		node * target = active_player;

		// Select random number between 1 and the number of enemies.
		int target_selector = (rand() % potential_targets+1);

		// Progress the head of the circular list ahead by target_selector.
		// i.e. 1 means go to next. Cannot go completely around the list.
		for (int i = 0; i < target_selector; i++)
		{
			target = target->next;
		}

		// Make attack against target. If attack kills them, result is set to dead. Else, alive.
		life_status result = active_player->player->make_attack(*(target->player));

		// If target is killed, remove them from the list and decrement the number of potential targets.
		if (result == dead)
		{
			remove_from_list(target);
			potential_targets--;
		}

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

	// Range based for loop. Print stats of each player to screen.
	for(combatant* D : players) {
		D->print_stats();
	}

	// Loop for combat.
	run_encounter(players);

    	return 0;
};
