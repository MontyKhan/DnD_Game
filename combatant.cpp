#include "include/combatant.h"
#include "include/tools.h"
#include "include/load_file.h"
#include "include/rapidxml/rapidxml_print.hpp"
#include <sstream>

using namespace std;
using namespace rapidxml;


/* brief:	Constructor for taking variables individually.
   param:	Name - Combatant name as string.
		HP - Combatant max HP as int.
		AC - Combatant Armour Class as int.
		Spd - Combatant speed in feet as an int.
		Init - Initiative modifier as an int. Is converted into a roll equal to 1d20 + Init.
		Coordinates - 3D coordinates of combatant
		Status - life_status of combatant
   return:	Nothing, as constructor.
*/

combatant::combatant(std::string Name, int HP, int AC, int Spd, int Init, location Coordinates, life_status Status)
{
	name = Name;
	hp = HP;
	ac = AC;
	speed = Spd;
	init = roll(1,20,Init);
	coordinates = Coordinates;
	status = Status;
}

/* brief:	Constructor for reading variables from a vector of strings.
   param:	line - Stats in order of Name, HP, AC, Spd, Init as in above formats.
   return:	Nothing, as constructor.
*/
combatant::combatant(std::vector<std::string> line)
{
	name = line[NAME_VAR];				// Get name (string)
	hp = stoi(line[HP_VAR]);			// Get HP (int)
	ac = stoi(line[AC_VAR]);			// Get AC (int)
	speed = stoi(line[SPD_VAR]);			// Get speed (int)
	init = roll(1,20,stoi(line[INIT_VAR]));		// Create initiative roll
	coordinates = location();
	status = dead;
}

/* brief:	Constructor reading variables from an xml node.
   param:	*node - Pointer to an xml node containing values
   return:	Nothing, as constructor.
*/
combatant::combatant(xml_node<> *root)
{
	for (xml_node<> *child = root->first_node(); child; child = child->next_sibling())	// Monster
	{
		xml_node<> *grandchild = child->first_node();	// Name

		std::string str_name;
		std::string str_value;

		// Convert name and value of child node to strings.
		node_to_str(str_name, str_value, child);

		if (str_name == "weapon")					// If has grandchildren, weapon.
		{
			// interpret_node(child);
			//combatant new_player = combatant(child);
			//players.push_back(new_player);
			weapons.push_back(weapon_type(child));
		}
		else if (str_name == "coordinates")
		{
			coordinates = location(str_value);
		}
		else
		{
			// I wish switches could handle strings.
			if (str_name == "name")
			{
				name = str_value;
			}
			else if (str_name == "ac")
			{
				ac = stoi(str_value);
			}
			else if (str_name == "hp")
			{
				hp = stoi(str_value);
			}
			else if (str_name == "speed")
			{
				speed = stoi(str_value);
			}
			else if (str_name == "initiative")
			{
				init = roll(1,20,stoi(str_value));
			}
		}
	}
}

/* brief:	Print all stats of combatant to screen.
   param:	None.
   returns:	Nothing.
*/
void combatant::print_stats()
{
	cout << "Name: " << name << endl;
	cout << "HP: " << hp << endl;
	cout << "AC: " << ac << endl;
	cout << "Speed: " << speed << endl;
	cout << "Iniative: " << init << endl;
	cout << endl;
}

/* brief: 	Generate a random number as if rolled by a dice.
   param: 	roll value, containing the number of dice, the size of the dice and the modifier.
   returns: 	The result of the roll, plus the modifier.
*/
int combatant::make_roll(roll x)
{
	int damage = 0;					// Initialise damage to 0.
	vector <int> results;				// Declare empty vector of ints for containing results of each roll.

	// Roll each dice using rand(), then add to vector.
	// Each roll produces a value between 1 and x.dice (e.g. 1 - 6 for a d6).
	for (int i = 0; i < x.num; i++)
	{
		int val = rand() % x.dice + 1;
		results.push_back(val);
		damage += val;
	}

	// Disable for now, as level of complexity of current program too low.
	//if (x.num > 1)
	//	print_vector(results);	

	return damage + x.mod;
}

