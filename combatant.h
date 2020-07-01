#include <iostream>
#include <string>
#include <vector>

typedef struct roll {
	int num;
	int dice;
	int mod;
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
	combatant(std::string Name, int HP, int AC, int Spd, int Init, std::string Attack, std::string Damage);
	// Constructor for vector of strings, as read from .csv.
	combatant(std::vector<std::string> line);

	// Interpret damage in form %d% + %.
	roll read_dam(std::string input);
};
