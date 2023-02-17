#ifndef OBJECT_H
#define OBJECT_H

#include "pathfinding.h"
#include "weapon_type.h"
#include "battlemap.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#define MAX_VALUE 32767

enum life_status {alive, death_1, death_2, dead};
enum object_type {OutOfBounds, type_object, type_player, type_combatant};

class Tile;

class Object {
protected:
	std::string name;
	Location coordinates;
	Tile *parent;
	uint8_t initiative;
	BattleMap *parentMap;

public:
	// Constructors
	Object() : name(""), coordinates(Location(0,0,0)), parent(NULL), initiative(0) {};
	Object(Location Coordinates) : name(""), coordinates(Coordinates), parent(NULL), initiative(0) {};

	// Get a list of vacant neighbouring tiles.
	std::vector<Tile*> getFreeNeighbours();
	// Get a list of occupied neighbouring tiles.
	std::vector<Tile*> getOccupiedNeighbours();

	// Debugging functions
	virtual void print_stats();

	// Virtual functions for downcasting
	// Roll a dice
	virtual int make_roll(Roll x) { return -1; };
	// Roll initiative specifically
	virtual int roll_initiative() { return -1; };
	// Move and then make attack
	virtual int take_turn(node* self) { return -1; };
	// Roll both attack and damage against a target.
	virtual life_status make_attack(Object & target) { return dead; };
	// Roll both attack and damage against a target, supplying a weapon.
	virtual life_status make_attack(weapon_type weapon, Object & target) { return dead; };	// Pass by reference
	// Reduce hp by dam
	virtual life_status take_damage(int dam) { return dead; };
	// Reduce hp by dam, specific to damage type.
	virtual life_status take_damage(int dam, type damage_type) { return dead; };
	// Move to a tile next to another tile.
	virtual int moveTo(Tile* target) { return -1; };

	// Getters/setters
	Location getCoordinates() { return coordinates; };
	int setCoordinates(Location Coordinates) { coordinates = Coordinates; return 0; };
	Tile *getParent() { return parent; };
	int setParent( Tile* Parent ) { parent = Parent; return 0; };
	BattleMap *getBattleMap() { return parentMap; };
	int setBattleMap(BattleMap* map) { parentMap = map; return 0; };

	// Virtual getters/setters
	virtual std::string getName() { return name; };				// Name
	virtual int setName(std::string Name) { name = Name; return 0; }
	virtual int getHp() { return -1; };					// HP
	virtual int setHp(int val) { return -1; };
	virtual int getAc() { return -1; };					// AC
	virtual int setAc(int val) { return -1; };
	virtual int getSpd() { return -1; };					// Speed
	virtual int setSpd(int val) { return -1; };
	virtual Roll getInit() { return Roll(0,0,0); };				// Initiative roll
	virtual int setInit(int val) { return -1; };
	virtual life_status getStatus() { return dead; };			// Status
	virtual int setStatus(life_status val) { return -1; };
	virtual int getInitiative() { return -1; };					// Initiative value
	virtual int setInitiative(int init) { return -1; };

	// Get type
	virtual object_type getObjectType() {return type_object; };			// Return ennumerated type value.
};

class OutOfBoundsObject : public Object
{
	using Object::Object;

	object_type getObjectType() {return OutOfBounds; };
};

#endif
