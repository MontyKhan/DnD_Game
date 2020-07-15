#include "include/csv_reader.h"
#include "include/combatant.h"
#include "include/tools.h"

using namespace std;

void run_encounter(std::vector <combatant> players)
{
	node * active_player = new node();
	int i = 0;

	active_player = initiative_round(players);

	cout << endl;

	int target_selector = (rand() % (players.size()+1)) - 1;


	while (active_player->initiative < active_player->prev->initiative)
	{
		cout << "List item " << i++ << ": " << active_player->player.getName() << endl;
		active_player = active_player->next;
	}

	while (active_player->next != active_player)
	{
		node * target = active_player->next;

		for (int i = 0; i < target_selector; i++)
		{
			target = target->next;
		}

		life_status result = active_player->player.make_attack(target->player);

		if (result == dead)
		{
			remove_from_list(target);
			target_selector--;
		}

		active_player = active_player->next;
	}

	cout << active_player->player.getName() << " wins!" << endl;
}

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
