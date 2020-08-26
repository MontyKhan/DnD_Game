#ifndef COMBATANT_H
#define COMBATANT_H

#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include "weapon_type.h"
#include "pathfinding.h"
#include "object.h"
#include "rapidxml/rapidxml_utils.hpp"

#define NAME_VAR 	0
#define HP_VAR		1
#define AC_VAR		2
#define SPD_VAR		3
#define INIT_VAR	4
#define ATTACK_VAR	5
#define DAM_VAR		6

using namespace rapidxml;

enum life_status {alive, death_1, death_2, dead};

class node;				// Forward declaration for take_turn(node* self) function.

// Class for each combatant in an encounter
class combatant : public object {
protected:
	std::string name;
	int hp;
	int ac;
	int speed;
	roll init;
	std::vector<weapon_type> weapons;
	life_status status;

public:
	// Constructor for individual variables
	combatant(std::string Name, int HP, int AC, int Spd, int Init, location Coordinates, life_status Status);
	// Constructor for vector of strings, as read from .csv.
	combatant(std::vector<std::string> line);
	// Constructor for xml node
	combatant(rapidxml::xml_node<> *node);
	// Default constructor
	combatant() 
		: name(""), hp(0), ac(0), speed(0), init(roll()), object(location()), status(dead) {};

	// Roll a dice
	int make_roll(roll x);
	// Roll initiative specifically
	int roll_initiative();
	// Move and then make attack
	virtual int take_turn(node* self);
	// Roll both attack and damage against a target.
	virtual life_status make_attack(combatant & target);
	// Roll both attack and damage against a target, supplying a weapon.
	life_status make_attack(weapon_type weapon, combatant & target);	// Pass by reference
	// Reduce hp by dam
	life_status take_damage(int dam);
	// Reduce hp by dam, specific to damage type.
	life_status take_damage(int dam, type damage_type);
	// Move to a tile next to another combatant, so they can attack.
	virtual int moveToFoe(combatant foe);

	// Getter/Setters
	std::string getName() { return name; };				// Name
	int setName(std::string val) { name = val; return 0; }
	int getHp() { return hp; };					// HP
	int setHp(int val) { hp = val; return 0; };
	int getAc() { return ac; };					// AC
	int setAc(int val) { ac = val; return 0; };
	int getSpd() { return speed; };					// Speed
	int setSpd(int val) { speed = val; return 0; };
	roll getInit() { return init; };				// Initiative
	int setInit(int val) { init = roll(1,20,val); return 0; };
	life_status getStatus() { return status; };			// Status
	int setStatus(life_status val) { status = val; return 0; };

	// Debugging functions
	void print_stats();
};

#endif
