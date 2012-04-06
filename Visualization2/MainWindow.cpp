#include "MainWindow.h"
#include <QtGui/QHBoxLayout>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include "Qt/qfiledialog.h"
#include <QtCore/QString>
#include <QtCore/QFile>
#include <string>


MainWindow::MainWindow(QWidget *parent /*= 0*/, Qt::WindowFlags flags /*= 0*/)  
: QMainWindow(parent, flags)
, timer(this)
, my_object(0)
, my_t_d(0, 0, 1.0, 1.0)
, m_double_Validator(0.0, 1.0, 3, this)
, errorMessage(this)
{
	//create gui elements defined in the Ui_MainWidow class
	setupUi(this);
	
    
	setUpSlots();
	setValidators();
	m_w_glWidget->setMyObject(my_object);
	m_gV_Texture->setScene(&my_t_d);
	m_sB_Texture->setWrapping(true);
	m_sB_Triangle->setWrapping(true);
	m_hSl_Triangles->setValue(-1);
	timer.start(40);
}

MainWindow::~MainWindow()
{
	// no need to delete child widgets, QT does it all for us
}


void MainWindow::OnBnClickedOpen()
{
	QString filenameOpen = QFileDialog::getOpenFileName(this, tr("Load Object"), "../Objects", 
		tr("TXT File (*.txt)"));
	if (filenameOpen == "")
		return;
	if (my_object != 0)
	{
		delete my_object;
		m_hSl_Subdivisions->setValue(0);
		m_hSl_Triangles->setValue(-1);
		m_w_glWidget->cleanUp();
	}
	try 
	{
		my_object = new MyObject(filenameOpen.toStdString());
		m_w_glWidget->setMyObject(my_object);
	}
	catch(...)
	{
		errorMessage.showMessage(QString("The specified file could not be loaded. Please specify another file"));
	}
}

void MainWindow::OnBnClickedTexture()
{
	QString filenameOpen = QFileDialog::getOpenFileName(this, tr("Load Texture"), "../TextureFiles", 
		tr("TXT File (*.txt)"));
	if (filenameOpen == "")
		return;
	if (my_object != 0)
	{
		try 
		{
			my_object->assignTexture(filenameOpen.toStdString());
			m_w_glWidget->enableTexturing();
			adjustSlider();
		}
		catch(...)
		{
			errorMessage.showMessage(QString("The specified file could not be loaded. Please reload the object and specify another specify another texture file"));
			delete my_object;
			my_object = 0;
			m_hSl_Subdivisions->setValue(0);
			m_hSl_Triangles->setValue(-1);
			m_w_glWidget->cleanUp();
		}
	}
}

void MainWindow::OnBnClickedSaveTextureFile()
{ 
	QString filenameSave = QFileDialog::getSaveFileName(this, tr("Save Texture"), "../TextureFiles", 
		tr("TXT File (*.txt)"));
	if (filenameSave == "")
		return;
	if (my_object)
	{
		my_object->writeToFile(m_w_glWidget->drawer.getCurrentLvl(), filenameSave.toStdString());
	}
}



void MainWindow::setUpSlots()
{	
	connect(action_Open, SIGNAL(activated()), this, SLOT(OnBnClickedOpen()));
	connect(action_Add_Texture, SIGNAL(activated()), this, SLOT(OnBnClickedTexture()));
	connect(actionSave_Current_Texture, SIGNAL(activated()), this, SLOT(OnBnClickedSaveTextureFile()));

	connect(&timer, SIGNAL(timeout()), m_w_glWidget, SLOT(updateGL()));
	connect(m_hSl_Subdivisions, SIGNAL(valueChanged ( int ) ), m_w_glWidget, SLOT(setLevel(int)));
	connect(m_hSl_Subdivisions, SIGNAL(valueChanged ( int ) ), this, SLOT(setSubLabel(int)));

	connect(m_hSl_Triangles, SIGNAL(valueChanged ( int ) ),  this, SLOT(activeTriangleChanged(int)));
	connect(m_sB_Triangle, SIGNAL(valueChanged ( int ) ),  this, SLOT(activeTriangleChanged(int)));

	connect(&(m_w_glWidget->drawer), SIGNAL(newTriangleMarked(QString &, QPointF &, QPointF &, QPointF &)), &my_t_d, SLOT(setTexture(QString &, QPointF &, QPointF &, QPointF &)));
	connect(&(m_w_glWidget->drawer), SIGNAL(newTextureNumber(int)), m_sB_Texture, SLOT(setValue(int)));
	connect(&my_t_d, SIGNAL(newTextures(QPointF &, QPointF &, QPointF &)), &(m_w_glWidget->drawer), SLOT(changeTextureCoordinates(QPointF &, QPointF &, QPointF &)));
	connect(m_w_glWidget, SIGNAL(minMaxTextures(int, int)), this, SLOT(setSpinBoxMinMax(int, int)));
	connect(&(m_w_glWidget->drawer), SIGNAL(minMaxTriangles(int, int)), this, SLOT(setTrianglesMinMax(int, int)));

	connect(m_pB_Apply, SIGNAL(pressed()), this, SLOT(buttonClickedApply()));
	connect(m_pB_Rotate, SIGNAL(pressed()), this, SLOT(buttonClickedRotate()));
	connect(m_pB_Flip, SIGNAL(pressed()), this, SLOT(buttonClickedFlip()));
	connect(&(m_w_glWidget->drawer), SIGNAL(newTriangleMarked(QString &, QPointF &, QPointF &, QPointF &)), this, SLOT(changeLineEdits(QString &, QPointF &, QPointF &, QPointF &)));

	connect(&(m_w_glWidget->drawer), SIGNAL(newTexture(QString&)), &my_t_d, SLOT(newTexture(QString&)));
	connect(&(m_w_glWidget->drawer), SIGNAL(setCoordinates(QPointF&, QPointF&, QPointF&)), &my_t_d, SLOT(setCoordinates(QPointF&, QPointF&, QPointF&)));
}

