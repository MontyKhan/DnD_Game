#include <iostream>
#include "include/rapidxml/rapidxml_utils.hpp"
#include "include/combatant.h"
#include "include/monster.h"
#include "include/player.h"
#include "include/tools.h"

using namespace rapidxml;
using namespace std;

/* brief:	Parses through a xml style .enctr file.
   param:	filepath - A string containing the relative address of the .enctr file.
   returns: 	A vector of pointers to combatants, as described by the .enctr file.
		Uses downcasting to actually contain Players and monsters.
*/
std::vector<object*> interpret_nodes(const char* filepath)
{
	rapidxml::file<> xmlFile(filepath); // Default template is char
    	rapidxml::xml_document<> doc;
    	doc.parse<0>(xmlFile.data());

	xml_node<> *root = doc.first_node();

	std::vector<object*> combatants;	// Stores both monsters and players through downcasting.

	for (xml_node<> *child = root->first_node(); child; child = child->next_sibling())	// Monster
	{
		std::string str_name;
		std::string str_value;
		node_to_str(str_name,str_value,child);
		
		if (str_name == "monster")					// AI controlled monster
		{
			monster* new_monster = new monster(child);
			new_monster->setStatus(alive);
			combatants.push_back(new_monster);
		}
		else if (str_name == "player")					// Human controlled player
		{
			Player* new_player = new Player(child);
			new_player->setStatus(alive);
			combatants.push_back(new_player);
		}
	}

	return combatants;
}
