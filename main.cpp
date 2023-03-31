#include "csv_reader.h"
#include "combatant.h"
#include "tools.h"
#include "load_file.h"
#include "monster.h"
#include "tile.h"
#include "display.h"
#include "linegrid.h"
#include "battlemap.h"
#include <math.h>
#include <map>
#include <filesystem>
#include <cstring>
#include <SFML/Graphics/Color.hpp>

using namespace std;

Tile *battlemap;

/* brief: 	main function. Loads players and monsters from .csv file with hardcoded address.
	  	Then prints each to screen, and runs an encounter with them.
   param: 	none
   returns: 	0
*/
int main() {

	srand(time(nullptr));							// Generate random seed.

	std::vector<Object*> players; 						// Create vector of players and monsters.

	players = interpret_nodes("./stats/encounter1.enctr");

	BattleMap *battlemap = new BattleMap(25,19,players);

	battlemap->print_map();

	// Fill texture and sprite maps with contents.
	load_sprites();

	// Range based for loop. Print stats of each player to screen.
	// Also adds players to map and screen in correct Location.
	for(Object* O : players) {
		O->print_stats();
		sprites[O->getName()].setPosition(16.f+(32.f*float(O->getCoordinates().getX())),
						  16.f+(32.f*float(O->getCoordinates().getY())));
		Tile *tile = battlemap->get(O->getCoordinates());
		tile->setContents(O);
		combatants.insert(std::pair<std::string, Object>(O->getName(), *O));
	}

	battlemap->print_map();

	std::cout << std::endl;

	// Loop for combat.
	// Graphics loop crudely inserted below, so declaring variables here for time being.
	sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H), "DnD_Game");
	battlemap->run_encounter(window);

	delete battlemap;

    return 0;
};
