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

		node() : player(combatant()), initiative(0) {};
};

void print_vector(std::vector <int> input);	// Print vector as a list seperated by commas.
void run_encounter(std::vector <combatant> players); 	// Run a fight, taking a list of players as the input.
