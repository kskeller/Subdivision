#include "HalfEdge.h"
//#include "Defines.h"
#include <iostream>

HE_HalfEdge::HE_HalfEdge()
: start(0)
, pair(0) 
, next(0)
, same_start(0)
, face(0)
, child(0)
{
}

void HE_HalfEdge::findPair()
{
	if (pair == 0)
	{
		HE_HalfEdge * candidate = next->start->he;
		while (candidate->next->start != start)
		{
			if (candidate == 0)
			{
				std::cout << "Couldnt match HalfEdge\n";
				return;
			}
			candidate = candidate->same_start;
		}

		candidate->pair = this;
		pair = candidate;
	}
}

void HE_HalfEdge::setRing(HE_HalfEdge * he2, HE_HalfEdge * he3)
{
	next = he2;
	he2->next = he3;
	he3->next = this;
}