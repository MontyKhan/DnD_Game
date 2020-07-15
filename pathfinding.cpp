#include "pathfinding.h"

using namespace std;

/* brief:	Convert three sets of distances to one.
   param:	x - Distance along x axis.
		y - Distance along y axis.
		z - Distance along z axis.
   return:	Distance between two points in euclidean space.
*/
int find_euc(int x, int y, int h)
{
	int d = sqrt(x*x + y*y + h*h);
	return d;
}
