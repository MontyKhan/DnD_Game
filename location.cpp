#include "location.h"
#include "tools.h"
#include <string>
#include <vector>
#include <math.h>

using namespace std;


/* brief:	Override function. Prints coordinates in format %, %, %.
		Friend function of Location.
   param:	&out - Address of output stream.
		&r - coordinates to print.
   returns:	output stream.
*/
std::ostream & operator << (std::ostream &out, const Location &l)
{
	out << "(" << l.x << ", " << l.y << ", " << l.z << ")";
	return out;
}

/* brief:	Compares two sets of Location data, returns True if equal.
   param:	&rhs - First Location to compare.
		&lhs - Second Location to compare.
   returns:	True if equal, false otherwise.
*/
bool operator == (const Location &rhs, const Location &lhs)
{
	return ((rhs.x == lhs.x) && (rhs.y == lhs.y) && (rhs.z == lhs.z));
}

/* brief:	Compare two sets of Location data, returns False is equal.
   param:	&rhs - First Location to compare.
		&lhs - Second Location to compare.
   returns:	True if unequal, false otherwise.
*/
bool operator != (const Location &rhs, const Location &lhs)
{
	return !(rhs == lhs);
}

/* brief:	Add two sets of Location data. To the right and up are considered positive directions.
		Down and left are considered negative.
   param:	&rhs - First Location to sum.
		&lhs - Second Location to sum.
   returns:	The sum of the two Locations.
*/
Location operator + (const Location &rhs, const Location &lhs)
{
	Location sum;

	// Sum all components
	sum.x = rhs.x + lhs.x;
	sum.y = rhs.y + lhs.y;
	sum.z = rhs.z + lhs.z;

	return sum;
}

/* brief:	Subtact one Location datum from another. To the right and up are considered positive directions.
		Down and left are considered negative.
   param:	&rhs - Location to subtract from.
		&lhs - Location to subtract.
   returns:	The sum of the two Locations.
*/
Location operator - (const Location &rhs, const Location &lhs)
{
	Location sum;

	// Sum all components
	sum.x = rhs.x - lhs.x;
	sum.y = rhs.y - lhs.y;
	sum.z = rhs.z - lhs.z;

	return sum;
}

/* brief:	Multiple coordinates by numerical value
   param:   &loc - Location value
			val - Numerical value
   returns: The product of the location and the value
			e.g. (1,1,1) * 3 = (3,3,3)
**/
Location operator * (const Location &loc, const double val)
{
	Location prod;

	prod.x = loc.x * val;
	prod.y = loc.y * val;
	prod.z = loc.z * val;

	return prod;
}


/* brief:	Sets values for x, y and z based on a string.
   param:	str, in the format %,%,%
   returns:	Nothing, as constructor.
*/
Location::Location(std::string str)
{
	std::vector<std::string> vals = split_string(str, ",");

	x = stoi(vals[0]);
	y = stoi(vals[1]);
	z = stoi(vals[2]);
}

float find_euc(Location rhs, Location lhs)
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
int Location::find_distance(Location coords)
{
	int x_d = abs(x - coords.getX());
	int y_d = abs(y - coords.getY());
	int z_d = abs(z - coords.getZ());

	int d = sqrt((x_d*x_d) + (y_d*y_d) + (z_d*z_d));

	return d;
}
