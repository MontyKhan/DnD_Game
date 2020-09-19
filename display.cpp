#include <SFML/Graphics.hpp>
#include "include/display.h"

/* brief:	Update the screen with all entities that need to be drawn.
   param:	*window - Pointed to the window used as the UI.
		entities - A vector containing all sprites to be drawn.
   returns:	Nothing.
*/
void updateScreen(sf::RenderWindow *window, std::map<std::string, sf::Sprite> sprites)
{
	window->clear();

	for (std::pair<std::string, sf::Sprite> p : sprites)
	{
		window->draw(p.second);
	}

	window->display();
}
