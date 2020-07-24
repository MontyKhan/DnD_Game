#include <iostream>
#include "include/rapidxml/rapidxml_utils.hpp"
#include "include/combatant.h"

using namespace rapidxml;
using namespace std;

/* brief:	Parses through a xml style .enctr file.
   param:	filepath - A string containing the relative address of the .enctr file.
   returns: 	A vector of combatants, as described by the .enctr file.
*/
std::vector<combatant> interpret_nodes(const char* filepath)
{
	rapidxml::file<> xmlFile(filepath); // Default template is char
    	rapidxml::xml_document<> doc;
    	doc.parse<0>(xmlFile.data());

	xml_node<> *root = doc.first_node();

	std::vector<combatant> players;

	for (xml_node<> *child = root->first_node(); child; child = child->next_sibling())	// Monster
	{
		xml_node<> *grandchild = child->first_node();	// Name
		if (grandchild)					// If has name, check contents of monster
		{
			// interpret_node(child);
			combatant new_player = combatant(child);
			players.push_back(new_player);
		}
	}

	return players;
}
