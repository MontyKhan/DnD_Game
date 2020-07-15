#include "include/tools.h"
#include "include/csv_reader.h"
#include <vector>

using namespace std;

// Enter values from a .csv into a vector of vectors.
std::vector<std::vector<std::string>> load_file(std::string filepath)
{
	// Create an object of CSV_Reader	
	CSV_Reader reader(filepath);
	// Get the data from the CSV file
	std::vector<std::vector<std::string>> dataList = reader.getData();

	return dataList;
}

// Print a vector to the screen.
void print_vector(vector <int> input)
{
	cout << "(";
	
	for(auto i = input.begin(); i != input.end(); i++)
	{
		if (next(i) == input.end())
			cout << *i << ")" << endl;
		else
			cout << *i << ", ";
	}
}

// Add a node to a linked list
void add_to_list(node * head, int initiative, combatant player)
{
	node * entry = new node();

	entry->player = player;			// Add data
	entry->initiative = initiative;

	if (head->next != NULL) {
		node * tmp = new node();		// Declare new node
		tmp = head->next;			// Bump next node along
		entry->next = tmp;
		entry->prev = head;
		head->next = entry;			// Insert node in.
		tmp->prev = entry;			// Reattach next node.
	}
	else {
		head->next = entry;			// Attach node to end.
		entry->prev = head;
	}
}

void change_head(node * head, combatant new_player, int new_initiative)
{
	combatant prev_player = head->player;
	int prev_roll = head->initiative;
				
	head->player = new_player;
	head->initiative = new_initiative;

	add_to_list(head, prev_roll, prev_player);
}

// Make circular linked list sorted by initiative, taking a vector as an argument.
node * initiative_round(vector <combatant> players)
{
	node * head = new node();
	node * iterator = head;

	head->player = players[0];
	head->initiative = players[0].roll_initiative();
	head->next = NULL;
	head->prev = NULL;

	for (int i = 1; i < players.size(); i++)
	{
		node * entry = new node();
		node * tmp = new node();

		tmp = head;
		node * tmp2 = head;

		cout << endl;

		int initiative_roll = players[i].roll_initiative();

		while (tmp != NULL) {
			if (initiative_roll > tmp->initiative) {
				change_head(tmp, players[i], initiative_roll);
				break;
			}
			else if (tmp->next == NULL) {
				add_to_list(tmp, initiative_roll, players[i]);
				break;
			}
			else {
				tmp = tmp->next;
			}
		}

		while (tmp2 != NULL)
		{
			cout << tmp2->player.getName() << " " << tmp2->initiative << endl;
			tmp2 = tmp2->next;
		}

	}

	while (iterator->next != NULL)
	{
		iterator = iterator->next;
	}
	iterator->next = head;

	return head;
}
