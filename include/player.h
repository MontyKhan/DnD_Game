#ifndef PLAYER_H
#define PLAYER_H

#include "combatant.h"

using namespace std;

class Player : public combatant
{
	using combatant::combatant;

public:
	// Make move, then attack.
	int take_turn(node* self);
	// Deal damage to target, then check if they survive.
	life_status make_attack(object & target);
};

#endif
