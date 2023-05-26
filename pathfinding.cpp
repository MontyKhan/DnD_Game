#include <map>
#include <algorithm>

#include "tile.h"
#include "location.h"
#include "tools.h"
#include "pathfinding.h"

#include "battlemap.h"

using namespace Pathfinding;


bool checkParametersOkay(Tile *start, Tile *end)
{
    if (start->getParentMap() != start->getParentMap())
        throw std::exception("Tiles have different maps!");
    else if (start->getParentMap()->isValid(start->getCoordinates()))
        throw std::exception("Start tile isn't on map!");
    else if (start->getParentMap()->isValid(end->getCoordinates()))
        throw std::exception("End tile isn't on map!");
    else if (start == end)
        throw std::exception("End is the same as start!");
    else if (!end->isUnblocked())
        throw std::exception("End tile is blocked!");
    else
        return true;

    // Something gone wrong
    return false;
}

Node *findNodeInSet(std::vector<Node *> &set, Tile *tile)
{
    for (const auto it : set)
    {
        if (it->tile == tile) return it;
    }

    return nullptr;
}

std::vector<Tile *> aStar(Tile *start, Tile *end)
{
    Node *current = nullptr;

    const std::vector<Tile *> empty;
    std::vector<Tile *> visited;

    if (!checkParametersOkay(start, end))
        return empty;

    /* Set up sets */
    std::vector<Node *> openSet, closedSet;
    openSet.reserve(100);
    closedSet.reserve(100);

    openSet.push_back(new Node(start));

    while (!openSet.empty())
    {
        current = openSet.front();

        for (const auto it : openSet)
        {
            if (it->getScore() <= current->getScore())
                current = it;

        }

        // Exit if we've reached our destination
        if (current->tile == end)
            break;

        // Update sets. Add visited tile to closed set.
        closedSet.push_back(current);
        eraseItem(openSet, current);
        
        auto freeNeighbours = current->tile->getFreeNeighbours();
        for (auto neighbour : freeNeighbours)
        {
            if (findNodeInSet(closedSet, neighbour))
                continue;

            double totalCost = current->G + (current->tile->isDiagonal(neighbour) ? 1.5 : 1);
            
            Node *successor = findNodeInSet(openSet, neighbour);

            if (successor == nullptr)
            {
                successor = new Node(neighbour, current);
                successor->G = totalCost;
                successor->H = neighbour->calculateHValue(end);
                openSet.push_back(successor);
            }
            else if (totalCost < successor->G)
            {
                successor->parent = current;
                successor->G = totalCost;
            }
        }
    }

    while (current != nullptr)
    {
        visited.push_back(current->tile);
        current = current->parent;
    }

    std::reverse(visited.begin(), visited.end());

    return visited;
}