#ifndef VERTEX_H
#define VERTEX_H

class HE_Vertex;

//class HE_Face;
#ifndef FACE_H
#include "Face.h"
#endif

//class HE_HalfEdge;
#ifndef HALF_EDGE_H
#include "HalfEdge.h"
#endif

#include "Point3d.h"

class HE_Vertex
{
public:
	HE_Vertex();
	void attachHalfEdge(HE_HalfEdge * he);
	void countAdjacentEdges();

	int id;
	int adjacent_edges;

	float x;
	float y;
	float z;

	HE_HalfEdge * he;
	HE_Vertex * child;
	Point3d vertexNormal;
		
	Point3d averageNeighbors();
	void setVertexNormal();

};

#endif