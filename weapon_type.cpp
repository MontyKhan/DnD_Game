#include "combatant.h"
#include "tools.h"
#include "load_file.h"
#include "weapon_type.h"
#include "pathfinding.h"
#include "object.h"
#include "rapidxml/rapidxml_print.hpp"
#include <sstream>

using namespace std;
using namespace rapidxml;

/* brief:	Constructor for weapon described by xml style node.
   param:	Node containing weapon stats.
   returns:	Nothing, as constructor.
*/
Weapon::Weapon(rapidxml::xml_node<> *root)
	: name{ "" }, attack{ Roll{1, 20, 0} }, damage{ Roll{ 1, 4, 0 } }, range{ 1 }, damage_type{ bludgeoning }, owner{ nullptr }
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
std::string Weapon::getTypeStr()
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

uint32_t Weapon::makeWeaponAttack(Object &target)
{
	uint8_t distance_to_target = find_euc(owner->getCoordinates(), target.getCoordinates());
	if (range < distance_to_target) {
		cout << target.getName() << " out of range of " << owner->getName() << "'s " << name << "!" << endl;
		return alive; // 0
	}

	int attack_roll = owner->make_roll(attack);		// Initialise attack_roll to randomly generated value in dice range.

	// If attack roll is less than the target's AC, print message about missing.
	if (attack_roll < target.getAc()) {
		cout << name << " swung at " << target.getName() << " but missed!" << endl;
		return alive; // 0
	}
	// If attack roll is greater than the target's AC, roll damage and subtract that from the target's HP.
	// Then print message about hitting and dealing damage to stdout. Check target's status.
	/* else */ {
		int damage_roll = owner->make_roll(damage);
		cout << name << " hit " << target.getName() << " with their " << name << " for "
			<< damage_roll << " " << getTypeStr() << " damage! ";
		life_status_t target_status = target.take_damage(damage_roll);
		if (target_status != dead)
			cout << target.getHp() << " HP remaining." << endl;
		return target_status;			// Return status of target.
	}
}