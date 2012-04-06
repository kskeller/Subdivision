#pragma once
//#include "gl/glu.h"
#include <QtOpenGL\QGLWidget>
#include <QtGui/QWidget>
#include <QtGui/QImage>
#include <QtGui/QPixmap>
#include "Qt/QPoint.h"
#include <QtGui/QMouseEvent>
#include <QtGui/QWheelEvent>
#include "../Subdivision/MyObject.h"
#include "ObjectDrawer.h"
#include <vector>
#include <string>
#include <QtGui/QErrorMessage>

class MyGLWidget : public QGLWidget
    {
         Q_OBJECT        // must include this if you use Qt signals/slots
	
	public:
        MyGLWidget(QWidget *parent);
		void setMyObject(MyObject * object);

		ObjectDrawer drawer;

		void cleanUp();
	 
	protected:

        void initializeGL();
        void resizeGL(int w, int h);
        void paintGL();

		virtual void mousePressEvent(QMouseEvent *event);
		virtual void mouseMoveEvent(QMouseEvent *event);
		virtual void mouseReleaseEvent(QMouseEvent *event);
		virtual void wheelEvent(QWheelEvent *event);


	public slots:
		void setLevel(int level);
		void enableTexturing();
		void setActiveTriangle(int t);

	signals:
		void minMaxTextures(int min, int max);

	private:
		void setLight();
		bool buttonLeft;
		bool buttonRight;
		void deleteTexture();
		QPoint camera_angle, camera_position;
		QPoint start, last;
		MyObject * obj;
		int lvl;
		bool texturing;
		std::vector<GLuint> actual_textures;

		QErrorMessage error;

};