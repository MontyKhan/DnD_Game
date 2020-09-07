#ifndef DISPLAY_H
#define DISPLAY_H

#include <SFML/Graphics.hpp>

#define WINDOW_W	800
#define WINDOW_H	600

// Draw all sprites within the vector "entities" to screen.
void updateScreen(sf::RenderWindow *window, std::vector<sf::Sprite> entities);

#endif
