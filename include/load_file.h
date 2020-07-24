#include "combatant.h"
#include "rapidxml/rapidxml_utils.hpp"

#ifndef LOAD_FILE_H
#define LOAD_FILE_H

using namespace rapidxml;

// Parses through an xml formatted .enctr file for combatants.
std::vector<combatant> interpret_nodes(const char* filepath);

#endif
