#include "roi_interpolator.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ROI_interpolator w;
	w.show();
	return a.exec();
}
