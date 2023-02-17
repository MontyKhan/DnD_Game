#ifndef WEAPON_TYPE_H
#define WEAPON_TYPE_H

#include "roll.h"
#include "rapidxml/rapidxml_utils.hpp"

using namespace rapidxml;

enum type {acid, bludgeoning, cold, fire, force, lightning, necrotic, piercing, poison, psychic, radiant, slashing, thunder};


// Class for each weapon wielded by combatant
class weapon_type {
private:
	std::string name;
	Roll attack;
	Roll damage;
	int range;
	type damage_type;
public:
	// Default constuctor, assume fists
	weapon_type() 
		: name(""), attack(Roll(1,20,0)), damage(Roll(1,4,0)), range(5), damage_type(bludgeoning) {};
	// Constructor for values recieved individually.
	weapon_type(std::string Name, Roll Attack, Roll Damage, int Range, type Type) 
		: name(Name), attack(Attack), damage(Damage), range(Range), damage_type(Type) {};
	// Constructor for xml node
	weapon_type(rapidxml::xml_node<> *root);

	// Setters/getters
	int setName(std::string Name) { name = Name; return 0; };
	std::string getName() { return name; };
	int setAttack(Roll Attack) { attack = Attack; return 0; };
	Roll getAttack() { return attack; };
	int setDamage(Roll Damage) { damage = Damage; return 0; };
	Roll getDamage() { return damage; };
	int setType(type Type) { damage_type = Type; return 0; };
	type getType() { return damage_type; };
	std::string getTypeStr();		// Defined in file.
};

#endif
