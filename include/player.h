#ifndef PLAYER_H
#define PLAYER_H

#include "combatant.h"

using namespace std;

class Player : public Combatant
{
	using Combatant::Combatant;

public:
	// Make move, then attack.
	int take_turn();
	// Deal damage to target, then check if they survive.
	life_status make_attack(Object & target);

	// Get object type
	object_type getObjectType() {return type_player; };
};

#endif
