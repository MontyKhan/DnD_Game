#ifndef TOOLS_H
#define TOOLS_H

#include "combatant.h"
#include "monster.h"
#include "rapidxml/rapidxml_utils.hpp"
#include <vector>

// Node for used with linked list.
class node {
	public:
		// Data
		combatant* player;	// Statistics of monster.
		int initiative;		// Initiative roll for use in sorting.

		// Linked list
		struct node *prev;	// Previous node in list.
		struct node *next;	// Next node in list.

		// Constructor
		node() : player(new monster), initiative(0), prev(NULL), next(NULL) {};
};

void print_vector(std::vector <int> input);					// Print vector as a list seperated by commas.
void run_encounter(std::vector <combatant*> players); 				// Run a fight, taking a list of players as the input.
node * initiative_round(std::vector <combatant*> players);			// Have all players roll initiative, and return head of list.
void add_to_list(node * head, int initiative, combatant* player);		// Add new node to list after head.
void change_head(node * head, combatant* new_player, int new_initiative);	// Add new node to list before head.
void remove_from_list(node * target);						// Remove node from list.
void node_to_str(std::string &name, std::string &value, xml_node<> *node);	// Convert whatever nodes store their values in to string.
type get_damage_type(std::string str);						// Returns to string value of the enum's name

#endif
