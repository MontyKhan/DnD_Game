#include "pathfinding.h"

using namespace std;

int find_euc(int x, int y, int h)
{
	int d = sqrt(x*x + y*y + h*h);
	return d;
}

int main()
{
	cout << find_euc(9,3,0) << endl;
}
