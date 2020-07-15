#include "include/csv_reader.h"
#include "include/combatant.h"
#include "include/tools.h"

using namespace std;

/* brief: 	Roll initiative for all players and monsters involved, then have each perform an action
	  	on their turn.
	  	Currently only supports melee attacks against random opponents.
   param: 	players - vector of players and monsters involved in encounter.
   returns: 	nothing
*/
void run_encounter(std::vector <combatant> players)
{
	node * active_player = new node();		// Create initialisation node for players.
	int i = 0;					// Initialise counter to 0.

	active_player = initiative_round(players);	// Create circular list of players sorted by intiative. Point active_player at head.

	cout << endl;					// Add line break for readability.

	int potential_targets = players.size() - 1;	// Calculate number of available targets. Vector size minus self.

	// Repeat until only one player is left.
	while (active_player->next != active_player)
	{
		node * target = active_player;		// Set target to start at attacker (origin).

		// int target_selector = (rand() % potential_targets+1) - 1;
		int target_selector = (rand() % potential_targets+1);

		for (int i = 0; i < target_selector; i++)
		{
			target = target->next;
		}

		life_status result = active_player->player.make_attack(target->player);

		if (result == dead)
		{
			remove_from_list(target);
			potential_targets--;
		}

		active_player = active_player->next;
	}

	cout << active_player->player.getName() << " wins!" << endl;
}

/* brief: 	main function. Loads players and monsters from .csv file with hardcoded address.
	  	Then prints each to screen, and runs an encounter with them.
   param: 	none
   returns: 	0
*/
int main() {
	srand(time(NULL));	// Generate random seed.

	std::vector<combatant> players; 		// Create vector of characters

	std::string filepath = "./stats/encounter1.csv";

	std::vector<std::vector<std::string>> dataList = load_file(filepath);

    	// Print the content of row by row on screen
    	// for(std::vector<std::string> vec : dataList)
	for (int i = 0; i < dataList.size(); i++)
    	{
		players.push_back(combatant(dataList[i]));
		cout << players[i].roll_initiative() << endl;	
    	}

	for(combatant D : players) {
		D.print_stats();
	}

	run_encounter(players);

    	return 0;
};
