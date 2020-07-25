#ifndef COMBATANT_H
#define COMBATANT_H

#include <iostream>
#include <ostream>
#include <string>
#include <vector>
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
enum type {acid, bludgeoning, cold, fire, force, lightning, necrotic, piercing, poison, psychic, radiant, slashing, thunder};


// May work better as typedef struct, review later.
class roll {
public:
	int num;		// Number of dice to roll.
	int dice;		// Size of dice to roll (e.g. d6)
	int mod;		// Modifier to roll, to be added on.

	// Constructors
	roll() :
		num(0), dice(0), mod(0) {};
	roll(int Num, int Dice, int Mod) :
		num(Num), dice(Dice), mod(Mod) {};
	roll(std::string input);

	// Friends
	friend std::ostream & operator << (std::ostream &out, const roll &r);
};

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

// Class for each combatant in an encounter
class combatant {
private:
	std::string name;
	int hp;
	int ac;
	int speed;
	roll init;
	roll attack;
	roll damage;
	std::vector<weapon_type> weapons;
	life_status status;

public:
	// Constructor for individual variables
	combatant(std::string Name, int HP, int AC, int Spd, int Init, int Attack, std::string Damage);
	// Constructor for vector of strings, as read from .csv.
	combatant(std::vector<std::string> line);
	// Constructor for xml node
	combatant(rapidxml::xml_node<> *node);
	// Default constructor
	combatant() 
		: name(""), hp(0), ac(0), speed(0), init(roll()), attack(roll()), damage(roll()), status(dead) {};

	// Interpret damage in form %d% + %.
	roll read_dam(std::string input);
	// Roll a dice
	int make_roll(roll x);
	// Roll initiative specifically
	int roll_initiative();
	// Roll both attack and damage against a target.
	life_status make_attack(combatant & target);
	// Roll both attack and damage against a target, supplying a weapon.
	life_status make_attack(weapon_type weapon, combatant & target);	// Pass by reference
	// Reduce hp by dam
	life_status take_damage(int dam);
	// Reduce hp by dam, specific to damage type.
	life_status take_damage(int dam, type damage_type);

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
