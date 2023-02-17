#include "combatant.h"
#include "tools.h"
#include "load_file.h"
#include "weapon_type.h"
#include "rapidxml/rapidxml_print.hpp"
#include <sstream>

using namespace std;
using namespace rapidxml;

/* brief:	Constructor for weapon described by xml style node.
   param:	Node containing weapon stats.
   returns:	Nothing, as constructor.
*/
weapon_type::weapon_type(rapidxml::xml_node<> *root)
{
	for (xml_node<> *child = root->first_node(); child; child = child->next_sibling())	// Monster
	{
		xml_node<> *grandchild = child->first_node();	// Name

		std::string str_name;
		std::string str_value;

		// Convert name and value of child node to strings.
		node_to_str(str_name, str_value, child);


		// I wish switches could handle strings.
		if (str_name == "name")
		{
			name = str_value;
		}
		else if (str_name == "attack")
		{
			attack = Roll(1,20,stoi(str_value));
		}
		else if (str_name == "damage")
		{
			damage = Roll(str_value);
		}
		else if (str_name == "range")
		{
			range = stoi(str_value);
		}
		else if (str_name == "type")
		{
			damage_type = get_damage_type(str_value);
		}
	}
}

/* brief:	Return a string corresponding to the supplied damage type.
   param:	None
   returns:	A string matching up to the enum of the damage type.
*/
std::string weapon_type::getTypeStr()
{
	if (damage_type == acid)
		return "acid";
	else if (damage_type = bludgeoning)
		return "bludgeoning";
	else if (damage_type == cold)
		return "cold";
	else if (damage_type == fire)
		return "fire";
	else if (damage_type == force)
		return "force";
	else if (damage_type == lightning)
		return "lightning";
	else if (damage_type == necrotic)
		return "necrotic";
	else if (damage_type == piercing)
		return "piercing";
	else if (damage_type == poison)
		return "poison";
	else if (damage_type == psychic)
		return "psychic";
	else if (damage_type == radiant)
		return "radiant";
	else if (damage_type == slashing)
		return "slashing";
	else if (damage_type == thunder)
		return "thunder";
	else
		return "invalid";
}
