#pragma once
//#include <gl/glew.h>
#include <QtOpenGL\QGLWidget>
#include "../Subdivision/MyObject.h"
#include "../Subdivision/TwoManifold.h"
#include "../Subdivision/Point3d.h"
#include "../Subdivision/Texture.h"
#include <vector>
#include <QtCore/QString>
#include <QtCore/QFile>
#include <QtCore/QTextStream>



class ObjectDrawer : public QObject
{
	Q_OBJECT

public:
	ObjectDrawer();
	void setObject(MyObject * obj);
	void draw(int lvl, std::vector<GLuint> & actual_texture);
	void enableTexturing();
	void setActiveTriangle(int t);
	int getNumberFaces();
	int getCurrentLvl(){return current_lvl;};
	void cleanUp();
	void deleteTexture();


public slots:
	void changeTextureCoordinates(QPointF &t1, QPointF &t2, QPointF &t3);
	void changeTextureForActiveTriangle(int text_no);


signals:
	void newTriangleMarked(QString &file, QPointF &t1, QPointF &t2, QPointF &t3);
	void newTextureNumber(int i);
	void newTexture(QString& file);
	void setCoordinates(QPointF &t1, QPointF &t2, QPointF &t3);
	void minMaxTriangles(int min, int max);

private: 
	void createTextures();
	MyObject * object;
	std::vector<float> x_cord;
	std::vector<float> y_cord;
	std::vector<float> z_cord;
	std::vector<Point3d> normals;
	std::vector<int> texture_indices;
	std::vector<HE_Texture> texture_coords;
	int current_lvl;
	int active_triangle;
	bool texturing;
	bool facenormals;
};