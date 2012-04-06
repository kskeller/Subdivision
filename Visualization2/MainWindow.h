#pragma once
#include "Ui_MainWindow.h"
#include "MyGLWidget.h"
#include <QTCore/QTimer>
#include "../Subdivision/MyObject.h"
#include "TextureDisplay.h"
#include <QtGui/QDoubleValidator>
#include <QtGui/QErrorMessage>

class MainWindow : public QMainWindow, protected Ui_MainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget* parent = 0, Qt::WindowFlags flags = 0);

	virtual ~MainWindow();


protected slots:
	void OnBnClickedOpen();
	void OnBnClickedTexture();
	void OnBnClickedSaveTextureFile();
	void setSubLabel(int sub);
	void buttonClickedApply();
	void buttonClickedRotate();
	void buttonClickedFlip();
	void changeLineEdits(QString &file, QPointF &t1, QPointF &t2, QPointF &t3);
	void setSpinBoxMinMax(int min, int max);
	void setTrianglesMinMax(int min, int max);
	void activeTriangleChanged(int t);

signals:
	void emitApply(QPointF t1, QPointF t2, QPointF t3);

private:
	void setUpSlots();
	void setValidators();
	QTimer timer;
	MyObject * my_object;
	TextureDisplay my_t_d;
	QDoubleValidator m_double_Validator;
	void adjustSlider();
	QErrorMessage errorMessage;

};