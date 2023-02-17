#include "csv_reader.h"
#include "combatant.h"
#include "tools.h"
#include "load_file.h"
#include "monster.h"
#include "tile.h"
#include "display.h"
#include "linegrid.h"
#include <math.h>
#include <map>
#include <filesystem>
#include <cstring>
#include <SFML/Graphics/Color.hpp>

using namespace std;

Tile *battlemap;

/* brief:	Return the correct number in degrees needed to face the mouse.
   param:	sprite - The sprite to rotate.
		&window - The game window, called by reference.
   returns:	The float value for the number of degrees needed to rotate by, in the range 0-360.
*/
float face_mouse(sf::Sprite sprite, sf::RenderWindow &window)
{
	sf::Vector2f spr_pos = sprite.getPosition();
	sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);

	const float pi = 3.14159265;

	float dx = spr_pos.x - mouse_pos.x;
	float dy = spr_pos.y - mouse_pos.y;

	float rotation = (atan2(dy,dx)) * (180/pi);

	return rotation + 180;
}

/** @brief: Move a rectangle to the tile corresponding to the mouse cursor.
	  @param: highlighter - Rectangle, passed by reference.
						window - Game window, passed by reference.
						hl_width - Width of rectangle.
		@returns: Nothing.
**/
void moveToMousedOverTile(sf::RectangleShape &highlighter, sf::RenderWindow &window, float hl_width)
{
	sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);

	float x_pos = (mouse_pos.x - (mouse_pos.x%int(hl_width))) + (hl_width/2);
	float y_pos = (mouse_pos.y - (mouse_pos.y%int(hl_width))) + (hl_width/2);

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
void run_encounter(std::vector <object*> players)
{
	node * active_player = new node();		// Create initialisation node for players.
	int i = 0;					// Initialise counter to 0.

	// Graphics loop crudely inserted below, so declaring variables here for time being.
	sf::RenderWindow window(sf::VideoMode(WINDOW_W,WINDOW_H), "DnD_Game");

	// Spawn mouse over tile icon.
	float hl_width = (WINDOW_W+1)/battlemap->width();
	sf::RectangleShape highlighter(sf::Vector2f(hl_width,hl_width));
	highlighter.setOrigin(hl_width/2, hl_width/2);
	highlighter.setFillColor(sf::Color(0xFF,0xFF,0x66,0x70));

	/* Create circular list of players sorted by intiative. Point active_player at head. */
	active_player = initiative_round(players, window);
	active_player->print();

	cout << endl;					// Add line break for readability.

	std::cout << endl;

	node * first_player = active_player;

	sf::Event event;
	// Repeat until only one player is left.
	do {
		std::cout << "character name: " << active_player->player->getName() << std::endl;
		std::cout << "character location: " << active_player->player->getCoordinates() << std::endl;
		// Make move and take attack
		bool turn_finished = active_player->player->take_turn(active_player);

		std::cout << "turn taken" << std::endl;

		// Progress iterator node to the next one unless waiting for input.
		if (turn_finished == true)
			active_player = active_player->next;

		bool nextTurn = false;
		while (nextTurn == false)
		{
			if (window.pollEvent(event))
			{
				// Keyboard events
				if (event.type == sf::Event::KeyPressed)
				{
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
				}
			}

			// Rotate player to face mouse
			sprites["Player"].setRotation(face_mouse(sprites["Player"],window));

			// Move tile highlighter to mouse.
			moveToMousedOverTile(highlighter, window, hl_width);

			window.clear();
			LineGrid tiles;
			tiles.create((WINDOW_W+1)/battlemap->width());

			updateScreen(&window);

			window.draw(highlighter);
			window.draw(tiles);
			window.display();
		}

		if (active_player->next == active_player)
		{
			std::cout << "Finished" << std::endl;
			break;
		}
	} while (event.type != sf::Event::Closed);

	window.close();

	// Debug code. State last fighter standing.
	cout << active_player->player->getName() << " wins!" << endl;
}

/* brief: 	main function. Loads players and monsters from .csv file with hardcoded address.
	  	Then prints each to screen, and runs an encounter with them.
   param: 	none
   returns: 	0
*/
int main() {

	srand(time(nullptr));							// Generate random seed.

	std::vector<object*> players; 						// Create vector of players and monsters.

	players = interpret_nodes("./stats/encounter1.enctr");

	battlemap = new Tile(25,19);

	battlemap->print_map();

	// Fill texture and sprite maps with contents.
	load_sprites();

	// Range based for loop. Print stats of each player to screen.
	// Also adds players to map and screen in correct location.
	for(object* O : players) {
		O->print_stats();
		sprites[O->getName()].setPosition(16.f+(32.f*float(O->getCoordinates().getX())),
						  16.f+(32.f*float(O->getCoordinates().getY())));
		Tile *tile = battlemap->get(O->getCoordinates());
		tile->setContents(O);
		combatants.insert(std::pair<std::string, object>(O->getName(), *O));
	}

	battlemap->print_map();

	std::cout << std::endl;

	// Loop for combat.
	run_encounter(players);

	delete(battlemap);

    return 0;
};
