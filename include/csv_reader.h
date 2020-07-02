#include <iostream>
#include <string>
#include <vector>

extern std::vector<std::vector<std::string>> load_file(std::string filepath);

// Class to read data from a CSV file
class CSV_Reader
{
	std::string fileName;
	std::string delimeter;

public:
	CSV_Reader(std::string filename, std::string delim = ",") :
		fileName(filename), delimeter(delim)
	{}

	// Function to fetch data from CSV file
	std::vector<std::vector<std::string>> getData();
};

