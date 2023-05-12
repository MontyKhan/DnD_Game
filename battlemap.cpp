#include "battlemap.h"

#include <functional>

#include "object.h"
#include "display.h"
#include "linegrid.h"
#include "player.h"
#include "scheduler.h"

const float time_max{ 0.5 };

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

/* brief: Get count of factions still involved in battle
   param: active_combatants - List of all objects in battle
   return: Count of unique factions
**/
int numberOfRemainingFactions(std::list<Object *> active_combatants)
{
	std::function<uint32_t (Object *)> getFaction = [&](Object *actor) {return static_cast<uint32_t>(actor->getFaction()); };

	active_combatants.sort([&](Object *lhs, Object *rhs) {return getFaction(lhs) > getFaction(rhs); });
	auto last = std::unique(active_combatants.begin(), active_combatants.end(), 
		[&](Object *lhs, Object *rhs) {return getFaction(lhs) == getFaction(rhs); });
	active_combatants.erase(last, active_combatants.end());

	return active_combatants.size();
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
	sf::Clock clock;
	Scheduler scheduler;
	bool move_anim_finished = true;
	bool turn_finished = false;
	bool move_animation_queued = false;
	bool attack_animation_queued = false;
	float clock_time = 0;
	// Repeat until only one player is left.

	scheduler.addEvent([](float time) {std::cout << "Testing Scheduler" << std::endl; return 0; }, 5, 0);

	do {
		scheduler.executeEvents();

		// Move tile highlighter to mouse.
		moveToMousedOverTile(highlighter, window, hl_width);

		window.clear();
		LineGrid tiles;
		tiles.create((WINDOW_W + 1) / this->computeWidth());

		updateScreen(&window);

		window.draw(highlighter);
		window.draw(tiles);
		window.display();

		// Check if battle over
		//if (this->initiative_order.size() <= 1)
		if (numberOfRemainingFactions(this->initiative_order) <= 1)
		{
			std::cout << "Finished" << std::endl;
			break;
		}

		std::vector<Tile *> *visitedTiles = (*active_player)->getVisitedTiles();
		bool move_action_used = (visitedTiles->size() > 0);
		bool attack_action_used = (*active_player)->getAttackTarget() != nullptr;

		if (move_action_used)
		{
			Tile *active_tile = *visitedTiles->begin();
			Tile *next_tile = (visitedTiles->size() > 1) ? *(visitedTiles->begin() + 1) : *visitedTiles->begin();

			Location grid_coordinates = active_tile->getCoordinates();
			clock_time = clock.getElapsedTime().asSeconds();
			if (clock_time > time_max) { clock_time = time_max; }

			float ref_coordinates_x = grid_coordinates.getX() + ((clock_time / time_max) * (next_tile->getCoordinates().getX() - active_tile->getCoordinates().getX()));
			float ref_coordinates_y = grid_coordinates.getY() + ((clock_time / time_max) * (next_tile->getCoordinates().getY() - active_tile->getCoordinates().getY()));
			sprites[(*active_player)->getName()].setPosition(16.f + (32.f * float(ref_coordinates_x)),
				16.f + (32.f * float(ref_coordinates_y)));

			if (clock_time == time_max)
			{
				clock.restart();
				clock_time = 0;
				visitedTiles->erase(visitedTiles->begin());

				if (visitedTiles->size() == 0)
					move_action_used = false;
			}
		}
		else if (attack_action_used && !attack_animation_queued)
		{
#if 0
			clock_time = clock.getElapsedTime().asSeconds();
			if (clock_time > time_max) { clock_time = time_max; }
#endif

			sprites[(*active_player)->getName()].rotate(360.f / (clock_time / time_max));
			sprites[(*active_player)->getAttackTarget()->getName()].setColor(sf::Color::Red);

			scheduler.addEvent([&](float time) { sprites[(*active_player)->getAttackTarget()->getName()].setColor(sf::Color::White);  std::cout << "clear colour" << std::endl; }, 1);
			scheduler.addEvent([&](float time) { (*active_player)->setAttackTarget(nullptr);  std::cout << "clear target" << std::endl; }, 1);
			scheduler.addEvent([&](float time) { attack_action_used = false; std::cout << "clear bool" << std::endl; }, 1);
			scheduler.addEvent([&](float time) { attack_animation_queued = false; std::cout << "clear bool" << std::endl; }, 1);

			attack_animation_queued = true;
#if 0
			if (clock_time == time_max)
			{
				clock.restart();
				clock_time = 0;

				sprites[(*active_player)->getAttackTarget()->getName()].setColor(sf::Color::White);
				(*active_player)->setAttackTarget(nullptr);
				attack_action_used = false;
			}
#endif
		}

		// Make move and take attack
		bool animations_finished = !(move_action_used || attack_action_used);
		if ((!turn_finished) && animations_finished)
			turn_finished = (*active_player)->take_turn();

		if (turn_finished && animations_finished)
		{
			std::cout << "character name: " << (*active_player)->getName() << std::endl;
			std::cout << "character location: " << (*active_player)->getCoordinates() << std::endl;

			for (const auto &actor : initiative_order)
			{
				std::cout << "actor name: " << actor->getName() << std::endl;
				std::cout << "actor location: " << actor->getCoordinates() << std::endl;
			}

			turn_finished = false;
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
				(*active_player)->handleEvent(event, window);
			}
		}

	} while (event.type != sf::Event::Closed);

	window.close();

	// Debug code. State last fighter standing.
	std::cout << (*active_player)->getName() << " wins!" << endl;
}