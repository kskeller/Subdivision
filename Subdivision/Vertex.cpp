#include "Vertex.h"
//#include "Defines.h"

HE_Vertex::HE_Vertex()
:he(0)
, child(0)
{}

//change the problem
void HE_Vertex::attachHalfEdge(HE_HalfEdge * successor)
{
	if (he == 0)
	{
		he = successor;
	}
	else
	{
		HE_HalfEdge * predecessor = he;
		while (predecessor->same_start)
		{
			predecessor = predecessor->same_start;
		}	
		predecessor->same_start = successor;
	}
}

void HE_Vertex::countAdjacentEdges()
{
	HE_HalfEdge * temp = he;
	int i = 0;
	while (temp != 0)
	{
		i++;
		temp = temp->same_start;	
	}
	adjacent_edges = i;
}

Point3d  HE_Vertex::averageNeighbors()
{
	HE_HalfEdge * temp = he;
	Point3d average;
	while (temp != 0)
	{
		average += Point3d(temp->next->start->x, temp->next->start->y, temp->next->start->z);
		temp = temp->same_start;	
	}
	average *= (1.0f/adjacent_edges);
	return average;
}

void HE_Vertex::setVertexNormal()
{
	HE_HalfEdge * temp = he;
	while (temp != 0)
	{
		vertexNormal += temp->face->normal;
		temp = temp->same_start;	
	}
	vertexNormal.normalize();
}
