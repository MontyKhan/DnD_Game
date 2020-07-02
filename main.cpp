#include "include/csv_reader.h"
#include "include/combatant.h"

using namespace std;

std::vector<std::vector<std::string>> load_file(std::string filepath)
{
	// Create an object of CSV_Reader	
	CSV_Reader reader(filepath);
	// Get the data from the CSV file
	std::vector<std::vector<std::string>> dataList = reader.getData();

	return dataList;
}

int main() {
	srand(time(NULL));	// Generate random seed.

	combatant C("Test", 1, 2, 3, 4, 5, "6d7 + 8");	// Create character

	C.print_stats();	// Print character stats to screen

	C.take_action();	// Roll attack and damage.

	std::string filepath = "./stats/encounter1.csv";

	std::vector<std::vector<std::string>> dataList = load_file(filepath);

    	// Print the content of row by row on screen
    	for(std::vector<std::string> vec : dataList)
    	{
        	for(std::string data : vec)
        	{
        		std::cout<<data << " , ";
        	}
        	std::cout<<std::endl;
    	}

    	return 0;
};
