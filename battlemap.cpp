#include "battlemap.h"

#include "object.h"
#include "display.h"
#include "linegrid.h"
#include "player.h"

BattleMap::BattleMap(uint8_t x, uint8_t y, std::vector<Object*> objects) :
	objects(objects),
	width(x),
	height(y)
{
	origin = new Tile(x, y);

	assignInitiativeOrder();
}

BattleMap::~BattleMap()
{
	delete origin;
}

// Get specific tile by map reference, Location.
Tile* BattleMap::get(Location coordinates) {
	return origin->get(coordinates);
};
// Get specific tile by map reference, individual ints.
Tile* BattleMap::get(int x, int y) {
	return origin->get(x, y);
}
// Get specific tile by contents.
Tile* BattleMap::get(Object* toFind) {
	return origin->get(toFind);
}

/* brief: Create a circular doubly linked list sorted by initiative.
   param: players - A vector containing pointers to all monsters and players involved via downcasting.
   returns: 	Pointer to the head of the new circular doubly linked list.
*/
void BattleMap::assignInitiativeOrder()
{
	for (const auto& player : objects)
	{
		initiative_order.push_back(player);
		player->setBattlemap(this);
		player->roll_initiative();	// Set initiative value for head to RNGed value.
	}

	initiative_order.sort([](auto& first, auto& second) { return (first->getInitiative() > second->getInitiative()); });
}

/* brief:	Return the correct number in degrees needed to face the mouse.
   param:	sprite - The sprite to rotate.
			&window - The game window, called by reference.
   returns:	The float value for the number of degrees needed to rotate by, in the range 0-360.

   TODO - MOVE SOMEWHERE BETTER
*/
float face_mouse(sf::Sprite sprite, sf::RenderWindow &window)
{
	sf::Vector2f spr_pos = sprite.getPosition();
	sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);

	const float pi = 3.14159265;

	float dx = spr_pos.x - mouse_pos.x;
	float dy = spr_pos.y - mouse_pos.y;

	float rotation = (atan2(dy, dx)) * (180 / pi);

	return rotation + 180;
}

/** @brief: Move a rectangle to the tile corresponding to the mouse cursor.
	  @param: highlighter - Rectangle, passed by reference.
						window - Game window, passed by reference.
						hl_width - Width of rectangle.
		@returns: Nothing.

	TODO - MOVE SOMEWHERE BETTER
**/
void moveToMousedOverTile(sf::RectangleShape &highlighter, sf::RenderWindow &window, float hl_width)
{
	sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);

	float x_pos = (mouse_pos.x - (mouse_pos.x % int(hl_width))) + (hl_width / 2);
	float y_pos = (mouse_pos.y - (mouse_pos.y % int(hl_width))) + (hl_width / 2);

	highlighter.setPosition(x_pos, y_pos);
}

/* brief: 	Roll initiative for all players and monsters involved, then have each perform an action
		on their turn.
		Currently only supports melee attacks against random opponents.
   param: 	players - vector of pointers to players and monsters involved in encounter.
		textures - map containing all textures to display
		sprites - map containing all sprites to display
   returns: 	nothing
*/
void BattleMap::run_encounter(sf::RenderWindow& window)
{
	auto active_player = this->initiative_order.begin();
	int i = 0;					// Initialise counter to 0.

	// Spawn mouse over tile icon.
	float hl_width = (WINDOW_W + 1) / this->computeWidth();
	sf::RectangleShape highlighter(sf::Vector2f(hl_width, hl_width));
	highlighter.setOrigin(hl_width / 2, hl_width / 2);
	highlighter.setFillColor(sf::Color(0xFF, 0xFF, 0x66, 0x70));

	std::cout << endl;

	sf::Event event;
	// Repeat until only one player is left.
	do {

		if (this->initiative_order.size() <= 1)
		{
			std::cout << "Finished" << std::endl;
			break;
		}

		// Make move and take attack
		bool turn_finished = (*active_player)->take_turn();

		if (turn_finished)
		{
			std::cout << "character name: " << (*active_player)->getName() << std::endl;
			std::cout << "character Location: " << (*active_player)->getCoordinates() << std::endl;

			if (std::next(active_player) == this->initiative_order.end())
			{
				active_player = this->initiative_order.begin();
			}
			else
			{
				active_player++;
			}
		}

		if (window.pollEvent(event))
		{
			if (dynamic_cast<Player *>(*active_player))
			{
#if 0
				if (event.key.code == sf::Keyboard::W)
					sprites["Player"].move(0.f, -5.f);

				if (event.key.code == sf::Keyboard::A)
					sprites["Player"].move(-5.f, 0.f);

				if (event.key.code == sf::Keyboard::S)
					sprites["Player"].move(0.f, 5.f);

				if (event.key.code == sf::Keyboard::D)
					sprites["Player"].move(5.f, 0.f);

				if (event.key.code == sf::Keyboard::P)
					std::cout << "print" << std::endl;

				if (event.key.code == sf::Keyboard::Return)
					nextTurn = true;
#else
				(*active_player)->handleEvent(event, window);
#endif
			}
			else
			{
				std::cout << "Not a player!" << std::endl;
			}
		}

		// Rotate player to face mouse
		sprites["Player"].setRotation(face_mouse(sprites["Player"], window));

		// Move tile highlighter to mouse.
		moveToMousedOverTile(highlighter, window, hl_width);

		window.clear();
		LineGrid tiles;
		tiles.create((WINDOW_W + 1) / this->computeWidth());

		updateScreen(&window);

		window.draw(highlighter);
		window.draw(tiles);
		window.display();

	} while (event.type != sf::Event::Closed);

	window.close();

	// Debug code. State last fighter standing.
	cout << (*active_player)->getName() << " wins!" << endl;
}