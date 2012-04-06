#pragma once
#include <vector>
#include "Point3d.h"
#include "TwoManifold.h"
#include "LoopSubdivision.h"


class MyObject
{
public:
	MyObject(std::string filename);
	virtual ~MyObject();
	TwoManifold * getSubdivision(int level);
	void makeVertexList(int lvl, std::vector<float> &x, std::vector<float> &y, std::vector<float> &z , std::vector<Point3d> &n, bool facenormal);
	void makeTextureList(int lvl, std::vector<int> &tex_indices, std::vector<HE_Texture> &texture_coords);
	//void giveTextureFiles(int lvl, std::vector<std::string> &texture_files
	void assignTexture(std::string filename);
	void changeTextureCoordinates(int lvl, int face, float t1x, float t1y, float t2x, float t2y, float t3x, float t3y);
	void changeTextureIndices(int lvl, int face, int texture);

	std::string getTextureName(int lvl, int face);
	void writeToFile(int lvl, std::string filename);

	//Return to private later
	std::vector<TwoManifold> levels_subdivision;
private:
	
	int no_subdivisions;
	int max_subdivisions;
	bool texture;
};