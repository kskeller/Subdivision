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
	TwoManifold(){};
	~TwoManifold();
	std::string getFilename(int face);
	void paintObject();
	std::vector<HE_Vertex> vertices;
	std::vector<HE_Face> faces;
	std::vector<HE_HalfEdge> halfedges;
	std::vector<HE_Texture> texture;
	std::vector<std::string> texture_files;
	void constructFromFile(std::string filename);
	bool texture_avail;
	void applyTexture(std::string filnename);
	void changeTextureCoordinates(int face, float t1x, float t1y, float t2x, float t2y, float t3x, float t3y);
	void changeTextureIndices(int face, int texture);
	void writeToFile(std::string filename);
};