#include "LoopSubdivision.h"

const float LoopSubdivision::a_e_1 = 0.375;
const float LoopSubdivision::a_e_2 = 0.125;
const float LoopSubdivision::a_n[10] = { 0, 0.765625, 0.390625, 0.4375, 0.515625, 0.579533905, 0.625, 0.656825558, 0.679457521, 0.695934838};

void LoopSubdivision::subdivide(TwoManifold & parent, TwoManifold & child)
{
	int old_no_faces = parent.faces.size();
	//check if that is correct!
	// reserve enough memory for new vertices.
	child.faces.reserve(old_no_faces*4);
	child.halfedges.reserve(parent.halfedges.size() * 4);
	child.vertices.reserve(parent.vertices.size() + parent.halfedges.size()/2 );

	//This is stupid! what is wrong with the constructor?
	child.texture_avail = false;
	if (parent.texture_avail)
	{
		child.texture_avail = true;
		child.texture.reserve(parent.texture.size() + parent.halfedges.size());
		// Copy texture_file names
		child.texture_files = parent.texture_files;
	}

	for (int i=0; i< old_no_faces; i++)
	{
		child.faces.push_back(HE_Face());
		HE_Face * f1 = &(child.faces.back());
		child.faces.push_back(HE_Face());
		HE_Face * f2 = &(child.faces.back());
		child.faces.push_back(HE_Face());
		HE_Face * f3 = &(child.faces.back());
		child.faces.push_back(HE_Face());
		HE_Face * f4 = &(child.faces.back());

		HE_Vertex * v1o = setNewVertexOnExistingVertex(parent.faces[i].he1->start, child);
		HE_Vertex * v2o = setNewVertexOnExistingVertex(parent.faces[i].he1->next->start, child);
		HE_Vertex * v3o = setNewVertexOnExistingVertex(parent.faces[i].he1->next->next->start, child);

		HE_Vertex * v1n = setNewVertexOnEdge(parent.faces[i].he1, child);
		HE_Vertex * v2n = setNewVertexOnEdge(parent.faces[i].he1->next, child);
		HE_Vertex * v3n = setNewVertexOnEdge(parent.faces[i].he1->next->next, child);	

		child.halfedges.push_back(HE_HalfEdge());
		HE_HalfEdge * he11 = &(child.halfedges.back());
		child.halfedges.push_back(HE_HalfEdge());
		HE_HalfEdge * he12 = &(child.halfedges.back());
		child.halfedges.push_back(HE_HalfEdge());
		HE_HalfEdge * he13 = &(child.halfedges.back());
		child.halfedges.push_back(HE_HalfEdge());
		HE_HalfEdge * he21 = &(child.halfedges.back());
		child.halfedges.push_back(HE_HalfEdge());
		HE_HalfEdge * he22 = &(child.halfedges.back());
		child.halfedges.push_back(HE_HalfEdge());
		HE_HalfEdge * he23 = &(child.halfedges.back());
		child.halfedges.push_back(HE_HalfEdge());
		HE_HalfEdge * he31 = &(child.halfedges.back());
		child.halfedges.push_back(HE_HalfEdge());
		HE_HalfEdge * he32 = &(child.halfedges.back());
		child.halfedges.push_back(HE_HalfEdge());
		HE_HalfEdge * he33 = &(child.halfedges.back());
		child.halfedges.push_back(HE_HalfEdge());
		HE_HalfEdge * he41 = &(child.halfedges.back());
		child.halfedges.push_back(HE_HalfEdge());
		HE_HalfEdge * he42 = &(child.halfedges.back());
		child.halfedges.push_back(HE_HalfEdge());
		HE_HalfEdge * he43 = &(child.halfedges.back());

		//Set FacePointers
		f1->he1 = he11;
		f2->he1 = he21;
		f3->he1 = he31;
		f4->he1 = he41;

		//Set Triangle Rings
		he11->setRing(he12, he13);
		he21->setRing(he22, he23);
		he31->setRing(he32, he33);
		he41->setRing(he42, he43);

		//Set starting vertices
		he11->start = v1o;
		v1o->attachHalfEdge(he11);
		he11->face = f1;
		
		he12->start = v1n;
		v1n->attachHalfEdge(he12);
		he12->face = f1;

		he13->start = v3n;
		v3n->attachHalfEdge(he13);
		he13->face = f1;

		he21->start = v2o;
		v2o->attachHalfEdge(he21);
		he21->face = f2;

		he22->start = v2n;
		v2n->attachHalfEdge(he22);
		he22->face = f2;

		he23->start = v1n;
		v1n->attachHalfEdge(he23);
		he23->face = f2;
		
		he31->start = v3o;
		v3o->attachHalfEdge(he31);
		he31->face = f3;
		
		he32->start = v3n;
		v3n->attachHalfEdge(he32);
		he32->face = f3;

		he33->start = v2n;
		v2n->attachHalfEdge(he33);
		he33->face = f3;

		he41->start = v3n;
		v3n->attachHalfEdge(he41);
		he41->face = f4;

		he42->start = v1n;
		v1n->attachHalfEdge(he42);
		he42->face = f4;

		he43->start = v2n;
		v2n->attachHalfEdge(he43);
		he43->face = f4;

		//Set Pairs -> other pairs will be set in function...
		he12->pair = he41;
		he41->pair = he12;

		he22->pair = he42;
		he42->pair = he22;

		he32->pair = he43;
		he43->pair = he32;

		//WORK NEEDED
		if (child.texture_avail)
		{
			HE_Face& parent_face = parent.faces[i];
			
			HE_Texture t1 = *(parent_face.t1);
			HE_Texture t2 = *(parent_face.t2);
			HE_Texture t3 = *(parent_face.t3);
			HE_Texture t12((t1.s + t2.s)/2.0, (t1.t + t2.t)/2.0);
			HE_Texture t23((t2.s + t3.s)/2.0, (t2.t + t3.t)/2.0);
			HE_Texture t13((t1.s + t3.s)/2.0, (t1.t + t3.t)/2.0);

			HE_Texture * p_t1 = pointerForTexture(parent_face.t1, child);
			HE_Texture * p_t2 = pointerForTexture(parent_face.t2, child);
			HE_Texture * p_t3 = pointerForTexture(parent_face.t3, child);

			child.texture.push_back(t12);
			HE_Texture * p_t12 = &(child.texture.back());
			child.texture.push_back(t23);
			HE_Texture * p_t23 = &(child.texture.back());
			child.texture.push_back(t13);
			HE_Texture * p_t13 = &(child.texture.back());

			//now set texture coordinates!
			f1->texture_id = parent_face.texture_id;
			f2->texture_id = parent_face.texture_id;
			f3->texture_id = parent_face.texture_id;
			f4->texture_id = parent_face.texture_id;

			f1->t1 = p_t1;
			f1->t2 = p_t12;
			f1->t3 = p_t13;

			f2->t1 = p_t2;
			f2->t2 = p_t23;
			f2->t3 = p_t12;

			f3->t1 = p_t3;
			f3->t2 = p_t13;
			f3->t3 = p_t23;

			f4->t1 = p_t13;
			f4->t2 = p_t12;
			f4->t3 = p_t23;
		}

	}

	for (int i=0; i<child.halfedges.size(); i++)
	{
		child.halfedges[i].findPair();
	}

	for (int i=0; i<child.faces.size(); i++)
	{
		child.faces[i].setNormal();
	}
	for (int j=0; j<child.vertices.size(); j++) 
	{
		child.vertices[j].setVertexNormal();
	}
}

