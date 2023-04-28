#pragma once
#include <map>

enum class Faction {
    none,
    player,
    goblin,
    drow,
    orcs
};

const std::map<std::string, Faction> factionLookup{
    {"none", Faction::none},
    {"player", Faction::player},
    {"goblin", Faction::goblin},
    {"drow", Faction::drow},
    {"orcs", Faction::orcs},
};