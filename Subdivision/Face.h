#ifndef FACE_H
#define FACE_H

class HE_Face;

#ifndef HALF_EDGE_H
#include "HalfEdge.h"
#endif

#ifndef VERTEX_H
#include "Vertex.h"
#endif

#include "Texture.h"
#include "Point3d.h"

class HE_Face
{
public:
	HE_Face();
	void setNormal();

	HE_HalfEdge *he1;
	HE_Texture *t1, *t2, *t3;
	int texture_id;
	Point3d normal;
};

#endif