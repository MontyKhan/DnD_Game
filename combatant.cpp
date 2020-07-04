#include "include/combatant.h"

using namespace std;

// Override function for "roll" variable.
std::ostream & operator << (std::ostream &out, const roll &r)
{
	out << r.num << "d" << r.dice << " + " << r.mod;
	return out;
}

// Constructor for when taking variables individually
combatant::combatant(std::string Name, int HP, int AC, int Spd, int Init, int Attack, std::string Damage)
{
	name = Name;
	hp = HP;
	ac = AC;
	speed = Spd;
	init = roll(1,20,Init);
	attack = roll(1,20,Attack);
	damage = read_dam(Damage);
}

// Constuctor when taking vector of strings as input
combatant::combatant(std::vector<std::string> line)
{
	name = line[NAME_VAR];				// Get name (string)
	hp = stoi(line[HP_VAR]);			// Get HP (int)
	ac = stoi(line[AC_VAR]);			// Get AC (int)
	speed = stoi(line[SPD_VAR]);			// Get speed (int)
	init = roll(1,20,stoi(line[INIT_VAR]));		// Create initiative roll
	attack = roll(1,20,stoi(line[ATTACK_VAR]));	// Create attack roll
	damage = read_dam(line[DAM_VAR]);		// Create damage roll
}

// Convert string in format %d% + % into three ints.
roll combatant::read_dam(std::string input)
{
	roll values;

	int d = input.find("d");
	int dice_length = input.length() - d + 1;

	int plus = input.find(" + ") + 2;
	int plus_length = input.length() + 1;
	values.mod = 0;

	if (plus > 1) {
		plus_length = input.length() - plus;
		values.mod = stoi(input.substr(plus+1, input.length() - plus_length));
	}

	values.num = stoi(input.substr(0,d));
	values.dice = stoi(input.substr(d+1, plus_length - dice_length));

	return values;
}

// Debugging, print all combatant stats.
void combatant::print_stats()
{
	cout << "Name: " << name << endl;
	cout << "HP: " << hp << endl;
	cout << "AC: " << ac << endl;
	cout << "Speed: " << speed << endl;
	cout << "Iniative: " << init << endl;
	cout << "Attack: " << attack << endl;			// Overridden, prints in form %d% + %.
	cout << "Damage: " << damage << endl;			// Overridden, prints in form %d% + %.
	cout << endl;
}

// Roll the dice given as input
int combatant::make_roll(roll x)
{
	int damage = 0;
	vector <int> results;

	for (int i = 0; i < x.num; i++)
	{
		int val = rand() % x.dice + 1;
		results.push_back(val);
		damage += val;
	}

	if (x.num > 1)
		print_vector(results);	

	return damage + x.mod;
}

// Roll Initiative specifically
int combatant::roll_initiative()
{
	return make_roll(init);
}

// Roll attack and damage.
int combatant::make_attack(combatant & target)
{
	int attack_roll = make_roll(attack);

	cout << "Attack: " << attack_roll << " ";

	if (attack_roll < target.getAc()) {
		cout << "(Miss)" << endl;
		return 0;
	}
	else {
		int damage_roll = make_roll(damage);
		cout << "(Hit, " << damage_roll << " damage)" << endl;
		return target.take_damage(damage_roll);			// Return status of target.
	}
	
	return -1;				// Should not reach here.
}

// Reduce HP by dam
int combatant::take_damage(int dam)
{
	if (dam < hp)
		hp -= dam;
	else {
		hp = 0;
		status = dead;
	}

	return status;
}
