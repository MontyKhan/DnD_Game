#include "pathfinding.h"
#include "tools.h"
#include <string>
#include <vector>
#include <math.h>

using namespace std;


/* brief:	Override function. Prints coordinates in format %, %, %.
		Friend function of location.
   param:	&out - Address of output stream.
		&r - coordinates to print.
   returns:	output stream.
*/
std::ostream & operator << (std::ostream &out, const location &l)
{
	out << "(" << l.x << ", " << l.y << ", " << l.z << ")";
	return out;
}

/* brief:	Compares two sets of location data, returns True if equal.
   param:	&rhs - First location to compare.
		&lhs - Second location to compare.
   returns:	True if equal, false otherwise.
*/
bool operator == (const location &rhs, const location &lhs)
{
	return ((rhs.x == lhs.x) && (rhs.y == lhs.y) && (rhs.z == lhs.z));
}

/* brief:	Compare two sets of location data, returns False is equal.
   param:	&rhs - First location to compare.
		&lhs - Second location to compare.
   returns:	True if unequal, false otherwise.
*/
bool operator != (const location &rhs, const location &lhs)
{
	return !(rhs == lhs);
}

/* brief:	Add two sets of location data. To the right and up are considered positive directions.
		Down and left are considered negative.
   param:	&rhs - First location to sum.
		&lhs - Second location to sum.
   returns:	The sum of the two locations.
*/
location operator + (const location &rhs, const location &lhs)
{
	location sum;

	// Sum all components
	sum.x = rhs.x + lhs.x;
	sum.y = rhs.y + lhs.y;
	sum.z = rhs.z + lhs.z;

	return sum;
}

/* brief:	Subtact one location datum from another. To the right and up are considered positive directions.
		Down and left are considered negative.
   param:	&rhs - Location to subtract from.
		&lhs - Location to subtract.
   returns:	The sum of the two locations.
*/
location operator - (const location &rhs, const location &lhs)
{
	location sum;

	// Sum all components
	sum.x = rhs.x - lhs.x;
	sum.y = rhs.y - lhs.y;
	sum.z = rhs.z - lhs.z;

	return sum;
}

/* brief:	Sets values for x, y and z based on a string.
   param:	str, in the format %,%,%
   returns:	Nothing, as constructor.
*/
location::location(std::string str)
{
	std::vector<std::string> vals = split_string(str, ",");

	x = stoi(vals[0]);
	y = stoi(vals[1]);
	z = stoi(vals[2]);
}

float find_euc(location rhs, location lhs)
{
	float x_d = abs(float(rhs.x) - float(lhs.x));
	float y_d = abs(float(rhs.y) - float(lhs.y));
	float z_d = abs(float(rhs.z) - float(lhs.z));

	float d = sqrt((x_d*x_d) + (y_d*y_d) + (z_d*z_d));

	return d;
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

	int d = sqrt((x_d*x_d) + (y_d*y_d) + (z_d*z_d));

	return d;
}
