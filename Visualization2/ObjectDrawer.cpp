#include "ObjectDrawer.h"

//#include <gl/glu.h>
#include <QtOpenGL\QGLWidget>
#include <QtGui/QImage>


ObjectDrawer::ObjectDrawer()
:current_lvl(-1)
, active_triangle(-1)
, texturing(false)
, facenormals(false)
{}

void ObjectDrawer::setObject(MyObject * obj)
{
	object = obj;
}

void ObjectDrawer::draw(int lvl, std::vector<GLuint> & actual_texture)
{
	if (object)
	{
		if (lvl != current_lvl)
		{
			object->makeVertexList(lvl, x_cord, y_cord, z_cord, normals, facenormals);
			current_lvl = lvl;
			if (texturing)
			{
				object->makeTextureList(current_lvl, texture_indices, texture_coords);
			}
			emit minMaxTriangles(-1, x_cord.size()/3 - 1);
		}

		//TwoManifold *tm = object->getSubdivision(lvl); 
	
		if (texturing)
		{
			for (int i=0; i<(x_cord.size()/3); i++) 
			{
				if (i == active_triangle)
				{
					glColor3f(1.0, 0, 0);
				}
				else 
				{
					glColor3f(1.0, 1.0, 1.0);
				}

				glBindTexture(GL_TEXTURE_2D, actual_texture[texture_indices[i]]);
				glBegin(GL_TRIANGLES);
					if (facenormals)
					{
						glNormal3f(normals[i].x, normals[i].y, normals[i].z);
					}
					else
					{
						glNormal3f(normals[3*i].x, normals[3*i].y, normals[3*i].z);
					}
					glTexCoord2f(texture_coords[3*i].s, texture_coords[3*i].t);
					glVertex3f(x_cord[3*i], y_cord[3*i], z_cord[3*i]);
					if (!facenormals)
					{
						glNormal3f(normals[3*i+1].x, normals[3*i+1].y, normals[3*i+1].z);
					}
					glTexCoord2f(texture_coords[3*i+1].s, texture_coords[3*i+1].t);
					glVertex3f(x_cord[3*i+1], y_cord[3*i+1], z_cord[3*i+1]);
					if (!facenormals)
					{
						glNormal3f(normals[3*i+2].x, normals[3*i+2].y, normals[3*i+2].z);
					}
					glTexCoord2f(texture_coords[3*i+2].s, texture_coords[3*i+2].t);
					glVertex3f(x_cord[3*i+2], y_cord[3*i+2], z_cord[3*i+2]);
				glEnd();
			}
		}
		else
		{
			glBegin(GL_TRIANGLES);
			glColor3f(0.15, 0.7, 0.8);
			for (int i=0; i<(x_cord.size()/3); i++) 
			{
				if (facenormals)
				{
					glNormal3f(normals[i].x, normals[i].y, normals[i].z);
				}
				else
				{
					glNormal3f(normals[3*i].x, normals[3*i].y, normals[3*i].z);
				}
				glVertex3f(x_cord[3*i], y_cord[3*i], z_cord[3*i]);
				if (!facenormals)
				{
					glNormal3f(normals[3*i+1].x, normals[3*i+1].y, normals[3*i+1].z);
				}
				glVertex3f(x_cord[3*i+1], y_cord[3*i+1], z_cord[3*i+1]);
				if (!facenormals)
				{
					glNormal3f(normals[3*i+2].x, normals[3*i+2].y, normals[3*i+2].z);
				}
				glVertex3f(x_cord[3*i+2], y_cord[3*i+2], z_cord[3*i+2]);

			}
			glEnd();
		}
		
	}
}

void ObjectDrawer::enableTexturing()
{
	texturing = true;
	glClear(GL_COLOR_BUFFER_BIT);
	if (object)
	{
		object->makeTextureList(current_lvl, texture_indices, texture_coords);

	}
}
	
void ObjectDrawer::setActiveTriangle(int t)
{
	active_triangle = t;
	if (object && texturing && t >= 0 && t < x_cord.size()/3)
	{
		QString file((object->getTextureName(current_lvl, t)).c_str());
		QPointF t1(texture_coords[3*t].s, texture_coords[3*t].t);
		QPointF t2(texture_coords[3*t + 1].s, texture_coords[3*t + 1].t);
		QPointF t3(texture_coords[3*t + 2].s, texture_coords[3*t + 2].t);
		emit newTriangleMarked(file, t1, t2, t3);
		emit newTextureNumber(texture_indices[t]);
	}
	
}

void ObjectDrawer::changeTextureCoordinates(QPointF &t1, QPointF &t2, QPointF &t3)
{
	if (object && texturing && active_triangle >= 0 && active_triangle < x_cord.size()/3)
	{
		texture_coords[3*active_triangle].s = t1.x();
		texture_coords[3*active_triangle].t = t1.y();
		texture_coords[3*active_triangle + 1].s = t2.x();
		texture_coords[3*active_triangle + 1].t = t2.y();
		texture_coords[3*active_triangle + 2].s = t3.x();
		texture_coords[3*active_triangle + 2].t = t3.y();

		object->changeTextureCoordinates(current_lvl, active_triangle, t1.x(), t1.y(), t2.x(), t2.y(), t3.x(), t3.y());
		emit setCoordinates(t1, t2, t3);
	}
}


int ObjectDrawer::getNumberFaces()
{
	if (object)
		return x_cord.size()/3;
	else
		return 0;
}

void ObjectDrawer::changeTextureForActiveTriangle(int text_no)
{
	if (object && active_triangle < x_cord.size()/3 && active_triangle >= 0)
	{
		texture_indices[active_triangle] = text_no;
		object->changeTextureIndices(current_lvl, active_triangle, text_no);
		
		QString file((object->getTextureName(current_lvl, active_triangle)).c_str());
		emit newTexture(file);
	}
}

void ObjectDrawer::cleanUp()
{
	object = 0;
	x_cord.clear();
	y_cord.clear();
	z_cord.clear();
	normals.clear();
	deleteTexture();
	current_lvl = -1;
}

void ObjectDrawer::deleteTexture()
{
	texturing = false;
	texture_indices.clear();
	texture_coords.clear();
}