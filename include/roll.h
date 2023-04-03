#ifndef ROLL_H
#define ROLL_H

#include "weapon_type.h"
#include <string>

// May work better as typedef struct, review later.
class Roll {
public:
	int num;		// Number of dice to roll.
	int dice;		// Size of dice to roll (e.g. d6)
	int mod;		// Modifier to roll, to be added on.

	// Constructors
	Roll() :
		num(0), dice(0), mod(0) {};
	Roll(int Num, int Dice, int Mod) :
		num(Num), dice(Dice), mod(Mod) {};
	Roll(std::string input);

	// Friends
	friend std::ostream & operator << (std::ostream &out, const Roll &r);
};

#endif