void MainWindow::setValidators()
{
	m_lE_pos_p1_x->setValidator(&m_double_Validator);
	m_lE_pos_p1_y->setValidator(&m_double_Validator);
	m_lE_pos_p2_x->setValidator(&m_double_Validator);
	m_lE_pos_p2_y->setValidator(&m_double_Validator);
	m_lE_pos_p3_x->setValidator(&m_double_Validator);
	m_lE_pos_p3_y->setValidator(&m_double_Validator);
}

void MainWindow::setSubLabel(int sub)
{
	QString str;
	str.setNum(sub);
	m_l_sub->setText(str);
}

void MainWindow::buttonClickedApply()
{
	//emit emitApply(QPointF(m_lE_pos_p1_x->text().toDouble(), m_lE_pos_p1_y->text().toDouble()), QPointF(m_lE_pos_p2_x->text().toDouble(), m_lE_pos_p2_y->text().toDouble()), QPointF(m_lE_pos_p3_x->text().toDouble(), m_lE_pos_p3_y->text().toDouble()));
	m_w_glWidget->drawer.changeTextureCoordinates(QPointF(m_lE_pos_p1_x->text().toDouble(), m_lE_pos_p1_y->text().toDouble()), QPointF(m_lE_pos_p2_x->text().toDouble(), m_lE_pos_p2_y->text().toDouble()), QPointF(m_lE_pos_p3_x->text().toDouble(), m_lE_pos_p3_y->text().toDouble()));
	m_w_glWidget->drawer.changeTextureForActiveTriangle(m_sB_Texture->value());
}


void MainWindow::buttonClickedRotate()
{
	QString sX, sY;

	sX = m_lE_pos_p1_x->text();
	m_lE_pos_p1_x->setText(m_lE_pos_p2_x->text());
	m_lE_pos_p2_x->setText(m_lE_pos_p3_x->text());
	m_lE_pos_p3_x->setText(sX);

	sY = m_lE_pos_p1_y->text();
	m_lE_pos_p1_y->setText(m_lE_pos_p2_y->text());
	m_lE_pos_p2_y->setText(m_lE_pos_p3_y->text());
	m_lE_pos_p3_y->setText(sY);

	buttonClickedApply();
}

void MainWindow::buttonClickedFlip()
{
	QString sX, sY;

	sX = m_lE_pos_p1_x->text();
	m_lE_pos_p1_x->setText(m_lE_pos_p2_x->text());
	m_lE_pos_p2_x->setText(sX);
	
	sY = m_lE_pos_p1_y->text();
	m_lE_pos_p1_y->setText(m_lE_pos_p2_y->text());
	m_lE_pos_p2_y->setText(sY);
	
	buttonClickedApply();
}

void MainWindow::changeLineEdits(QString &file, QPointF &t1, QPointF &t2, QPointF &t3)
{
	QString number;

	number.setNum(t1.x());
	m_lE_pos_p1_x->setText(number);
	number.setNum(t1.y());
	m_lE_pos_p1_y->setText(number);
	
	number.setNum(t2.x());
	m_lE_pos_p2_x->setText(number);
	number.setNum(t2.y());
	m_lE_pos_p2_y->setText(number);
	
	number.setNum(t3.x());
	m_lE_pos_p3_x->setText(number);
	number.setNum(t3.y());
	m_lE_pos_p3_y->setText(number);
}

void MainWindow::adjustSlider()
{
	m_hSl_Triangles->setRange(-1, m_w_glWidget->drawer.getNumberFaces());
}

void MainWindow::setSpinBoxMinMax(int min, int max)
{
	m_sB_Texture->setRange(min, max);
}

void MainWindow::setTrianglesMinMax(int min, int max)
{
	m_sB_Triangle->setRange(min, max);
	m_hSl_Triangles->setRange(min, max);
}

void MainWindow::activeTriangleChanged(int t)
{
	m_sB_Triangle->setValue(t);
	m_hSl_Triangles->setValue(t);
	m_w_glWidget->setActiveTriangle(t);
}

