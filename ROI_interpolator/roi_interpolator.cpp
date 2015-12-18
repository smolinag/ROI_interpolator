#include "roi_interpolator.h"

ROI_interpolator::ROI_interpolator(QWidget *parent)
	: QMainWindow(parent)
{
	//Create Gui variable
	ROI_inter = new Ui_ROI_interpolatorClass();
	ROI_inter->setupUi(this);
}

ROI_interpolator::~ROI_interpolator()
{

}

void ROI_interpolator::addNewROI()
{
	int ID = ROI_inter->ID_edit->text().toInt();

	int Frame = ROI_inter->ID_edit->text().toInt();
}
