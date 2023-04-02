#ifndef LOAD_FILE_H
#define LOAD_FILE_H

#include <map>
#include "object.h"
#include "rapidxml/rapidxml_utils.hpp"

using namespace rapidxml;

// Parses through an xml formatted .enctr file for actors.
std::vector<Object*> interpret_nodes(const char* filepath);

#endif
