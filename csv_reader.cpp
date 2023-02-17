#include "csv_reader.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include "tools.h"

using namespace std;

/* brief: 	Parse through .csv file at fileName line by line and transfer data to a vector of strings.
   param: 	none
   return: 	A vector of vectors of strings containing contents of file.
*/
std::vector<std::vector<std::string> > CSV_Reader::getData()
{
	std::ifstream file(fileName);						// Open file with address at fileName.
	std::vector<std::vector<std::string> > dataList;			// Declare vector of vectors of strings.
	std::string line = "";							// Declare empty string.

	getline(file, line);							// Get first line of file.

	// Iterate through each line and split the content using delimeter
	while (getline(file, line))
	{
		std::vector<std::string> vec = split_string(line, delimeter);
        dataList.push_back(vec);
    }

    // Close the File
    file.close();
    return dataList;
}

