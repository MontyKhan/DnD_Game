#ifndef COMBATANT_H
#define COMBATANT_H

#include <iostream>
#include <ostream>
#include <string>
#include <vector>

#define NAME_VAR 	0
#define HP_VAR		1
#define AC_VAR		2
#define SPD_VAR		3
#define INIT_VAR	4
#define ATTACK_VAR	5
#define DAM_VAR		6

#if 0
typedef struct roll {
	int num;
	int dice;
	int mod;

	// Constructors
	roll() :
		num(0), dice(0), mod(0) {};
	roll(int Num, int Dice, int Mod) :
		num(Num), dice(Dice), mod(Mod) {};

	// Friends
	friend std::ostream& operator << (ostream &out, const roll &r);

} roll;
#endif

enum life_status {alive, death_1, death_2, dead};

// May work better as typedef struct, review later.
class roll {
public:
	int num;
	int dice;
	int mod;

	// Constructors
	roll() :
		num(0), dice(0), mod(0) {};
	roll(int Num, int Dice, int Mod) :
		num(Num), dice(Dice), mod(Mod) {};

	// Friends
	friend std::ostream & operator << (std::ostream &out, const roll &r);
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
	life_status status;

public:
	// Constructor for individual variables
	combatant(std::string Name, int HP, int AC, int Spd, int Init, int Attack, std::string Damage);
	// Constructor for vector of strings, as read from .csv.
	combatant(std::vector<std::string> line);
	// Default constructor
	combatant() : name(""), hp(0), ac(0), speed(0), init(roll()), attack(roll()), damage(roll()), status(dead) {};

	// Interpret damage in form %d% + %.
	roll read_dam(std::string input);
	// Roll a dice
	int make_roll(roll x);
	// Roll initiative specifically
	int roll_initiative();
	// Roll both attack and damage againt target
	life_status make_attack(combatant & target);	// Pass by reference
	// Reduce hp by dam
	life_status take_damage(int dam);

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
