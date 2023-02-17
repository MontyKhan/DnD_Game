#ifndef DISPLAY_H
#define DISPLAY_H

#include <SFML/Graphics.hpp>
#include <map>
#include "object.h"

#define WINDOW_W	800
#define WINDOW_H	600

// Create map containers
extern std::map<std::string, sf::Texture> textures;
extern std::map<std::string, sf::Sprite> sprites;
extern std::map<std::string, Object> combatants;

// Draw all sprites within the vector "entities" to screen.
void updateScreen(sf::RenderWindow *window);
// Preload all sprites and textures and store them in maps.
int load_sprites();

#endif
