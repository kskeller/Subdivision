#pragma once

struct HE_face;
struct HE_half_edge;


struct HE_texture
{
	float s;
	float t;
};

struct HE_vertex
{
	int id;

	float x;
	float y;
	float z;

	HE_half_edge * he;
};

struct HE_half_edge
{
	HE_vertex * start;
	HE_half_edge * pair;
	HE_half_edge * next;
	HE_half_edge * sameStartingPoint;
	HE_face * face;
};

struct HE_face
{
	HE_half_edge * he1;
	HE_half_edge * he2;
	HE_half_edge * he3;

	HE_vertex *v1;
	HE_vertex *v2;
	HE_vertex *v3;

	HE_texture *t1;
	HE_texture *t2;
	HE_texture *t3;


};