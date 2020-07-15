#include "combatant.h"
#include <vector>

// Node for used with linked list.
class node {
	public:
		// Data
		combatant player;
		int initiative;

		// Linked list
		struct node *prev;
		struct node *next;

		node() : player(combatant()), initiative(0), prev(NULL), next(NULL) {};
};

void print_vector(std::vector <int> input);	// Print vector as a list seperated by commas.
void run_encounter(std::vector <combatant> players); 	// Run a fight, taking a list of players as the input.
node * initiative_round(std::vector <combatant> players);
void add_to_list(node * head, int initiative, combatant player);
void change_head(node * head, combatant new_player, int new_initiative);
void remove_from_list(node * target);
