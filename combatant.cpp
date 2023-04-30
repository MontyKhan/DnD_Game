#include "combatant.h"
#include "tools.h"
#include "load_file.h"
#include "pathfinding.h"
#include "battlemap.h"
#include "rapidxml/rapidxml_print.hpp"
#include "display.h"
#include "weapon_type.h"
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
		Coordinates - 3D coordinates of Combatant
		Status - life_status_t of Combatant
   return:	Nothing, as constructor.
*/

Combatant::Combatant(std::string Name, int HP, int AC, int Spd, int Init, Location Coordinates, life_status_t Status, Faction Faction) :
	hp{ HP }, ac{ AC }, speed{ Spd }, init{ Roll(1, 20, Init) }, status{ Status }, faction{ Faction }
{
	name = Name;
	coordinates = Coordinates;
}

/* brief:	Constructor for reading variables from a vector of strings.
   param:	line - Stats in order of Name, HP, AC, Spd, Init as in above formats.
   return:	Nothing, as constructor.
*/
Combatant::Combatant(std::vector<std::string> line)
{
	name = line[NAME_VAR];				// Get name (string)
	hp = stoi(line[HP_VAR]);			// Get HP (int)
	ac = stoi(line[AC_VAR]);			// Get AC (int)
	speed = stoi(line[SPD_VAR]);			// Get speed (int)
	init = Roll(1,20,stoi(line[INIT_VAR]));		// Create initiative roll
	coordinates = Location();
	status = dead;
}

/* brief:	Constructor reading variables from an xml node.
   param:	*node - Pointer to an xml node containing values
   return:	Nothing, as constructor.
*/
Combatant::Combatant(xml_node<> *root) :
	hp{ 0 }, ac{ 0 }, speed{ 0 }, status{ dead }, faction{ Faction:: none }
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
			Weapon weapon = Weapon(child);
			weapon.setOwner(this);
			weapons.push_back(weapon);
		}
		else if (str_name == "coordinates")
		{
			coordinates = Location(str_value);
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

				if (hp > 0)
					status = alive;
			}
			else if (str_name == "speed")
			{
				speed = stoi(str_value);
			}
			else if (str_name == "initiative")
			{
				init = Roll(1,20,stoi(str_value));
			}
			else if (str_name == "faction")
			{
				if (factionLookup.find(str_value) != factionLookup.end())
					faction = factionLookup.find(str_value)->second;
				else
					faction = Faction::none;
			}
		}
	}
}

/* brief:	Print all stats of Combatant to screen.
   param:	None.
   returns:	Nothing.
*/
void Combatant::print_stats()
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
int Combatant::make_roll(Roll x)
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
int Combatant::roll_initiative()
{
	initiative = make_roll(init);
	return initiative;
}

/* brief:	Select opponent and make attack.
   returns:	0 if successful.
*/
int Combatant::take_turn()
{
	// Count other actors in initiative list.
	//std::list<Object *> *potential_targets = &(this->parentMap->initiative_order);
	std::list<Object *> potential_targets;
	std::copy_if(this->parentMap->initiative_order.begin(), this->parentMap->initiative_order.end(),
		std::back_inserter(potential_targets),
		[&](Object *actor) {return (actor != this) && (actor->getFaction() != this->faction); }
	);

	vector<int> distances;
	for (const auto &enemy : potential_targets)
		distances.push_back(this->coordinates.find_distance(enemy->getCoordinates()));

	// Find minimum distance in list, i.e. closest opponent.
	auto target = potential_targets.begin();

	auto min = *min_element(distances.begin(), distances.end());
	for (int D : distances)
	{
		if (D == min)
		{
			std::cout << "target position: " << (*target)->getCoordinates() << std::endl;
			std::vector<Tile*> free_cells = (*target)->getFreeNeighbours();
			int min_dist = MAX_VALUE;
			bool reached = false;

			if (free_cells.size() > 0)
			{
				Tile* new_Location = nullptr;
				for (Tile* T : free_cells)
				{
					std::cout << "T: " << T->getCoordinates();
					uint8_t weapon_range = weapons[0].getRange();
					// If weapon doesn't require you to be neighbouring, just get close enough to hit.
					std::vector<Tile *> visited = this->tile->findMinimumPath(T, weapon_range);
					int dist = visited.size();
					this->visitedTiles = std::move(visited);

					std::cout << ", dist: " << dist << std::endl;
					if (dist < min_dist)
					{
						min_dist = dist;

						if (min_dist <= weapon_range)
						{
							new_Location = this->tile;
							std::cout << "Already neighbour. Stay in place." << std::endl;
							reached = true;
						}
						if (min_dist <= this->speed)
						{
							new_Location = T;
							reached = true;
						}
						else
						{
							new_Location = tile->findMidPoint(T, this->speed);
							visited = this->tile->findMinimumPath(new_Location);
							this->visitedTiles = std::move(visited);
						}
					}
				}

				std::cout << "new Location: " << new_Location->getCoordinates() << std::endl;

				// Select new tile to move to.
				moveTo(new_Location);
			}
			else
			{
				std::cout << "staying in place." << std::endl;
			}

			// If next to target, attack. Otherwise, do nothing but print message.
			life_status_t result = alive;
			if (reached)
				// Make attack against target. If attack kills them, result is set to dead. Else, alive.
				result = this->make_attack(**target);
			else
				cout << this->name << " moved to " << this->coordinates << "." << endl;

		break;
		}
		else
		{
			if (std::next(target) != potential_targets.end())
				target++;
			else
				target = potential_targets.begin();
		}
	}

	return 1;
}

/* brief:	Roll attack. If it's greater than the target's AC, roll damage and subtract that from the target's HP. Print result.
		If it's less, just print miss to stdout.
   param:	target - Passed by reference. Combatant for the attacks to be made against.
   return:	status of target after attack, i.e. dead or alive.
*/
life_status_t Combatant::make_attack(Object & target)
{
	int wc = 0;							// Weapon choice

	return (life_status_t)weapons[wc].makeWeaponAttack(target);
}

/* brief:	Take a value away from HP.
   param:	dam, the damage to be taken by the recipitent.
   returns:	The recipitent's status, i.e. dead or alive.
*/
life_status_t Combatant::take_damage(int dam)
{
	// If damage is less than the target's HP, just reduce HP.
	if (dam < hp)
		hp -= dam;
	// If damage is greater than target's HP, set HP to zero and kill recipitent.
	else {
		hp = 0;
		status = dead;
		cout << name << " was downed!" << endl;

		auto corpse = find(this->parentMap->initiative_order.begin(), this->parentMap->initiative_order.end(), this);
		this->parentMap->initiative_order.erase(corpse);
		this->tile->clearContents();
	}

	return status;
}

/* brief:	Move to a specified tile.
   param:	The tile to be moved to.
   returns:	A 0 on a success.
*/
int Combatant::moveTo(Tile* target)
{
	Tile* tmp = this->tile;
	this->coordinates = target->getCoordinates();
	if (target->setContents(this) == 0)
	{
		tmp->clearContents();
	}

	return 0;
}
