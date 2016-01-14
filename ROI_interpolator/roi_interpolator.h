#ifndef ROI_INTERPOLATOR_H
#define ROI_INTERPOLATOR_H

#include <QtWidgets/QMainWindow>
#include "ui_roi_interpolator.h"
#include "ui_delete_roi.h"
#include <qmessagebox.h>
#include <tuple>
#include <iostream>

//Keypoint ROI tuple
typedef std::tuple<int, QVector<int>> KeyROI;

class ROI_interpolator : public QMainWindow
{
	Q_OBJECT

public:
	ROI_interpolator(QWidget *parent = 0);
	~ROI_interpolator();

	QVector<std::tuple<int, int, QVector<KeyROI>>> AllROIs;	//All ROIs global history
	QVector<std::tuple<int, int, QVector<KeyROI>>> KeyROIs;	//KeyROIs global history

private:

	//Main Gui
	Ui::ROI_interpolatorClass ui;
	Ui_ROI_interpolatorClass *ROI_inter;

	//Delete ROI Gui
	QDialog *deleteROI_dialog;
	Ui_deleteROI_dialog *delete_ROI;

	int vid_length;
	int NROI;

	//ROI parameters
	int ID;
	int label;
	int frame;
	int x_coord;
	int y_coord;
	int width;
	int height;
	QVector<int> states;

	//Delete ROI parameters
	int delID;
	int delFrame;

	KeyROI newKROI;

	//Functions
	bool validateNumber(const QString &Input);

	void makeKeyROI();	

	void interpolateROI();

	void interpolation(KeyROI prev, KeyROI curr, KeyROI next, int fID);

	void initializeTable();

	void updateTable();

	public slots:

	void addNewROI();

	void deleteROI_execDialog();

	void accept_deleteROI();

	void cancel_deleteROI();
};

#endif // ROI_INTERPOLATOR_H
