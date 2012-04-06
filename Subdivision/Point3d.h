#pragma once

class Point3d
{
public:
	float x;
	float y;
	float z;
	
	Point3d(void);
	Point3d(float x,float y,float z);
//	~Point3d(void);
	
	Point3d& operator+=(const Point3d& rhs);
	Point3d operator +(const Point3d& rhs) const;
	Point3d operator -(const Point3d& rhs) const;
	Point3d Point3d::operator*(const float rhs) const;
	Point3d& Point3d::operator *=(const float rhs);
	float length();
	void normalize();
	Point3d cross(const Point3d& rhs);

};