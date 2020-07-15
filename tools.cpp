#include "include/tools.h"
#include "include/csv_reader.h"
#include <vector>

using namespace std;

/* brief:	Declare CSV_Reader object, and load data from .csv file at filepath into a vector of vectors of strings.
   param:	filepath - A relative address pointing to the .csv file.
   returns:	A vector of vectors of strings containing contents of file.
*/
std::vector<std::vector<std::string>> load_file(std::string filepath)
{
	// Create an object of CSV_Reader	
	CSV_Reader reader(filepath);
	// Get the data from the CSV file
	std::vector<std::vector<std::string>> dataList = reader.getData();

	return dataList;
}

/* brief:	Print a vector of ints to the screen.
		Should be updated to work for vectors of any class.
   param:	input - A vector of ints.
   returns:	Nothing.
*/
void print_vector(vector <int> input)
{
	cout << "(";						// Prints a "(" for readability.
	
	// Iterate through vector, printing each value to screen.
	// If last value in vector, follow with ")". Otherwise, follow with ", ".
	for(auto i = input.begin(); i != input.end(); i++)
	{
		if (next(i) == input.end())
			cout << *i << ")" << endl;
		else
			cout << *i << ", ";
	}
}

/* brief: 	Adds a node to a linked list, after the input.
   param:	head - A pointer to the node which the new node should follow.
		initiative - The initiative value for the new node.
		player - The player value for the new node.
   returns:	Nothing.
*/
void add_to_list(node * head, int initiative, combatant player)
{
	node * entry = new node();			// Declare empty node, entry.

	entry->player = player;				// Add data
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

/* brief:	Remove a node from a linked list.
   param:	target - A pointer to the node to be removed.
   returns:	Nothing.
*/
void remove_from_list(node * target)
{
	// If not last node in list, point "prev" of subsequent node to previous node.
	if (target->next != NULL)
		target->next->prev = target->prev;
	// If not first node in list, point "next" of previous node to subsequent node.
	if (target->prev != NULL)
		target->prev->next = target->next;

	delete target;	// Free up memory.
}

/* brief:	Adds a node to a linked list, before the input.
   param:	head - A pointer to the node to be preceeded by the new node.
		new_player - Values for new player stats for the new node.
		new_initiative - Value for new initiative stat for the new node.
   returns:	Nothing.
*/
void change_head(node * head, combatant new_player, int new_initiative)
{
	combatant prev_player = head->player;			// Set prev_player to current head.
	int prev_roll = head->initiative;			// Set prev_roll to initiative value of current head.
				
	head->player = new_player;				// Set player value of current head to desired new value.
	head->initiative = new_initiative;			// Set initiative value of current head to desired new value.

	add_to_list(head, prev_roll, prev_player);		// Add node with previous values of current head after current head.
}

/* brief: Create a circular doubly linked list sorted by initiative.
   param: players - A vector containing all combatants involved.
   returns: 	Pointer to the head of the new circular doubly linked list.
*/
node * initiative_round(vector <combatant> players)
{
	node * head = new node();				// Declare new empty node for head of list.
	node * iterator = head;					// Declare new node for use as an iterator, pointing to head.

	head->player = players[0];				// Set player value for head to first value in vector.
	head->initiative = players[0].roll_initiative();	// Set initiative value for head to RNGed value.
	head->next = NULL;					// Point next towards empty space.
	head->prev = NULL;					// Point prev towards empty space.

	// Starting at next value in vector, append contents of vector onto each other.
	// Sort by initiative values.
	for (int i = 1; i < players.size(); i++)
	{
		node * entry = new node();			// Declare empty node to be added to previous node.
		node * tmp = new node();			// Declare empty node to be used as an iterator.

		tmp = head;					// Point iterator node to head.
		node * tmp2 = head;				// Declare second iterator node, point to head.

		int initiative_roll = players[i].roll_initiative();	// Set initiative to randomly generated value.

		// Keep iterating through list until you reach the end.
		while (tmp != NULL) {
			// If initiative is greater than that of tmp, add new node before it.
			if (initiative_roll > tmp->initiative) {
				change_head(tmp, players[i], initiative_roll);
				break;
			}
			// If current node is last in list, add new node after it.
			else if (tmp->next == NULL) {
				add_to_list(tmp, initiative_roll, players[i]);
				break;
			}
			// If initiative is less than that of tmp and tmp isn't the last, move to the next node.
			else {
				tmp = tmp->next;
			}
		}

		// Set tmp2 to the last node in the list.
		while (tmp2 != NULL)
		{
			tmp2 = tmp2->next;
		}

	}

	// Set iterator to last node in list.
	while (iterator->next != NULL)
	{
		iterator = iterator->next;
	}
	iterator->next = head;				// Stitch next value of last node to the first node.
	head->prev = iterator;				// Stitch prev value of first node to the last node.

	return head;
}
