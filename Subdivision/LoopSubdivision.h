#pragma once

#include "Subdivision.h"
#include "Point3d.h"
#include "Vertex.h"
#include "Face.h"
#include "HalfEdge.h"
#include "TwoManifold.h"

class LoopSubdivision
{
public:
	static void  subdivide(TwoManifold & parent, TwoManifold & child);


private:
	static HE_Vertex * setNewVertexOnExistingVertex(HE_Vertex * old, TwoManifold & child);
	static HE_Vertex * setNewVertexOnEdge(HE_HalfEdge * he,  TwoManifold & child);
	static HE_Texture * pointerForTexture(HE_Texture * t, TwoManifold & child);


	static const float a_n[10];
	//static int a_n[10] = { 0, 49/64, 25/64, 7/16, 33/64, 0.579533905, 5/8, 0.656825558, 0.679457521, 0.695934838};
	static const float a_e_2;
	static const float a_e_1;
};