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

class node;				// Forward declaration for take_turn(node* self) function.

// Class for each Combatant in an encounter
class Combatant : public Object {
protected:
	int hp;
	int ac;
	int speed;
	Roll init;
	std::vector<weapon_type> weapons;
	life_status status;

public:
	// Constructor for individual variables
	Combatant(std::string Name, int HP, int AC, int Spd, int Init, Location Coordinates, life_status Status);
	// Constructor for vector of strings, as read from .csv.
	Combatant(std::vector<std::string> line);
	// Constructor for xml node
	Combatant(rapidxml::xml_node<> *node);
	// Default constructor
	Combatant() 
		: hp(0), ac(0), speed(0), init(Roll()), Object(Location()), status(dead) {};

	// Roll a dice
	int make_roll(Roll x);
	// Roll initiative specifically
	int roll_initiative();
	// Move and then make attack
	virtual int take_turn();
	// Roll both attack and damage against a target.
	virtual life_status make_attack(Object & target);
	// Reduce hp by dam
	life_status take_damage(int dam);
	// Move to a tile next to another tile.
	virtual int moveTo(Tile* target);

	// Getter/Setters
	std::string getName() { return name; };				// Name
	int setName(std::string val) { name = val; return 0; }
	int getHp() { return hp; };					// HP
	int setHp(int val) { hp = val; return 0; };
	int getAc() { return ac; };					// AC
	int setAc(int val) { ac = val; return 0; };
	int getSpd() { return speed; };					// Speed
	int setSpd(int val) { speed = val; return 0; };
	Roll getInit() { return init; };				// Initiative
	int setInit(int val) { init = Roll(1,20,val); return 0; };
	life_status getStatus() { return status; };			// Status
	int setStatus(life_status val) { status = val; return 0; };
	int getInitiative() { return initiative; };
	int setInitiative(int init) { initiative = init; return 0; };

	// Debugging functions
	void print_stats();

	// Get object type
	object_type getObjectType() {return type_combatant; };
};

#endif
