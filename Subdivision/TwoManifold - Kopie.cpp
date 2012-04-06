#include "TwoManifold.h"
#include <fstream>
//#include <GL/glut.h>

TwoManifold::TwoManifold(std::string filename)
{
	constructFromFile(filename);
}

TwoManifold::~TwoManifold()
{
	for (int i=0; i<vertices.size(); i++) 
	{
		delete vertices[i];
	}
	for (int i=0; i<faces.size(); i++) 
	{
		delete faces[i];
	}
	for (int i=0; i<halfedges.size(); i++) 
	{
		delete halfedges[i];
	}
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
		HE_Vertex * myvertex = new HE_Vertex;
		myvertex->id = i;
		myvertex->x = x;
		myvertex->y = y;
		myvertex->z = z;
		myvertex->he = NULL;
		vertices.push_back(myvertex);
		
		filestream.ignore(10, ')');
		filestream >> temp;

		i++;
	}

	std::string triangles;
	int no_faces;
	filestream >> vert >> no_faces;
	faces.reserve(no_faces);
	
	temp2 = "(t";
	int v1, v2, v3;
	filestream >> temp;
	while (temp == temp2)
	{
		filestream >> v1 >> v2 >> v3;
		HE_Face *myface = new HE_Face();
		HE_HalfEdge *he1 = new HE_HalfEdge();
		HE_HalfEdge *he2 = new HE_HalfEdge();
		HE_HalfEdge *he3 = new HE_HalfEdge();
		
		myface->he1 = he1;

		he1->face = myface;
		he1->next = he2;
		he1->start = vertices[v1];

		vertices[v1]->attachHalfEdge(he1);
		
		he2->face = myface;
		he2->next = he3;
		he2->start = vertices[v2];
		vertices[v2]->attachHalfEdge(he2);

		he3->face = myface;
		he3->next = he1;
		he3->start = vertices[v3];
		vertices[v3]->attachHalfEdge(he3);

		faces.push_back(myface);
		halfedges.push_back(he1);
		halfedges.push_back(he2);
		halfedges.push_back(he3);
		
		filestream.ignore(10, ')');
		filestream >> temp;
	}
	filestream.close();

	for (int j=0; j<vertices.size(); j++) 
	{
		vertices[j]->countAdjacentEdges();
	}

	for (int j=0; j<halfedges.size(); j++) 
	{
		halfedges[i]->findPair();
	}
	
}

void TwoManifold::paintObject()
{
	for (int i=0; i<faces.size(); i++) 
	{
		/*glBegin(GL_TRIANGLES);
			glVertex3f(faces[i]->he->start->x,faces[i]->he->start->y, faces[i]->he->start->z);  
			glVertex3f(faces[i]->he->next->start->x,faces[i]->he->next->start->y, faces[i]->he->next->start->z);
			glVertex3f(faces[i]->he->next->next->start->x,faces[i]->he->next->next->start->y, faces[i]->he->next->next->start->z);
		glEnd;*/
	}
}