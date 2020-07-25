#include "include/pathfinding.h"
#include <boost/algorithm/string.hpp>
#include <string>
#include <vector>

using namespace std;


/* brief:	Override function. Prints coordinates in format %, %, %.
		Friend function of location.
   param:	&out - Address of output stream.
		&r - coordinates to print.
   returns:	output stream.
*/
std::ostream & operator << (std::ostream &out, const location &l)
{
	out << l.x << ", " << l.y << ", " << l.z;
	return out;
}

/* brief:	Sets values for x, y and z based on a string.
   param:	str, in the format %,%,%
   returns:	Nothing, as constructor.
*/
location::location(std::string str)
{
	std::vector<std::string> vals;

	boost::algorithm::split(vals,str,boost::is_any_of(","));

	x = stoi(vals[0]);
	y = stoi(vals[1]);
	z = stoi(vals[2]);
}

/* brief:	Convert three sets of distances to one.
   param:	x - Distance along x axis.
		y - Distance along y axis.
		z - Distance along z axis.
   return:	Distance between two points in euclidean space.
*/
int location::find_distance(location coords)
{
	int x_d = abs(x - coords.getX());
	int y_d = abs(y - coords.getY());
	int z_d = abs(z - coords.getZ());

	int d = (x_d*x_d) + (y_d*y_d) + (z_d*z_d);

	return d;
}
