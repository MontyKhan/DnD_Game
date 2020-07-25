#ifndef ROLL_H
#define ROLL_H

#include "weapon_type.h"
#include <string>

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

#endif
