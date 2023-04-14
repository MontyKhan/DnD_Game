#ifndef WEAPON_TYPE_H
#define WEAPON_TYPE_H

#include "roll.h"
#include "rapidxml/rapidxml_utils.hpp"

using namespace rapidxml;

class Object;

enum type {acid, bludgeoning, cold, fire, force, lightning, necrotic, piercing, poison, psychic, radiant, slashing, thunder};


// Class for each weapon wielded by Combatant
class Weapon {
private:
	std::string name;
	Roll attack;
	Roll damage;
	uint8_t range;
	type damage_type;
	Object *owner;
public:
	// Default constuctor, assume fists
	Weapon() 
		: name{ "" }, attack{ Roll{1, 20, 0} }, damage{ Roll{ 1, 4, 0 } }, range{ 1 }, damage_type{ bludgeoning }, owner{ nullptr } {};
	// Constructor for values recieved individually.
	Weapon(std::string Name, Roll Attack, Roll Damage, uint8_t Range, type Type, Object *Owner = nullptr) 
		: name{ Name }, attack{ Attack }, damage{ Damage }, range{ Range }, damage_type{ Type }, owner{ Owner } {};
	// Constructor for xml node
	Weapon(rapidxml::xml_node<> *root);

	// Attack target
	uint32_t makeWeaponAttack(Object &target);

	// Setters/getters
	int setName(std::string Name) { name = Name; return 0; };
	std::string getName() { return name; };
	int setAttack(Roll Attack) { attack = Attack; return 0; };
	Roll getAttack() { return attack; };
	int setDamage(Roll Damage) { damage = Damage; return 0; };
	Roll getDamage() { return damage; };
	uint8_t setRange(uint8_t Range) { range = Range; return 0; };
	uint8_t getRange() { return range; };
	int setType(type Type) { damage_type = Type; return 0; };
	type getType() { return damage_type; };
	std::string getTypeStr();		// Defined in file.
	int setOwner(Object *Owner) { owner = Owner; return 0; };
	Object *getOwner() { return owner; };
};

#endif
