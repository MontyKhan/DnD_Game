#ifndef PLAYER_H
#define PLAYER_H

#include "combatant.h"

using namespace std;

class Player : public combatant
{
	using combatant::combatant;

public:
	life_status make_attack(combatant & target);
};

#endif
