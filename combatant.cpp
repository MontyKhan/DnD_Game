#include "combatant.h"

using namespace std;

// Convert string in format %d% + % into three ints.
roll combatant::read_dam(std::string input)
{
	roll values;

	int d = input.find("d");
	int dice_length = input.length() - d + 1;

	int plus = input.find(" + ") + 2;
	int plus_length = input.length() + 1;
	damage.mod = 0;

	if (plus > 1) {
		plus_length = input.length() - plus;
		damage.mod = stoi(input.substr(plus+1, input.length() - plus_length));
	}

	damage.num = stoi(input.substr(0,d));
	damage.dice = stoi(input.substr(d+1, plus_length - dice_length));

	return values;
}

// Empty main function
int main() {
	
};
