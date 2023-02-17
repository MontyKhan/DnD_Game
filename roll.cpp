#include "combatant.h"
#include "tools.h"

using namespace std;


/* brief:	Override function. Prints roll to screen in format %d% + %.
		Friend function of roll.
   param:	&out - Address of output stream.
		&r - roll to print.
   returns:	output stream.
*/
std::ostream & operator << (std::ostream &out, const Roll &r)
{
	out << r.num << "d" << r.dice << " + " << r.mod;
	return out;
}

/* brief:	Constructor for a roll based on the format %d% + %.
   param:	std::string input, in the format %d% + %.
   returns:	Nothing, as constructor.
*/
Roll::Roll(std::string input)
{
	int d = input.find("d");			// Find number of characters in the 'd' char is.
	int dice_length = input.length() - d + 1;	// Assign length of dice string to one less than the number of chars in d is.

	int plus = input.find(" + ") + 2;		// Find number of characters in the " + " string is.
	int plus_length = input.length() + 1;		// Assign length of string up to " + " to full length of string plus one.
	mod = 0;					// By default, set modifier to zero.

	// If plus is greater than 1, means it's present.
	// Change value of plus_length to number of characters till " + ".
	// Assign value of mod to string after " + ".
	if (plus > 1) {
		plus_length = input.length() - plus;
		mod = stoi(input.substr(plus+1, input.length() - plus_length));
	}

	num = stoi(input.substr(0,d));					// Convert string before "d" to an int, num.
	dice = stoi(input.substr(d+1, plus_length - dice_length));	// Convert string between "d" and " + " to an int, dice. 
}
