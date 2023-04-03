#include "tools.h"
#include "csv_reader.h"
#include "display.h"
#include <vector>
#include <sstream>

using namespace std;

/* brief:	Declare CSV_Reader object, and load data from .csv file at filepath into a vector of vectors of strings.
   param:	filepath - A relative address pointing to the .csv file.
   returns:	A vector of vectors of strings containing contents of file.
*/
std::vector<std::vector<std::string>> load_file(std::string filepath)
{
	// Create an object of CSV_Reader	
	CSV_Reader reader(filepath);
	// Get the data from the CSV file
	std::vector<std::vector<std::string>> dataList = reader.getData();

	return dataList;
}

/* brief:	Converts a string describing a damage type into the corresponding enum.
   param:	str, the string containing a damage type.
   returns:	The corresponding damage type as an enum.
		If there are no matches, it defaults to bludgeoning.
*/
type get_damage_type(std::string str)
{
	if (str == "acid")
		return acid;
	else if (str == "bludgeoning")
		return bludgeoning;
	else if (str == "cold")
		return cold;
	else if (str == "fire")
		return fire;
	else if (str == "force")
		return force;
	else if (str == "lightning")
		return lightning;
	else if (str == "necrotic")
		return necrotic;
	else if (str == "piercing")
		return piercing;
	else if (str == "poison")
		return poison;
	else if (str == "psychic")
		return psychic;
	else if (str == "radiant")
		return radiant;
	else if (str == "slashing")
		return slashing;
	else if (str == "thunder")
		return thunder;
	else
		return bludgeoning;
}

/* brief: 	Extract the name of value of an xml node and assign to strings.
   param: 	*name - A string to store the name in, called by reference.
	  	*value - A string to store the value in, called by reference.
	  	node - The node containing the information.
   returns:	Nothing, as calling by reference.
*/
void node_to_str(std::string &name, std::string &value, xml_node<> *node)
{
	// Likely a better solution than this, but documentation is currently down.
	std::stringstream ss_value, ss_name;
	ss_value << node->value();
	ss_name << node->name();
	value = ss_value.str();
	name = ss_name.str();
}

/* brief:	Print a vector of ints to the screen.
		Should be updated to work for vectors of any class.
   param:	input - A vector of ints.
   returns:	Nothing.
*/
void print_vector(vector <int> input)
{
	cout << "(";						// Prints a "(" for readability.
	
	// Iterate through vector, printing each value to screen.
	// If last value in vector, follow with ")". Otherwise, follow with ", ".
	for(auto i = input.begin(); i != input.end(); i++)
	{
		if (next(i) == input.end())
			cout << *i << ")" << endl;
		else
			cout << *i << ", ";
	}
}

std::vector<std::string> split_string(std::string& str, std::string delim)
{
	size_t pos = 0;
	std::vector<std::string> arr;

	while ((pos = str.find(delim)) != std::string::npos) {
		arr.push_back(str.substr(0, pos));
		str.erase(0, pos + 1);	// +1 represents delimiter
	}

	// Check if any information after final delimiter.
	if (str.size() > 0)
		arr.push_back(str);

	return arr;
}