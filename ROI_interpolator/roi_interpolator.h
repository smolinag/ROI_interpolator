#ifndef ROI_INTERPOLATOR_H
#define ROI_INTERPOLATOR_H

#include <QtWidgets/QMainWindow>
#include "ui_roi_interpolator.h"

class ROI_interpolator : public QMainWindow
{
	Q_OBJECT

public:
	ROI_interpolator(QWidget *parent = 0);
	~ROI_interpolator();

private:

	//Main Gui
	Ui::ROI_interpolatorClass ui;
	Ui_ROI_interpolatorClass *ROI_inter;

};

#endif // ROI_INTERPOLATOR_H
