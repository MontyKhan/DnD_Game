#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>
#include "display.h"
#include "combatant.h"

namespace fs = std::filesystem;

// Create map containers
std::map<std::string, sf::Texture> textures;
std::map<std::string, sf::Sprite> sprites;
std::map<std::string, object> combatants;

/* brief:	Update the screen with all entities that need to be drawn.
   param:	*window - Pointed to the window used as the UI.
		entities - A vector containing all sprites to be drawn.
   returns:	Nothing.
*/
void updateScreen(sf::RenderWindow *window)
{
	for (std::pair<std::string, sf::Sprite> p : sprites)
	{
		window->draw(p.second);
	}
}

/* brief:	Fill the texture and sprite maps with files to optimise load times.
   param:	&textures - Map containing textures loaded from images. Passed by reference.
		&sprites - Map containing sprites, containing pointers to textures. Passed by reference.
   returns:	0, to be changed later to how many textures couldn't be loaded.
*/
int load_sprites()
{
	std::string directory = "./images/sprites/";

	float mult = 1;

	for(auto& p: fs::directory_iterator(directory))
	{
		std::string name = p.path().stem().string();
		
		sf::Image image;

		std::string imagepath = p.path().string();
		std::cout << "Absolute path for " << p << " is " << fs::absolute(p) << '\n';
		bool exists = std::filesystem::exists(p.path().string());
		if (!(image.loadFromFile(p.path().string())))
			std::cout << "Could not load from file!" << std::endl;

		sf::Texture texture;
		texture.loadFromImage(image);

		textures.insert({name, texture});

		sf::Sprite sprite;
		sprite.setTexture(textures[name]);

		sprite.scale(32.f / sprite.getLocalBounds().height, 32.f / sprite.getLocalBounds().height);

		float y_size = sprite.getLocalBounds().height / 2.f;
		float x_size = sprite.getLocalBounds().width / 2.f;
		sprite.setOrigin(x_size, y_size);
		sprite.setPosition(mult*25.f, 50.f);
		if (name.compare("river_bridge") == 0)	// Come up with better solution for this later.
		{
			sprite.setOrigin(0.f, 0.f);
			sprite.setScale(float(WINDOW_W)/float(texture.getSize().x),float(WINDOW_H)/float(texture.getSize().y));
			sprite.setPosition(0.f, 0.f);
			sprites.insert({"AAAAA", sprite});
		}
		else
			sprites.insert({name, sprite});

		mult++;
	}

	return 0;
}
