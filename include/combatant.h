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
	int init;
	roll attack;
	roll damage;
	life_status status;

public:
	// Constructor for individual variables
	combatant(std::string Name, int HP, int AC, int Spd, int Init, int Attack, std::string Damage);
	// Constructor for vector of strings, as read from .csv.
	combatant(std::vector<std::string> line);

	// Interpret damage in form %d% + %.
	roll read_dam(std::string input);
	// Roll a dice
	int make_roll(roll x);
	// Roll both attack and damage
	void take_action();
	// Reduce hp by dam
	int take_damage(int dam);

	// Debugging functions
	void print_stats();
};

void print_vector(std::vector <int> input);
