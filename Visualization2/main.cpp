#include <Qt/qapplication.h>
// Header file for MainWindow cass
#include "MainWindow.h"

int main(int argc, char* argv[])
{
	
	QApplication app(argc, argv);
	MainWindow myWindow(0, Qt::Window);
	myWindow.show();

	return app.exec();
}