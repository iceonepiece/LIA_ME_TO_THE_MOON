#include <QtWidgets/QApplication>
#include "MainWindow.h"
#include <vld.h> 


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	/*QWidget w;

	QSlider slider(Qt::Horizontal, &w);
	slider.setGeometry(0, 0, 100, 20);

	QLineEdit edit(&w);
	edit.setValidator(new QIntValidator(0, 5000, &w));
	edit.setGeometry(0, 30, 60, 20);
	
	QObject::connect(&edit, SIGNAL(editingFinished()), &slider, SLOT(close()));


	w.show();*/


	MainWindow window;
	window.show();

	return a.exec();
}
