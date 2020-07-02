#include "action.h"

using namespace std;

void print_vector(vector <int> input)
{
	cout << "(";
	
	for(auto i = input.begin(); i != input.end(); i++)
	{
		if (next(i) == input.end())
			cout << *i << ")" << endl;
		else
			cout << *i << ", ";
	}
}

int roll_dice(int num, int dice, int mod)
{
	int damage = 0;
	vector <int> results;

	for (int i = 0; i < num; i++)
	{
		int roll = rand() % dice + 1;
		results.push_back(roll);
		damage += roll;
	}

	if (num > 1)
		print_vector(results);	

	return damage + mod;
}

int take_action(std::vector<std::string> creature)
{
	int attack_mod = stoi(creature[ATTACK_VAR]);
	cout << "Attack: " << roll_dice(1,20,attack_mod) << endl;	// Roll attack

	std::string damage_roll = creature[DAM_VAR];
}

int main()
{
	srand(time(NULL));	// Generate random seed.

	string input;

	getline(cin, input);

	int * dam_values = read_dam(input);

	// cout << num << "d" << dice << " + " << mod << endl;

	cout << "Attack: " << roll_dice(1,20,0) << endl;
	cout << "Damage: " << roll_dice(dam_values[0],dam_values[1],dam_values[2]) << endl;

	return 0;
}
