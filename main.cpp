#include <SFML/Graphics.hpp>
#include "include/csv_reader.h"
#include "include/combatant.h"
#include "include/tools.h"
#include "include/load_file.h"
#include "include/monster.h"
#include "include/tile.h"

using namespace std;

Tile *battlemap;

/* brief: 	Roll initiative for all players and monsters involved, then have each perform an action
	  	on their turn.
	  	Currently only supports melee attacks against random opponents.
   param: 	players - vector of pointers to players and monsters involved in encounter.
   returns: 	nothing
*/
void run_encounter(std::vector <object*> players)
{
	node * active_player = new node();		// Create initialisation node for players.
	int i = 0;					// Initialise counter to 0.

	active_player = initiative_round(players);	// Create circular list of players sorted by intiative. Point active_player at head.

	cout << endl;					// Add line break for readability.

	// Graphics loop crudely inserted below, so declaring variables here for time being.
	sf::RenderWindow window(sf::VideoMode(200,200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	cout << endl;

	// Repeat until only one player is left.
	while (active_player->next != active_player)
	{
		// Make move and take attack
		active_player->player->take_turn(active_player);

		// Progress iterator node to the next one.
		active_player = active_player->next;

		// Going to stick graphics loop here temporarily, and rewrite everything when it's more developed.
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

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

	std::vector<object*> players; 					// Create vector of players and monsters.

	players = interpret_nodes("./stats/encounter1.enctr");

	battlemap = new Tile(125,35);

	// Range based for loop. Print stats of each player to screen.
	// Also adds players to map.
	for(object* O : players) {
		O->print_stats();
		Tile *tile = battlemap->get(O->getCoordinates());
		tile->setContents(O);
	}

	battlemap->print_map();

	std::cout << std::endl;

	// Loop for combat.
	run_encounter(players);

	delete(battlemap);

    	return 0;
};
