#ifndef OBJECT_H
#define OBJECT_H

#include "pathfinding.h"
#include "weapon_type.h"
#include <string>
#include <vector>

#define MAX_VALUE 32767

enum life_status {alive, death_1, death_2, dead};

class Tile;
class node;

class object {
protected:
	std::string name;
	location coordinates;
	Tile* parent;
public:
	// Constructors
	object() : name(""), coordinates(location(0,0,0)), parent(NULL) {};
	object(location Coordinates) : name(""), coordinates(Coordinates), parent(NULL) {};

	// Get a list of vacant neighbouring tiles.
	std::vector<Tile*> getFreeNeighbours();
	// Get a list of occupied neighbouring tiles.
	std::vector<Tile*> getOccupiedNeighbours();

	// Debugging functions
	virtual void print_stats();

	// Virtual functions for downcasting
	// Roll a dice
	virtual int make_roll(roll x) { return -1; };
	// Roll initiative specifically
	virtual int roll_initiative() { return -1; };
	// Move and then make attack
	virtual int take_turn(node* self) { return -1; };
	// Roll both attack and damage against a target.
	virtual life_status make_attack(object & target) { return dead; };
	// Roll both attack and damage against a target, supplying a weapon.
	virtual life_status make_attack(weapon_type weapon, object & target) { return dead; };	// Pass by reference
	// Reduce hp by dam
	virtual life_status take_damage(int dam) { return dead; };
	// Reduce hp by dam, specific to damage type.
	virtual life_status take_damage(int dam, type damage_type) { return dead; };
	// Move to a tile next to another tile.
	virtual int moveTo(Tile* target) { return -1; };

	// Getters/setters
	location getCoordinates() { return coordinates; };
	int setCoordinates(location Coordinates) { coordinates = Coordinates; return 0; };
	Tile* getParent() { return parent; };
	int setParent( Tile* Parent ) { parent = Parent; return 0; };

	// Virtual getters/setters
	virtual std::string getName() { return name; };				// Name
	virtual int setName(std::string Name) { name = Name; return 0; }
	virtual int getHp() { return -1; };					// HP
	virtual int setHp(int val) { return -1; };
	virtual int getAc() { return -1; };					// AC
	virtual int setAc(int val) { return -1; };
	virtual int getSpd() { return -1; };					// Speed
	virtual int setSpd(int val) { return -1; };
	virtual roll getInit() { return roll(); };					// Initiative
	virtual int setInit(int val) { return -1; };
	virtual life_status getStatus() { return dead; };				// Status
	virtual int setStatus(life_status val) { return -1; };
};

#endif
