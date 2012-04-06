#include "GL/glew.h"
#include "MyGLWidget.h"
//#include "GL/glext.h"




MyGLWidget::MyGLWidget(QWidget *parent)
: QGLWidget(parent)
, buttonRight(false)
, buttonLeft(false)
, obj(0)
, lvl(0)
{
	setLevel(lvl);
}

//MyGLWidget::~MyGLWidget()
//{
//	makeCurrent();
//    glDeleteLists(object, 1);
//}

//QSize MyGLWidget::minimumSizeHint() const
// {
//     return QSize(50, 50);
// }
//
// QSize MyGLWidget::sizeHint() const
// {
//     return QSize(400, 400);
// }

void MyGLWidget::initializeGL()
{
	glClearColor(0.1, 0.1, 0.1, 0.0);
	//glClearColor(0.1, 0.64, 0.54, 0.0);
    glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	setLight();
	//enableTexturing();



}

void MyGLWidget::resizeGL(int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(45.0, (GLfloat) w/(GLfloat) h, 1, 15.0);
    glMatrixMode (GL_MODELVIEW);
}

void MyGLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	glTranslatef(0.0f,0.0f,-0.1f*camera_position.y()-7.0f);
	//gluLookAt(0, 0, -7.0, 0.0, 0.0, 0.0, camera_angle.x(), camera_angle.y(), 0.0);
	glRotatef(-camera_angle.x(), 0, 1, 0);
	glRotatef(-camera_angle.y(), 1, 0, 0);
	//glTranslatef(0.0f,0.0f,-1.0f);

	if (obj)
	{
		//setLight();
		drawer.draw(lvl, actual_textures);
	}
	

}


void MyGLWidget::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		buttonLeft = true;
	}
	if (event->button() == Qt::RightButton)
	{
		buttonRight = true;
	}
	
	start.setX(event->x());
	start.setY(event->y());
	last.setX(event->x());
	last.setY(event->y());

	paintGL();
}


void MyGLWidget::mouseMoveEvent(QMouseEvent *event)
{
	QPoint dif(last.x() - event->x(), last.y() - event->y());
	last.setX(event->x());
	last.setY(event->y());

	if(buttonLeft)
		camera_angle+=dif;
	if(buttonRight)
		camera_position+=dif;
}

void MyGLWidget::mouseReleaseEvent(QMouseEvent *event)
{
 	if (event->button() == Qt::LeftButton)
		buttonLeft = false;
	if (event->button() == Qt::RightButton)
		buttonRight = false;
}


void MyGLWidget::wheelEvent(QWheelEvent *event)
 {
	
 }

void MyGLWidget::setMyObject(MyObject *object)
{
	obj = object;
	drawer.setObject(obj);
	//setLevel(lvl);
}

void MyGLWidget::setLevel(int level)
{
	lvl = level;
}

void MyGLWidget::setLight()
{
	float mat_specular[4] = {0.4, 0.4, 0.4, 1.0};
	float mat_shininess[1] = {80.0};
	float mat_ambient[4] = {0.1, 0.1, 0.1, 1.0};
	float mat_diffuse[4] = {1.0, 1.0, 1.0, 1.0};
 
	float light_position[4] = {-5, 5, 0, 0};
	float light_ambient[4] = {0.1, 0.1, 0.1, 1.0};
	float light_diffuse[4] = {1.0, 1.0, 1.0, 1.0};

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   mat_diffuse);
 
    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glLightfv(GL_LIGHT1, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position);

	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.5);

    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_CULL_FACE);
	glShadeModel(GL_SMOOTH);

	glLightModelf(GL_LIGHT_MODEL_COLOR_CONTROL,GL_SEPARATE_SPECULAR_COLOR);
}

void MyGLWidget::enableTexturing()
{
	
	//Delete Textures that have been bound before
	if (texturing)
	{
		deleteTexture();
		drawer.deleteTexture();
	}
	texturing = true;

	drawer.enableTexturing();
	std::vector<std::string> & texture_files = obj->levels_subdivision[lvl].texture_files;
	int no_textures = texture_files.size();
	emit minMaxTextures(0, no_textures-1);
	for (int i = 0; i < no_textures; i++)
	{
		actual_textures.push_back(GLuint());
		
		/*
		QImage t = QGLWidget::convertToGLFormat(QImage(texture_files[i].c_str()));
		glGenTextures( 1, &actual_textures[i] );
		glBindTexture( GL_TEXTURE_2D, actual_textures[i] );
		glTexImage2D( GL_TEXTURE_2D, 0, 3, t.width(), t.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, t.bits());
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		*/
		QImage image = QImage(texture_files[i].c_str());
		//QPixmap image = QPixmap(texture_files[i].c_str());
		if (image.isNull())
		{
			error.showMessage("Image file could not be read");
		}
		else
		{
			actual_textures[i] = bindTexture(image, GL_TEXTURE_2D);
		}
		//actual_textures[i] = bindTexture(QImage(texture_files[i].c_str()), GL_TEXTURE_2D);
	}
}

void MyGLWidget::cleanUp()
{
	obj = 0;
	if (texturing)
	{
		deleteTexture();
	}
	drawer.cleanUp();
}

void MyGLWidget::deleteTexture()
{
	texturing = false;
	emit minMaxTextures(0, 0);
	for (int i = 0; i < actual_textures.size(); i++)
	{
		glDeleteTextures(1, &(actual_textures[i]));
	}
	actual_textures.clear();
}

void MyGLWidget::setActiveTriangle(int t)
{
	drawer.setActiveTriangle(t);
}

