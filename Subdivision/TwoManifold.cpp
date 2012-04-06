#include "TwoManifold.h"
#include <fstream>
//#include <GL/glut.h>

TwoManifold::TwoManifold(std::string filename)
: texture_avail(false)
{
	constructFromFile(filename);
}

TwoManifold::~TwoManifold()
{
}


void TwoManifold::constructFromFile(std::string filename)
{
	std::fstream filestream(filename.c_str(), std::fstream::in);
	std::string vert;
	int no_vertices;
	filestream >> vert >> no_vertices;
	vertices.reserve(no_vertices);

	float x, y, z;
	std::string temp;
	filestream >> temp;
	std::string temp2("(v");
	int i =0;
	while (temp == temp2)
	{
		filestream >> x >> y >> z;
		vertices.push_back(HE_Vertex());
		vertices[i].id = i;
		vertices[i].x = x*10;
		vertices[i].y = y*10;
		vertices[i].z = z*10;

		filestream.ignore(10, ')');
		filestream >> temp;

		i++;
	}

	std::string triangles;
	int no_faces;
	filestream >> vert >> no_faces;
	faces.reserve(no_faces);
	halfedges.reserve(3*no_faces);
	
	temp2 = "(t";
	int v1, v2, v3;
	filestream >> temp;
	i=0;
	while (temp == temp2)
	{
		filestream >> v1 >> v2 >> v3;
			
		faces.push_back(HE_Face());
		halfedges.push_back(HE_HalfEdge());
		halfedges.push_back(HE_HalfEdge());
		halfedges.push_back(HE_HalfEdge());

		faces[i].he1 = &(halfedges[3*i]);

		halfedges[3*i].face = &(faces[i]);
		halfedges[3*i].next = &(halfedges[3*i +1]);
		halfedges[3*i].start = &(vertices[v1]);
		vertices[v1].attachHalfEdge(&(halfedges[3*i]));

		halfedges[3*i+1].face = &(faces[i]);
		halfedges[3*i+1].next = &(halfedges[3*i +2]);
		halfedges[3*i+1].start = &(vertices[v2]);
		vertices[v2].attachHalfEdge(&(halfedges[3*i+1]));

		halfedges[3*i+2].face = &(faces[i]);
		halfedges[3*i+2].next = &(halfedges[3*i]);
		halfedges[3*i+2].start = &(vertices[v3]);
		vertices[v3].attachHalfEdge(&(halfedges[3*i+2]));

		filestream.ignore(10, ')');
		filestream >> temp;
		i++;
	}
	filestream.close();

	for (int j=0; j<vertices.size(); j++) 
	{
		vertices[j].countAdjacentEdges();
	}

	for (int j=0; j<halfedges.size(); j++) 
	{
		halfedges[j].findPair();
	}

	for (int j=0; j<faces.size(); j++) 
	{
		faces[j].setNormal();
	}
	for (int j=0; j<vertices.size(); j++) 
	{
		vertices[j].setVertexNormal();
	}
	
}


void TwoManifold::applyTexture(std::string filename)
{
	texture_avail=true;
	texture.clear();

	std::fstream filestream(filename.c_str(), std::fstream::in);
	std::string names;
	int no_names;
	filestream >> names >> no_names;
	vertices.reserve(no_names);
	
	std::string current_name;
	std::string temp;
	filestream >> temp;
	std::string temp2("(f");
	int i =0;
	while (temp == temp2)
	{
		filestream >> current_name;
		texture_files.push_back(current_name);
		
		filestream.ignore(10, ')');
		filestream >> temp;

		i++;
	}

	std::string triangles;
	int no_faces;
	filestream >> triangles >> no_faces;
	
	if (no_faces != faces.size())
	{
		throw "Doesn't work";
	}
	texture.reserve(no_faces * 3);
	temp2 = "(t";
	int tex;
	float s1, t1, s2, t2, s3, t3;
	filestream >> temp;
	i=0;
	while (temp == temp2)
	{
		filestream >> tex >> s1 >> t1 >> s2 >> t2 >> s3 >> t3;
		faces[i].texture_id = tex;
		texture.push_back(HE_Texture(s1, t1));
		faces[i].t1 = &(texture.back());
		texture.push_back(HE_Texture(s2, t2));
		faces[i].t2 = &(texture.back());
		texture.push_back(HE_Texture(s3, t3));
		faces[i].t3 = &(texture.back());
		
		filestream.ignore(10, ')');
		filestream >> temp;

		i++;
	}
	filestream.close();

}
		
std::string TwoManifold::getFilename(int face)
{
	return texture_files[faces[face].texture_id];
}

void TwoManifold::changeTextureCoordinates(int face_no, float t1x, float t1y, float t2x, float t2y, float t3x, float t3y)
{
	if (face_no < faces.size())
	{
		faces[face_no].t1->s = t1x;
		faces[face_no].t1->t = t1y;
		faces[face_no].t2->s = t2x;
		faces[face_no].t2->t = t2y;
		faces[face_no].t3->s = t3x;
		faces[face_no].t3->t = t3y;
	}
}

void TwoManifold::changeTextureIndices(int face, int texture)
{
	faces[face].texture_id = texture;
}

void TwoManifold::writeToFile(std::string filename)
{
	
	std::fstream filestream(filename.c_str(), std::fstream::out);
	filestream << "(images " << texture_files.size() << "\n";
	for (int i = 0; i < texture_files.size(); i++)
	{
		filestream << "(f " << texture_files[i] << " )\n";
	}
	filestream << ")\n";
	filestream << "(triangles " << faces.size() << "\n";
	for (int i = 0; i < faces.size(); i++)
	{
		filestream << "(t " << faces[i].texture_id << " " << faces[i].t1->s << " " << faces[i].t1->t << " " << faces[i].t2->s << " " << faces[i].t2->t << " " << faces[i].t3->s << " " << faces[i].t3->t << " )\n";
	}
	filestream << ")\n";
	filestream.close();

}


