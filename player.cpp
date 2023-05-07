#include "player.h"
#include "combatant.h"
#include "roll.h"
#include "tools.h"
#include "battlemap.h"
#include "weapon_type.h"

/* brief: 	Make move and then make attack against specified target.
	  		Virtual overloaded function from Combatant.
   returns:	0 if still players turn, 1 otherwise.
*/
int Player::take_turn()
{
	int state = turn_finished ? 1 : 0;
	turn_finished = false;	// Reset before next turn

	return state;
}

bool Player::handleEvent(sf::Event &event, sf::RenderWindow &window)
{
	if (turn_finished)
		return true;	// No moves after turn is finished!

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
		{
			visitedTiles = this->tile->findMinimumPath(newTile);
			moveTo(newTile);
		}
	}
	
	return true;
}

/* brief: 	Roll attack against the target's AC, then roll damage.
	 	Virtual overloaded function from Combatant.
   param: 	Address of target, called by reference.
   returns:	The status of the target.
*/
life_status_t Player::make_attack(Object & target)
{
	//std::string input;
	//cout << endl << "Please give number of weapon to use: ";
	//cin >> input;
	int wc = 0;							// Weapon choice
	attack_target = &target;

	return (life_status_t)weapons[wc].makeWeaponAttack(target);
}
