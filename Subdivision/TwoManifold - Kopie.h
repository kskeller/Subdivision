#pragma once

#include <list>
#include <string>
#include <vector>
//#include "HalfEdgeDataStructure.h"
#include "Face.h"
#include "HalfEdge.h"
#include "Vertex.h"

class TwoManifold
{
public:
	TwoManifold(std::string filename);
	TwoManifold();
	~TwoManifold();
	void paintObject();
	std::vector<HE_Vertex *> vertices;
	std::vector<HE_Face *> faces;
	std::vector<HE_HalfEdge*> halfedges;
	std::vector<HE_Texture*> texture;
private:
	void constructFromFile(std::string filename);

};