/* brief:	Roll initiative specifically. Accesses init from class.
   param:	None
   returns:	The result of the 1d20 + init roll.
*/
int combatant::roll_initiative()
{
	return make_roll(init);
}

/* brief:	Roll attack. If it's greater than the target's AC, roll damage and subtract that from the target's HP. Print result.
		If it's less, just print miss to stdout.
   param:	target - Passed by reference. Combatant for the attacks to be made against.
   return:	status of target after attack, i.e. dead or alive.
*/
life_status combatant::make_attack(combatant & target)
{
	int wc = 0;							// Weapon choice

	int attack_roll = make_roll(weapons[wc].getAttack());		// Initialise attack_roll to randomly generated value in dice range.

	// If attack roll is less than the target's AC, print message about missing.
	if (attack_roll < target.getAc()) {
		cout << name << " swung at " << target.getName() << " but missed!" << endl;
		return alive; // 0
	}
	// If attack roll is greater than the target's AC, roll damage and subtract that from the target's HP.
	// Then print message about hitting and dealing damage to stdout. Check target's status.
	else {
		int damage_roll = make_roll(weapons[wc].getDamage());
		cout << name << " hit " << target.getName() << " with their " << weapons[wc].getName() << " for " 
		     << damage_roll << " " << weapons[wc].getTypeStr() << " damage! ";
		life_status target_status = target.take_damage(damage_roll);
		if (target_status != dead)
			cout << target.getHp() << " HP remaining." << endl;
		return target_status;			// Return status of target.
	}
	
	return alive;				// Should not reach here.
}

/* brief:	Roll attack. If it's greater than the target's AC, roll damage and subtract that from the target's HP. Print result.
		If it's less, just print miss to stdout.
   param:	weapon - Weapon with which attacks are made, using damage and attack rolls. Type checked.
		target - Passed by reference. Combatant for the attacks to be made against.
   return:	status of target after attack, i.e. dead or alive.
*/
life_status combatant::make_attack(weapon_type weapon, combatant & target)
{
	int attack_roll = make_roll(weapon.getAttack());		// Initialise attack_roll to randomly generated value in dice range.

	// If attack roll is less than the target's AC, print message about missing.
	if (attack_roll < target.getAc()) {
		cout << name << " swung at " << target.getName() << " but missed!" << endl;
		return alive; // 0
	}
	// If attack roll is greater than the target's AC, roll damage and subtract that from the target's HP.
	// Then print message about hitting and dealing damage to stdout. Check target's status.
	else {
		int damage_roll = make_roll(weapon.getDamage());
		cout << name << " hit " << target.getName() << " for " << damage_roll << " damage! ";
		life_status target_status = target.take_damage(damage_roll);
		if (target_status != dead)
			cout << target.getHp() << " HP remaining." << endl;
		return target_status;			// Return status of target.
	}
	
	return alive;				// Should not reach here.
}

/* brief:	Take a value away from HP.
   param:	dam, the damage to be taken by the recipitent.
   returns:	The recipitent's status, i.e. dead or alive.
*/
life_status combatant::take_damage(int dam)
{
	// If damage is less than the target's HP, just reduce HP.
	if (dam < hp)
		hp -= dam;
	// If damage is greater than target's HP, set HP to zero and kill recipitent.
	else {
		hp = 0;
		status = dead;
		cout << name << " was downed!" << endl;
	}

	return status;
}

/* brief:	Take a value away from HP.
   param:	dam, the damage to be taken by the recipitent.
		damage_type, the type of the damage. Currently ignored.
   returns:	The recipitent's status, i.e. dead or alive.
*/
life_status combatant::take_damage(int dam, type damage_type)
{
	// If damage is less than the target's HP, just reduce HP.
	if (dam < hp)
		hp -= dam;
	// If damage is greater than target's HP, set HP to zero and kill recipitent.
	else {
		hp = 0;
		status = dead;
		cout << name << " was downed!" << endl;
	}

	return status;
}
