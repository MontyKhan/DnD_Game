#include <iostream>
#include <string>
#include <vector>

#define NAME_VAR 	0
#define HP_VAR		1
#define AC_VAR		2
#define SPD_VAR		3
#define INIT_VAR	4
#define ATTACK_VAR	5
#define DAM_VAR		6

typedef struct roll {
	int num;
	int dice;
	int mod;

	// Constructors
	roll() :
		num(0), dice(0), mod(0) {};
	roll(int Num, int Dice, int Mod) :
		num(Num), dice(Dice), mod(Mod) {};
} roll;

// Class for each combatant in an encounter
class combatant {
private:
	std::string name;
	int hp;
	int ac;
	int speed;
	int init;
	roll attack;
	roll damage;

public:
	// Constructor for individual variables
	combatant(std::string Name, int HP, int AC, int Spd, int Init, int Attack, std::string Damage);
	// Constructor for vector of strings, as read from .csv.
	combatant(std::vector<std::string> line);

	// Interpret damage in form %d% + %.
	roll read_dam(std::string input);
};
