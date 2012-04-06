#ifndef HALF_EDGE_H
#define HALF_EDGE_H

class HE_HalfEdge;

//class HE_Face;
#ifndef FACE_H
#include "Face.h"
#endif

//class HE_Vertex;
#ifndef VERTEX_H
#include "Vertex.h"
#endif

class HE_HalfEdge
{
public:
	HE_HalfEdge();
	void findPair();
	void setRing(HE_HalfEdge * he2, HE_HalfEdge * he3);

	HE_Vertex * start;
	HE_HalfEdge * pair;
	HE_HalfEdge * next;
	HE_HalfEdge * same_start;
	HE_Face * face;
	HE_Vertex * child;
};

#endif