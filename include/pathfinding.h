#include <vector>

class Tile;

namespace Pathfinding
{
    class Node
    {
    public:
        Tile *tile;
        Node *parent;

        double G, H;

        Node(Tile *t, Node *p = nullptr) : tile{ t }, parent{ p }, G{ 0 }, H{ 0 } {};

        double getScore() {
            return G + H;
        };
    };

    std::vector<Tile *> aStar(Tile *start, Tile *end);
}