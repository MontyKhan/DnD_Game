#include "combatant.h"
#include "tools.h"
#include "load_file.h"
#include "pathfinding.h"
#include "rapidxml/rapidxml_print.hpp"
#include "display.h"
#include <sstream>
#include <algorithm>

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
	cout << "Initiative: " << init << endl;
	cout << "Coordinates: " << coordinates << endl;
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

/* brief:	Select opponent and make attack.
   param:	A pointer to the node containing the combatant making the attack.
   returns:	0 if successful.
*/
int combatant::take_turn(node* self)
{
	// Set target to start at attacker (origin).
	node * target = self;

	// Count other combatants in initiative list.
	int potential_targets = 0;
	while (target->next != self)
	{
		potential_targets++;
		target = target->next;
	}

	// Reset target to origin.
	target = self;

	vector<int> distances;

	// Progress the head of the circular list ahead by target_selector.
	// i.e. 1 means go to next. Cannot go completely around the list.
	// for (int i = 0; i < target_selector; i++)
	for (int i = 0; i < potential_targets; i++)
	{
		target = target->next;
		distances.push_back(this->coordinates.find_distance(target->player->getCoordinates()));
	}

	// Find minimum distance in list, i.e. closest opponent.
	target = self;
	auto min = *min_element(distances.begin(), distances.end());
	for (int D : distances)
	{
		target = target->next;
		if (D == min)
		{
			std::cout << "test_take_turn_1" << std::endl;
			std::cout << "target position: " << target->player->getCoordinates() << std::endl;
			std::vector<Tile*> free_cells = target->player->getFreeNeighbours();
			std::cout << "test_take_turn_2" << std::endl;
			int min_dist = MAX_VALUE;
			bool reached = false;

			if (free_cells.size() > 0)
			{
				Tile* new_location;
				for (Tile* T : free_cells)
				{
					std::cout << "T: " << T->getCoordinates();
					int dist = this->parent->findMinimumPath(T);
					std::cout << ", dist: " << dist << std::endl;
					if (dist < min_dist)
					{
						min_dist = dist;

						if (min_dist <= DIAGONAL_NEIGHBOUR)
						{
							new_location = this->parent;
							std::cout << "Already neighbour. Stay in place." << std::endl;
							reached = true;
						}
						if (min_dist <= this->speed)
						{
							new_location = T;
							reached = true;
						}
						else
							new_location = parent->findMidPoint(T, this->speed);
					}
				}

				std::cout << "new location: " << new_location->getCoordinates() << std::endl;

				// Select new tile to move to.
				moveTo(new_location);
			}
			else
			{
				std::cout << "staying in place." << std::endl;
			}

			// If next to target, attack. Otherwise, do nothing but print message.
			life_status result = alive;
			if (reached)
				// Make attack against target. If attack kills them, result is set to dead. Else, alive.
				result = self->player->make_attack(*(target->player));
			else
				cout << this->name << " moved to " << this->coordinates << "." << endl;

			// If target is killed, remove them from the list and decrement the number of potential targets.
			if (result == dead)
			{
				remove_from_list(target);
				potential_targets--;
			}
		break;
		}
	}

	return 1;
}

/* brief:	Roll attack. If it's greater than the target's AC, roll damage and subtract that from the target's HP. Print result.
		If it's less, just print miss to stdout.
   param:	target - Passed by reference. Combatant for the attacks to be made against.
   return:	status of target after attack, i.e. dead or alive.
*/
life_status combatant::make_attack(object & target)
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
		Virtual function, overwritten in Player.
   param:	weapon - Weapon with which attacks are made, using damage and attack rolls. Type checked.
		target - Passed by reference. Combatant for the attacks to be made against.
   return:	status of target after attack, i.e. dead or alive.
*/
life_status combatant::make_attack(weapon_type weapon, object & target)
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

/* brief:	Move to a specified tile.
   param:	The tile to be moved to.
   returns:	A 0 on a success.
*/
int combatant::moveTo(Tile* target)
{
	Tile* tmp = this->parent;
	this->coordinates = target->getCoordinates();
	if (target->setContents(this) == 0)
	{
		tmp->clearContents();
		sprites[this->name].setPosition(16.f+(32.f*float(this->coordinates.getX())),
						16.f+(32.f*float(this->coordinates.getY())));
	}

	return 0;
}
