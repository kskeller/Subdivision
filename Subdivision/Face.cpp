#include "Face.h"
//#include "Defines.h"

HE_Face::HE_Face()
:he1(0)
, t1(0)
, t2(0)
, t3(0)
{}

void HE_Face::setNormal()
{
	Point3d v1(he1->start->x, he1->start->y, he1->start->z);
	Point3d v2(he1->next->start->x, he1->next->start->y, he1->next->start->z);
	Point3d v3(he1->next->next->start->x, he1->next->next->start->y, he1->next->next->start->z);
	
	normal = (v2-v1).cross(v3-v1);
	normal.normalize();
}
