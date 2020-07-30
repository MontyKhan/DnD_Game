#include "include/player.h"
#include "include/combatant.h"
#include "include/roll.h"

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
