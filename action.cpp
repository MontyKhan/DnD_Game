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

int main()
{
	srand(time(NULL));	// Generate random seed.

	string input;

	getline(cin, input);
	int deliminator = input.find("d");
	int dice_length = input.length() - deliminator + 1;

	int num = stoi(input.substr(0,deliminator));
	int dice = stoi(input.substr(deliminator+1, dice_length));

	cout << "Attack: " << roll_dice(1,20,0) << endl;
	cout << "Damage: " << roll_dice(num,dice,0) << endl;

	return 0;
}
