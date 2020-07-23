#include <iostream>
#include "./include/rapidxml/rapidxml_utils.hpp"

using namespace rapidxml;
using namespace std;

void interpret_node(xml_node<> *node)
{
	for (xml_node<> *child = node->first_node(); child; child = child->next_sibling())	// Monster
	{
		xml_node<> *grandchild = child->first_node();	// Name
		if (grandchild)					// If has name, check contents of monster
			interpret_node(child);
		else
			std::cout << "Node " << node->name() << " has value " << node->value() << endl;	// Print contents of node
	}
}

int main()
{
	std::string filepath = "./stats/encounter1.enctr";

	rapidxml::file<> xmlFile("./stats/encounter1.enctr"); // Default template is char
	//rapidxml::file<> xmlFile("./stats/test.enctr"); // Default template is char
    	rapidxml::xml_document<> doc;
    	doc.parse<0>(xmlFile.data());

	std::cout << "Name of my first node is: " << doc.first_node()->name() << "\n";
	xml_node<> *original = doc.first_node();
	interpret_node(doc.first_node());	// Encounter
	/*
	for (xml_node<> *attr = original->first_node();
     		attr; attr = attr->next_sibling())
	{
    		std::cout << "Node foobar has attribute " << attr->name() << " ";
    		std::cout << "with value " << attr->value() << "\n";
		for (xml_node<> *child = attr->first_node();
			child; child = child->next_sibling())
		{
			std::cout << "Child node has attribute " << child->name() << " ";
			std::cout << "with value " << child->value() << "\n";
		}
	}
	*/
}
