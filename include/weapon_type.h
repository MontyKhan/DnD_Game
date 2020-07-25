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
	roll attack;
	roll damage;
	int range;
	type damage_type;
public:
	// Default constuctor, assume fists
	weapon_type() 
		: name(""), attack(roll(1,20,0)), damage(roll(1,4,0)), range(5), damage_type(bludgeoning) {};
	// Constructor for values recieved individually.
	weapon_type(std::string Name, roll Attack, roll Damage, int Range, type Type) 
		: name(Name), attack(Attack), damage(Damage), range(Range), damage_type(Type) {};
	// Constructor for xml node
	weapon_type(rapidxml::xml_node<> *root);

	// Setters/getters
	int setName(std::string Name) { name = Name; return 0; };
	std::string getName() { return name; };
	int setAttack(roll Attack) { attack = Attack; return 0; };
	roll getAttack() { return attack; };
	int setDamage(roll Damage) { damage = Damage; return 0; };
	roll getDamage() { return damage; };
	int setType(type Type) { damage_type = Type; return 0; };
	type getType() { return damage_type; };
	std::string getTypeStr();		// Defined in file.
};

#endif
