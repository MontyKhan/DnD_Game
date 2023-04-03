#ifndef TOOLS_H
#define TOOLS_H

#include "combatant.h"
#include "monster.h"
#include "tile.h"
#include "rapidxml/rapidxml_utils.hpp"
#include <vector>

#define NEXT_IN_INITIATIVE_ORDER(subject, order)	(std::next(subject) != order->end() ? subject++ : order->begin())

void print_vector(std::vector <int> input);					  // Print vector as a list seperated by commas.
void node_to_str(std::string &name, std::string &value, xml_node<> *node);	 // Convert whatever nodes store their values in to string.
type get_damage_type(std::string str);						 // Returns to string value of the enum's name
std::vector<std::string> split_string(std::string& str, std::string delim);	// Populate vector with split string

extern Tile* map;

#endif
