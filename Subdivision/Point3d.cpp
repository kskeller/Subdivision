#include "Point3d.h"
#include "math.h"

Point3d::Point3d(void)
:x(0)
,y(0)
,z(0)
{}

Point3d::Point3d(float a,float b,float c)
: x(a)
, y(b)
, z(c)
{
}

Point3d& Point3d::operator +=(const Point3d& rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

Point3d Point3d::operator +(const Point3d& rhs) const
{
	return Point3d(x + rhs.x, y+rhs.y, z+rhs.z);
}

Point3d Point3d::operator -(const Point3d& rhs) const
{
	return Point3d(x - rhs.x, y-rhs.y, z-rhs.z);
}

Point3d Point3d::operator*(const float rhs)const
{
	return Point3d(x * rhs, y * rhs, z * rhs);
}

Point3d& Point3d::operator *=(const float rhs)
{
	x*=rhs;
	y*=rhs;
	z*=rhs;
	return *this;
}

float Point3d::length()
{
	return sqrt(x*x + y*y + z*z);
}

void  Point3d::normalize()
{
	float l = length();
	if (l != 0.0f)
	{
		x /= l;
		y /= l;
		z /= l;
	}
}
	
Point3d Point3d::cross(const Point3d& rhs)
{
	return Point3d(y *rhs.z - z*rhs.y, z*rhs.x - x*rhs.z, x*rhs.y - y*rhs.x);
}