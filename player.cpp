#include "player.h"
#include "combatant.h"
#include "roll.h"
#include "tools.h"
#include "battlemap.h"

/* brief: 	Make move and then make attack against specified target.
	  		Virtual overloaded function from Combatant.
   returns:	0 if successful.
*/
int Player::take_turn()
{
	int state = turn_finished ? 1 : 0;
	turn_finished = false;	// Reset before next turn

	return state;
}

bool Player::handleEvent(sf::Event &event, sf::RenderWindow &window)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::W)
			moveTo(this->tile->getNorth());

		if (event.key.code == sf::Keyboard::A)
			moveTo(this->tile->getWest());

		if (event.key.code == sf::Keyboard::S)
			moveTo(this->tile->getSouth());

		if (event.key.code == sf::Keyboard::D)
			moveTo(this->tile->getEast());

		if (event.key.code == sf::Keyboard::P)
			std::cout << "print" << std::endl;

		if (event.key.code == sf::Keyboard::Return)
			turn_finished = true;
	}

	else if (event.type == sf::Event::MouseButtonReleased)
	{
		sf::Vector2i pos = sf::Mouse::getPosition(window);
		sf::Vector2u window_size = window.getSize();

		uint8_t x_pos = (pos.x/float(window_size.x)) * this->getBattlemap()->getWidth();
		uint8_t y_pos = (pos.y /float(window_size.y)) * this->getBattlemap()->getHeight();

		Tile *newTile = this->getBattlemap()->get(x_pos, y_pos);
		if (newTile->getContents())
			make_attack(*(newTile->getContents()));
		else
			moveTo(newTile);
	}
	
	return true;
}

/* brief: 	Roll attack against the target's AC, then roll damage.
	 	Virtual overloaded function from Combatant.
   param: 	Address of target, called by reference.
   returns:	The status of the target.
*/
life_status Player::make_attack(Object & target)
{
	//std::string input;
	//cout << endl << "Please give number of weapon to use: ";
	//cin >> input;
	int wc = 0;							// Weapon choice

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
