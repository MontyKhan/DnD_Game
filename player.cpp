#include "player.h"
#include "combatant.h"
#include "roll.h"
#include "tools.h"

/* brief: 	Make move and then make attack against specified target.
	  		Virtual overloaded function from Combatant.
   returns:	0 if successful.
*/
int Player::take_turn()
{
	cout << "Currently at: " << this->coordinates << endl;
#if 0
	Location new_Location = Location();
	bool Location_set = false;
	int turn_finished = 0;

	sf::Event event;

	while (Location_set == false)
	{
		//if (this->parentWindow->pollEvent(event))
		{
			if (event.type == sf::Event::MouseButtonPressed)
			{
				new_Location.setX(int(event.mouseButton.x/32.f));
				new_Location.setY(int(event.mouseButton.y/32.f));
				cout << "x: " << event.mouseButton.x/32.f << ", y: " << event.mouseButton.y/32.f << endl;
				Location_set = true;
				turn_finished = 1;
			}
		}
	}

	//Location new_Location = this->coordinates + move_vector;
	if (new_Location != this->coordinates)
	{
		Tile* new_tile = this->parent->get(new_Location);
		moveTo(this->parent->findMidPoint(new_tile, this->speed));
	}
	cout << "Now at " << this->coordinates << endl;

	// Count other combatants in neighbouring tiles.
	int potential_targets = 0;
	std::vector<Tile*> adjacent_foes = this->getOccupiedNeighbours();

	if (adjacent_foes.size() > 0)
	{
		cout << "Select target:\t";
		for(Tile* T : adjacent_foes)
		{
			cout << T->getContents()->getName() << " (" << ++potential_targets << ")" << endl << "\t\t";
		}

		// Ask user for which enemy to attack.
		int tc;
		cin >> tc;

		// Make attack against target. If attack kills them, result is set to dead. Else, alive.
		life_status result = this->make_attack(*(adjacent_foes[tc-1]->getContents()));

		// If target is killed, remove them from the list and decrement the number of potential targets.
		if (result == dead)
		{
			auto corpse = find(this->parentMap->initiative_order.begin(), this->parentMap->initiative_order.end(), adjacent_foes[tc - 1]->getContents());
			if (corpse != this->parentMap->initiative_order.end())
			{
				this->parentMap->initiative_order.erase(corpse);
				potential_targets--;
			}
			else
				throw("Could not find corpse in initiative order!");
		}
	}

	return turn_finished;
#endif
	return 0;
}

/* brief: 	Roll attack against the target's AC, then roll damage.
	 	Virtual overloaded function from Combatant.
   param: 	Address of target, called by reference.
   returns:	The status of the target.
*/
life_status Player::make_attack(Object & target)
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
