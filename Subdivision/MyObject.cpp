#include "MyObject.h"
#include "LoopSubdivision.h"
#include "Face.h"

MyObject::MyObject(std::string filename)
: no_subdivisions(0)
, max_subdivisions(5)
, texture(false)
{
	//TwoManifold * tm  = ;
	levels_subdivision.reserve(max_subdivisions + 1);
	levels_subdivision.push_back(TwoManifold());
	levels_subdivision.back().texture_avail = texture;
	levels_subdivision.back().constructFromFile(filename);
}

MyObject::~MyObject()
{}

TwoManifold * MyObject::getSubdivision(int level)
{
	while (level > no_subdivisions)
	{
		levels_subdivision.push_back(TwoManifold());
		no_subdivisions++;
	}
	return (&(levels_subdivision[level]));
}

void MyObject::makeVertexList(int lvl, std::vector<float> &x, std::vector<float> &y, std::vector<float> &z, std::vector<Point3d> &n, bool facenormal)
{
	if (lvl <= max_subdivisions)
	{
		if (lvl > no_subdivisions)
		{
			while (lvl > no_subdivisions)
			{
				levels_subdivision.push_back(TwoManifold());
				//LoopSubdivision::subdivide(levels_subdivision[lvl-1], levels_subdivision[lvl]);
				LoopSubdivision::subdivide(levels_subdivision[no_subdivisions], levels_subdivision[no_subdivisions+1]);
				no_subdivisions++;
			}
		}

		int no_faces = levels_subdivision[lvl].faces.size();
		x.clear();
		x.reserve(no_faces * 3);
		y.clear();
		y.reserve(no_faces * 3);
		z.clear();
		z.reserve(no_faces * 3);
		n.clear();
		if (facenormal)
		{
			n.reserve(no_faces);
		}
		else
		{
			n.reserve(no_faces * 3);
		}
		std::vector<HE_Face> & f = levels_subdivision[lvl].faces;
		for (int i = 0; i<no_faces; i++)
		{
			x.push_back(f[i].he1->start->x);
			x.push_back(f[i].he1->next->start->x);
			x.push_back(f[i].he1->next->next->start->x);
			y.push_back(f[i].he1->start->y);
			y.push_back(f[i].he1->next->start->y);
			y.push_back(f[i].he1->next->next->start->y);
			z.push_back(f[i].he1->start->z);
			z.push_back(f[i].he1->next->start->z);
			z.push_back(f[i].he1->next->next->start->z);
			if (facenormal)
			{
				n.push_back(f[i].normal);
			} 
			else
			{
				n.push_back(f[i].he1->start->vertexNormal);
				n.push_back(f[i].he1->next->start->vertexNormal);
				n.push_back(f[i].he1->next->next->start->vertexNormal);
			}
		}
	}
}

//to be called after makeVertexList...
void MyObject::makeTextureList(int lvl, std::vector<int> &tex_indices, std::vector<HE_Texture> &tex_coords)
{
	tex_indices.clear();
	tex_coords.clear();

	std::vector<HE_Face> & f = levels_subdivision[lvl].faces;

	int no_faces = f.size();
	tex_indices.reserve(no_faces);
	tex_coords.reserve(no_faces * 3);

	for (int i = 0; i<no_faces; i++)
	{
		tex_indices.push_back(f[i].texture_id);
		tex_coords.push_back(*(f[i].t1));
		tex_coords.push_back(*(f[i].t2));
		tex_coords.push_back(*(f[i].t3));
	}
}


//Only works for lvl == 0 find solution
void MyObject::assignTexture(std::string filename)
{
	texture = true;
	levels_subdivision[0].applyTexture(filename);
}

std::string MyObject::getTextureName(int lvl, int face)
{
	return levels_subdivision[lvl].getFilename(face);
}

void MyObject::changeTextureCoordinates(int lvl, int face, float t1x, float t1y, float t2x, float t2y, float t3x, float t3y)
{
	levels_subdivision[lvl].changeTextureCoordinates(face, t1x, t1y, t2x, t2y, t3x, t3y);
}

void MyObject::changeTextureIndices(int lvl, int face, int texture)
{
	levels_subdivision[lvl].changeTextureIndices(face, texture);
}

void MyObject::writeToFile(int lvl, std::string filename)
{
	if (lvl < levels_subdivision.size())
	{
		levels_subdivision[lvl].writeToFile(filename);
	}
}