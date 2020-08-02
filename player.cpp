#include "include/player.h"
#include "include/combatant.h"
#include "include/roll.h"
#include "include/tools.h"

/* brief: 	Make move and then make attack.
	  	Virtual overloaded function from combatant.
   param: 	Pointer to node describing the player.
   returns:	0 if successful.
*/
int Player::take_turn(node* self)
{
	// Set target to start at attacker (origin).
	node * target = self;

	// Count other combatants in initiative list.
	int potential_targets = 0;
	while (target->next != self) 
	{
		potential_targets++;
		target = target->next;
	}

	// Reset target to origin.
	target = self;

	// Select random number between 1 and the number of enemies.
	int target_selector = (rand() % potential_targets+1);

	// Progress the head of the circular list ahead by target_selector.
	// i.e. 1 means go to next. Cannot go completely around the list.
	for (int i = 0; i < target_selector; i++)
	{
		target = target->next;
	}

	// Make attack against target. If attack kills them, result is set to dead. Else, alive.
	life_status result = self->player->make_attack(*(target->player));

	// If target is killed, remove them from the list and decrement the number of potential targets.
	if (result == dead)
	{
		remove_from_list(target);
		potential_targets--;
	}

	return 0;
}

/* brief: 	Roll attack against the target's AC, then roll damage.
	 	Virtual overloaded function from combatant.
   param: 	Address of target, called by reference.
   returns:	The status of the target.
*/
life_status Player::make_attack(combatant & target)
{
	std::string input;
	cout << endl << "Please give number of weapon to use: ";
	cin >> input;
	int wc = stoi(input);							// Weapon choice

	int attack_roll = make_roll(weapons[wc].getAttack());		// Initialise attack_roll to randomly generated value in dice range.

	cout << "Player ";

	// If attack roll is less than the target's AC, print message about missing.
	if (attack_roll < target.getAc()) {
		cout << name << " swung at " << target.getName() << " but missed!" << endl;
		return alive; // 0
	}
	// If attack roll is greater than the target's AC, roll damage and subtract that from the target's HP.
	// Then print message about hitting and dealing damage to stdout. Check target's status.
	else {
		int damage_roll = make_roll(weapons[wc].getDamage());
		cout << name << " hit " << target.getName() << " with their " << weapons[wc].getName() << " for " 
		     << damage_roll << " " << weapons[wc].getTypeStr() << " damage! ";
		life_status target_status = target.take_damage(damage_roll);
		if (target_status != dead)
			cout << target.getHp() << " HP remaining." << endl;
		return target_status;			// Return status of target.
	}
	
	return alive;				// Should not reach here.
}
