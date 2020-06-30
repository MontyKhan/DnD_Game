#include "csv_reader.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include <boost/algorithm/string.hpp>

using namespace std;

// Parses through csv file line by line and returns the data
// in vector of vector of strings.
std::vector<std::vector<std::string> > CSV_Reader::getData()
{
	std::ifstream file(fileName);
	std::vector<std::vector<std::string> > dataList;
	std::string line = "";
	getline(file, line);
	// Iterate through each line and split the content using delimeter
	while (getline(file, line))
	{
        	std::vector<std::string> vec;
        	boost::algorithm::split(vec, line, boost::is_any_of(delimeter));
        	dataList.push_back(vec);
    	}
    	// Close the File
    	file.close();
    	return dataList;
}

std::vector<std::vector<std::string>> load_file(std::string filepath)
{
	// Create an object of CSV_Reader	
	CSV_Reader reader(filepath);
	// Get the data from the CSV file
	std::vector<std::vector<std::string>> dataList = reader.getData();

	return dataList;
}

int main()
{
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
}
