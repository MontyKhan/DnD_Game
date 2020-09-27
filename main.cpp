#include "include/csv_reader.h"
#include "include/combatant.h"
#include "include/tools.h"
#include "include/load_file.h"
#include "include/monster.h"
#include "include/tile.h"
#include "include/display.h"
#include "include/linegrid.h"
#include <math.h>
#include <map>
#include <filesystem>
#include <cstring>

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

/* brief: 	Roll initiative for all players and monsters involved, then have each perform an action
	  	on their turn.
	  	Currently only supports melee attacks against random opponents.
   param: 	players - vector of pointers to players and monsters involved in encounter.
		textures - map containing all textures to display
		sprites - map containing all sprites to display
   returns: 	nothing
*/
void run_encounter(std::vector <object*> players, std::map<std::string, sf::Texture> &textures, std::map<std::string, sf::Sprite> &sprites)
{
	node * active_player = new node();		// Create initialisation node for players.
	int i = 0;					// Initialise counter to 0.

	active_player = initiative_round(players);	// Create circular list of players sorted by intiative. Point active_player at head.

	cout << endl;					// Add line break for readability.

	// Graphics loop crudely inserted below, so declaring variables here for time being.
	sf::RenderWindow window(sf::VideoMode(WINDOW_W,WINDOW_H), "DnD_Game");

	cout << endl;

	sf::Event event;
	// Repeat until only one player is left.
	while (event.type != sf::Event::Closed)
	{
		// Make move and take attack
		// active_player->player->take_turn(active_player);

		// Progress iterator node to the next one.
		active_player = active_player->next;

		// Going to stick graphics loop here temporarily, and rewrite everything when it's more developed.
		while (window.pollEvent(event))
		{
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
			}
		}

		// Rotate player to face mouse
		sprites["Player"].setRotation(face_mouse(sprites["Player"],window));

		window.clear();
		LineGrid tiles;
		tiles.create((WINDOW_W+1)/battlemap->width());

		updateScreen(&window,sprites);

		window.draw(tiles);
		window.display();

		if (active_player->next == active_player)
			break;
	}

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

	srand(time(NULL));							// Generate random seed.

	std::vector<object*> players; 						// Create vector of players and monsters.

	players = interpret_nodes("./stats/encounter1.enctr");

	battlemap = new Tile(25,19);

	// Create map containers
	std::map<std::string, sf::Texture> textures;
	std::map<std::string, sf::Sprite> sprites;

	// Fill texture and sprite maps with contents.
	load_sprites(textures, sprites);

	// Range based for loop. Print stats of each player to screen.
	// Also adds players to map and screen in correct location.
	for(object* O : players) {
		O->print_stats();
		sprites[O->getName()].setPosition(50.f*float(O->getCoordinates().getX()), 50.f*float(O->getCoordinates().getY()));
		Tile *tile = battlemap->get(O->getCoordinates());
		tile->setContents(O);
	}

	battlemap->print_map();

	std::cout << std::endl;

	// Loop for combat.
	run_encounter(players, textures, sprites);

	delete(battlemap);

    	return 0;
};
