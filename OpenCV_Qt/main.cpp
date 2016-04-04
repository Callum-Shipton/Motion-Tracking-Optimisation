#include "opencv_qt.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	OpenCV_Qt w;
	w.setAttribute(Qt::WA_DeleteOnClose, true);
	w.show();
	return a.exec();
}