HE_Vertex * LoopSubdivision::setNewVertexOnExistingVertex(HE_Vertex * old, TwoManifold & child)
{
	//does the existing Vertex already have a child vertex?
	if (old->child)	
	{
		return old->child;
	}
	else
	{	
		//make new Point
		child.vertices.push_back(HE_Vertex());
		HE_Vertex * v= &(child.vertices.back());
		old->child = v;
		
		//calculate and set coordinates of new point
		float a = a_n[old->adjacent_edges];
		Point3d q = old->averageNeighbors();
		Point3d v_star(old->x, old->y, old->z);
		Point3d v_new = v_star * a + q *(1-a);
		v->x = v_new.x;
		v->y = v_new.y;
		v->z = v_new.z;

		v->adjacent_edges = old->adjacent_edges;
		//how about id?
		v->id = child.vertices.size() - 1;

		return v;
	}
}


HE_Vertex * LoopSubdivision::setNewVertexOnEdge(HE_HalfEdge * he, TwoManifold & child)
{
	//does the existing Vertex already have a child vertex?
	if (he->child)	
	{
		return he->child;
	}
	else
	{	
		//make new Point
		child.vertices.push_back(HE_Vertex());
		HE_Vertex * v= &(child.vertices.back());
		he->child = v;
		he->pair->child = v;
		
		//calculate and set coordinates of new point
		Point3d v1(he->start->x, he->start->y, he->start->z);
		Point3d v2(he->pair->start->x, he->pair->start->y, he->pair->start->z);
		Point3d v3(he->next->next->start->x, he->next->next->start->y, he->next->next->start->z);
		Point3d v4(he->pair->next->next->start->x, he->pair->next->next->start->y, he->pair->next->next->start->z);
		
		Point3d v_new = v1 * a_e_1 + v2 * a_e_1 + v3 * a_e_2 + v4 * a_e_2;
		v->x = v_new.x;
		v->y = v_new.y;
		v->z = v_new.z;

		v->adjacent_edges = 6;
		//how about id?
		v->id = child.vertices.size() -1;

		return v;
	}

}

HE_Texture * LoopSubdivision::pointerForTexture(HE_Texture * t, TwoManifold & child)
{
	HE_Texture * p_t1;
	if (t->child == 0)
	{
		child.texture.push_back(*t);
		p_t1 = &(child.texture.back());
		t->child = p_t1;
	}
	else
	{
		p_t1 = t->child;
	}
	return p_t1;
}