#include <iostream>
#include <string>
#include <vector>

extern std::vector<std::vector<std::string>> load_file(std::string filepath);

// Class to read data from a CSV file
class CSV_Reader
{
	std::string fileName;		// Filepath
	std::string delimeter;		// Character seperating strings.

public:
	// Constructor, taking the filepath and the delimeter.
	CSV_Reader(std::string filename, std::string delim = ",") :
		fileName(filename), delimeter(delim)
	{}

	// Function to fetch data from CSV file
	std::vector<std::vector<std::string>> getData();
};

