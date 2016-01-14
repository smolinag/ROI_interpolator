#include "roi_interpolator.h"


ROI_interpolator::ROI_interpolator(QWidget *parent)
	: QMainWindow(parent)
{
	//Create Gui variable
	ROI_inter = new Ui_ROI_interpolatorClass();
	ROI_inter->setupUi(this);

	vid_length = 15;
	NROI = 0;

	initializeTable();

	connect(ROI_inter->addROI_button, SIGNAL(clicked()), this, SLOT(addNewROI()));

	//Create delete ROI Dialog
	deleteROI_dialog = new QDialog(this);
	delete_ROI = new Ui_deleteROI_dialog();
	delete_ROI->setupUi(deleteROI_dialog);

	connect(ROI_inter->deleteROI_button, SIGNAL(clicked()), this, SLOT(deleteROI_execDialog()));

	connect(delete_ROI->accept_button, SIGNAL(clicked()), this, SLOT(accept_deleteROI()));
	connect(delete_ROI->cancel_button, SIGNAL(clicked()), this, SLOT(cancel_deleteROI()));
}

ROI_interpolator::~ROI_interpolator()
{

}

void ROI_interpolator::addNewROI()
{
	QString input;  
	bool valid_num;

	//Set error message 
	QMessageBox errorBox;
	errorBox.setWindowTitle("Error");
	errorBox.setIcon(QMessageBox::Icon::Critical);
	errorBox.setDefaultButton(QMessageBox::Ok);

	//Get ROI ID
	input = ROI_inter->ID_edit->text();
	valid_num = validateNumber(input);
	if (valid_num)
		ID = input.toInt();
	else
	{
		errorBox.setText("Set a valid ROI ID");
		errorBox.exec();
	}

	//Get ROI frame
	input = ROI_inter->frame_edit->text();
	valid_num = validateNumber(input);
	if (valid_num)
		frame = input.toInt();
	else
	{
		errorBox.setText("Set a valid ROI frame");
		errorBox.exec();
	}

	//Get ROI x coordinate
	input = ROI_inter->x_edit->text();
	valid_num = validateNumber(input);
	if (valid_num)
		x_coord = input.toInt();
	else
	{
		errorBox.setText("Set a valid ROI x coordinate");
		errorBox.exec();
	}
	
	//Get ROI y coordinate
	input = ROI_inter->y_edit->text();
	valid_num = validateNumber(input);
	if (valid_num)
		y_coord = input.toInt();
	else
	{
		errorBox.setText("Set a valid ROI y coordinate");
		errorBox.exec();
	}

	//Get ROI width
	input = ROI_inter->w_edit->text();
	valid_num = validateNumber(input);
	if (valid_num)
		width = input.toInt();
	else
	{
		errorBox.setText("Set a valid ROI width");
		errorBox.exec();
	}

	//Get ROI height
	input = ROI_inter->h_edit->text();
	valid_num = validateNumber(input);
	if (valid_num)
		height = input.toInt();
	else
	{
		errorBox.setText("Set a valid ROI height");
		errorBox.exec();
	}

	//Create new KeyROI with user input information
	makeKeyROI();

	//ROI interpolation
	interpolateROI();
}

void ROI_interpolator::makeKeyROI()
{
	states.clear();
	states.append(x_coord);
	states.append(y_coord);
	states.append(width);
	states.append(height);

	newKROI = std::make_tuple(frame, states);
}

void ROI_interpolator::interpolateROI()
{
	bool ID_found = false;
	int fID = -1;

	//Search newKROI ID in KeyROIs history
	for (int i = 0; i < KeyROIs.size(); i++)
	{
		if (ID == std::get<0>(KeyROIs[i]))
		{
			fID = i;
			ID_found = true;
			break;
		}
	}

	//Create new Key ROI history
	if (!ID_found)
	{
		QVector<KeyROI> KROI_hist;
		KROI_hist.append(newKROI);
		KeyROIs.append(std::make_tuple(ID, label, KROI_hist));
		fID = KeyROIs.size() - 1;
		NROI++;
	}

	KeyROI KROI_prev, KROI_next;
	int mindif = 100000;
	int mindif_idx;

	//If input ROI ID found
	if (ID_found)
	{
		//Search frames to select interpolation
		for (int i = 0; i < std::get<2>(KeyROIs[fID]).size(); i++)
		{
			//Get frame of analysis
			int currFr = std::get<0>(std::get<2>(KeyROIs[fID])[i]);

			int dif = frame - currFr;

			if (abs(dif) < abs(mindif))
			{
				mindif = dif;
				mindif_idx = i;
			}
		}

		//Find values for interpolation (KROI_prev, KROI_next)

		//Current indexed ROI's frame is greater than a previous one
		if (mindif > 0)
		{
			KROI_prev = std::get<2>(KeyROIs[fID])[mindif_idx];

			if (mindif_idx + 1 < std::get<2>(KeyROIs[fID]).size())
			{
				KROI_next = std::get<2>(KeyROIs[fID])[mindif_idx + 1];
			}

			//Insert new KROI
			std::get<2>(KeyROIs[fID]).insert(mindif_idx + 1, newKROI);
		}

		//Current indexed ROI's frame is less than a previous one
		if (mindif < 0)
		{
			KROI_next = std::get<2>(KeyROIs[fID])[mindif_idx];

			if (mindif_idx - 1 >= 0)
			{
				KROI_prev = std::get<2>(KeyROIs[fID])[mindif_idx - 1];
			}

			//Insert new KROI
			std::get<2>(KeyROIs[fID]).insert(mindif_idx, newKROI);
		}

		//Current indexed ROI's frame is equal to a previous one
		if (mindif == 0)
		{
			if (mindif_idx - 1 >= 0)
			{
				KROI_prev = std::get<2>(KeyROIs[fID])[mindif_idx - 1];
			}

			if (mindif_idx + 1 < std::get<2>(KeyROIs[fID]).size())
			{
				KROI_next = std::get<2>(KeyROIs[fID])[mindif_idx + 1];
			}

			//Replace KROI
			std::get<2>(KeyROIs[fID])[mindif_idx] = newKROI;
		}
	}

	interpolation(KROI_prev, newKROI, KROI_next, fID);

	updateTable();
}

void ROI_interpolator::interpolation(KeyROI prev, KeyROI curr, KeyROI next, int fID)
{
	//Test
	std::cout << std::endl << "New interpolation:" << std::endl;
	if (std::get<1>(prev).size() != 0)
		std::cout << "Prev=" << " f:" << std::get<0>(prev) << " x:" << std::get<1>(prev)[0] << " y:" << std::get<1>(prev)[1] << " w:" << std::get<1>(prev)[2] << " h:" << std::get<1>(prev)[3] << std::endl;
	std::cout << "Curr=" << " f:" << std::get<0>(curr) << " x:" << std::get<1>(curr)[0] << " y:" << std::get<1>(curr)[1] << " w:" << std::get<1>(curr)[2] << " h:" << std::get<1>(curr)[3] << std::endl;
	if (std::get<1>(next).size() != 0)
		std::cout << "Next=" << " f:" << std::get<0>(next) << " x:" << std::get<1>(next)[0] << " y:" << std::get<1>(next)[1] << " w:" << std::get<1>(next)[2] << " h:" << std::get<1>(next)[3] << std::endl;
	//-----

	QVector<KeyROI> interpROI_states;
	int xc_int, yc_int, w_int, h_int;
	int x0, y0, x1, y1;
	double slope_x, slope_y, slope_w, slope_h;
	
	//Replicate input states until last
	if (std::get<1>(prev).size() == 0 && std::get<1>(next).size() == 0)
	{
		for (int i = 0; i < vid_length; i++)
		{
			if (i < frame)
			{
				QVector<int> st(4, 0);
				interpROI_states.append(std::make_tuple(i,st));
			}
			else
			{
				interpROI_states.append(std::make_tuple(i, states));
			}
		}
		AllROIs.append(std::make_tuple(ID, label, interpROI_states));
	}

	//Linear interpolation until next or last
	if (std::get<1>(prev).size() != 0)
	{
		//slope for x coordinate
		y0 = std::get<1>(prev)[0];
		y1 = std::get<1>(curr)[0];
		x0 = std::get<0>(prev);
		x1 = std::get<0>(curr);
		slope_x = double(y1 - y0) / double(x1 - x0);

		//slope for y coordinate
		y0 = std::get<1>(prev)[1];
		y1 = std::get<1>(curr)[1];
		x0 = std::get<0>(prev);
		x1 = std::get<0>(curr);
		slope_y = double(y1 - y0) / double(x1 - x0);

		//slope for width
		y0 = std::get<1>(prev)[2];
		y1 = std::get<1>(curr)[2];
		x0 = std::get<0>(prev);
		x1 = std::get<0>(curr);
		slope_w = double(y1 - y0) / double(x1 - x0);

		//slope for height
		y0 = std::get<1>(prev)[3];
		y1 = std::get<1>(curr)[3];
		x0 = std::get<0>(prev);
		x1 = std::get<0>(curr);
		slope_h = double(y1 - y0) / double(x1 - x0);

		//Get superior limit to replicate linear interpolation values
		int lim_sup;
		if (std::get<1>(next).size() == 0)
			lim_sup = std::get<0>(curr);
		else
			lim_sup = std::get<0>(next);

		for (int i = 0; i < vid_length; i++)
		{
			if (i > std::get<0>(prev) && i < lim_sup)
			{
				//Interpolate x coordinate
				y0 = std::get<1>(prev)[0];
				xc_int = y0 + int(std::floor(double(i - x0)*slope_x));

				//Interpolate y coordinate
				y0 = std::get<1>(prev)[1];
				yc_int = y0 + int(std::floor(double(i - x0)*slope_y));

				//Interpolate width
				y0 = std::get<1>(prev)[2];
				w_int = y0 + int(std::floor(double(i - x0)*slope_w));

				//Interpolate height
				y0 = std::get<1>(prev)[3];
				h_int = y0 + int(std::floor(double(i - x0)*slope_h));

				QVector<int> st;
				st.append(xc_int);
				st.append(yc_int);
				st.append(w_int);
				st.append(h_int);

				//Store new states according interpolation
				std::get<2>(AllROIs[fID])[i] = std::make_tuple(i, st);
			}

			//Keep
			if (i >= lim_sup && (std::get<1>(next).size() == 0))
			{
				//Store new states according interpolation
				std::get<2>(AllROIs[fID])[i] = std::make_tuple(i, std::get<1>(curr));
			}
		}
	}

	//Linear interpolation from current to next
	if (std::get<1>(next).size() != 0)
	{
		//slope for x coordinate
		y0 = std::get<1>(curr)[0];
		y1 = std::get<1>(next)[0];
		x0 = std::get<0>(curr);
		x1 = std::get<0>(next);
		slope_x = int(std::floor(double(y1 - y0) / double(x1 - x0)));

		//slope for y coordinate
		y0 = std::get<1>(curr)[1];
		y1 = std::get<1>(next)[1];
		x0 = std::get<0>(curr);
		x1 = std::get<0>(next);
		slope_y = int(std::floor(double(y1 - y0) / double(x1 - x0)));

		//slope for width
		y0 = std::get<1>(curr)[2];
		y1 = std::get<1>(next)[2];
		x0 = std::get<0>(curr);
		x1 = std::get<0>(next);
		slope_w = int(std::floor(double(y1 - y0) / double(x1 - x0)));

		//slope for height
		y0 = std::get<1>(curr)[3];
		y1 = std::get<1>(next)[3];
		x0 = std::get<0>(curr);
		x1 = std::get<0>(next);
		slope_h = int(std::floor(double(y1 - y0) / double(x1 - x0)));

		for (int i = 0; i < vid_length; i++)
		{
			if (i >= std::get<0>(curr) && i < std::get<0>(next))
			{
				//Interpolate x coordinate
				y0 = std::get<1>(curr)[0];
				xc_int = y0 + (i - x0)*slope_x;

				//Interpolate y coordinate
				y0 = std::get<1>(curr)[1];
				yc_int = y0 + (i - x0)*slope_y;

				//Interpolate width
				y0 = std::get<1>(curr)[2];
				w_int = y0 + (i - x0)*slope_w;

				//Interpolate height
				y0 = std::get<1>(curr)[3];
				h_int = y0 + (i - x0)*slope_h;

				QVector<int> st;
				st.append(xc_int);
				st.append(yc_int);
				st.append(w_int);
				st.append(h_int);

				//Store new states according interpolation
				std::get<2>(AllROIs[fID])[i] = std::make_tuple(i, st);
			}
		}
	}
}

void ROI_interpolator::deleteROI_execDialog()
{
	QString input;
	bool valid_num;

	//Set error message 
	QMessageBox errorBox;
	errorBox.setWindowTitle("Error");
	errorBox.setIcon(QMessageBox::Icon::Critical);
	errorBox.setDefaultButton(QMessageBox::Ok);

	//Get ROI ID
	input = ROI_inter->ID_edit->text();
	valid_num = validateNumber(input);
	if (valid_num)
		delID = input.toInt();
	else
	{
		errorBox.setText("Set a valid ROI ID");
		errorBox.exec();
	}

	//Get ROI frame
	input = ROI_inter->frame_edit->text();
	valid_num = validateNumber(input);
	if (valid_num)
		delFrame = input.toInt();
	else
	{
		errorBox.setText("Set a valid ROI frame");
		errorBox.exec();
	}

	delete_ROI->delAll_radioButton->setChecked(true);
	delete_ROI->delCurr_radioButton->setChecked(false);
	deleteROI_dialog->exec();
}

void ROI_interpolator::accept_deleteROI()
{
	QVector<int> st(4, 0);

	//Delete delFrame ROI and subsequent ROIs from ALLROIs
	if (delete_ROI->delAll_radioButton->isChecked())
	{
		for (int i = delFrame; i < vid_length; i++)
		{
			std::get<2>(AllROIs[ID])[i] = std::make_tuple(i, st);
		}

		//Delete Key ROIs with frame bigger than delete point
		for (int i = 0; i < KeyROIs.size(); i++)
		{
			if (std::get<0>(KeyROIs[i]) == delID)
			{
				for (int j = 0; j < std::get<2>(KeyROIs[i]).size(); j++)
				{
					if (std::get<0>(std::get<2>(KeyROIs[i])[j]) >= delFrame)
						std::get<2>(KeyROIs[i]).erase(std::get<2>(KeyROIs[i]).begin() + j);
				}
				break;
			}
		}
	}	
	
	//Delete only delFrame ROI from ALLROIs
	if (delete_ROI->delCurr_radioButton->isChecked())
	{
		std::get<2>(AllROIs[ID])[frame] = std::make_tuple(frame, st);

		//Delete Key ROI if found any in delFrame
		for (int i = 0; i < KeyROIs.size(); i++)
		{
			if (std::get<0>(KeyROIs[i]) == delID)
			{
				for (int j = 0; j < std::get<2>(KeyROIs[i]).size(); j++)
				{
					if (std::get<0>(std::get<2>(KeyROIs[i])[j]) == delFrame)
						std::get<2>(KeyROIs[i]).erase(std::get<2>(KeyROIs[i]).begin()+j);
				}
				break;
			}
		}
	}

	deleteROI_dialog->close();
	updateTable();
}

void ROI_interpolator::cancel_deleteROI()
{

}

bool ROI_interpolator::validateNumber(const QString &Input)
{
	//convert qstring to string
	std::string Instr = Input.toLocal8Bit().constData();

	//iterate through string checking for no numbers
	return !Instr.empty() && std::find_if(Instr.begin(),
		Instr.end(), [](char c) { return !isdigit(c); }) == Instr.end();
}

void ROI_interpolator::initializeTable()
{
	QTableWidget *ROITable = ROI_inter->ROI_table;
	ROITable->setColumnCount(7);
	ROITable->setRowCount(vid_length);

	QStringList column_names;
	column_names << "ID" << "Class" << "Frame"<< "X"<< "Y" << "W"<< "H";
	ROITable->setHorizontalHeaderLabels(column_names);
	ROITable->setColumnWidth(0, 40);
	ROITable->setColumnWidth(1, 45);
	ROITable->setColumnWidth(2, 45);
	ROITable->setColumnWidth(3, 40);
	ROITable->setColumnWidth(4, 40);
	ROITable->setColumnWidth(5, 40);
	ROITable->setColumnWidth(6, 40);

	ROITable->verticalHeader()->setVisible(false);
	ROITable->horizontalHeader()->setStretchLastSection(true);

	//Initialize edits
	ROI_inter->ID_edit->setText("0");
	ROI_inter->frame_edit->setText("3");
	ROI_inter->x_edit->setText("100");
	ROI_inter->y_edit->setText("100");
	ROI_inter->w_edit->setText("20");
	ROI_inter->h_edit->setText("20");
}

void ROI_interpolator::updateTable()
{
	QTableWidget *ROITable = ROI_inter->ROI_table;

	ROITable->setRowCount(NROI*vid_length);

	//std::cout<< "frame:"<< frame << "x:" << states[0] << "y:" << states[1] << "w:" << states[2] << "h:" << states[3]<< std::endl;

	for (int j = 0; j < NROI; j++)
	{
		int currID = std::get<0>(AllROIs[j]);

		for (int i = 0; i < vid_length; i++)
		{
			int ROIstep = (j * vid_length);

			QTableWidgetItem * id_item = new QTableWidgetItem(QString::number(currID));
			id_item->setFlags(Qt::NoItemFlags);
			ROITable->setItem(i + ROIstep, 0, id_item);

			QTableWidgetItem * lbl_item = new QTableWidgetItem(QString::number(1));
			lbl_item->setFlags(Qt::NoItemFlags);
			ROITable->setItem(i + ROIstep, 1, lbl_item);

			QTableWidgetItem * frame_item = new QTableWidgetItem(QString::number(i));
			frame_item->setFlags(Qt::NoItemFlags);
			ROITable->setItem(i + ROIstep, 2, frame_item);

			int x_item_num = std::get<1>(std::get<2>(AllROIs[j])[i])[0];
			QTableWidgetItem * x_item = new QTableWidgetItem(QString::number(x_item_num));
			x_item->setFlags(Qt::NoItemFlags);
			ROITable->setItem(i + ROIstep, 3, x_item);

			int y_item_num = std::get<1>(std::get<2>(AllROIs[j])[i])[1];
			QTableWidgetItem * y_item = new QTableWidgetItem(QString::number(y_item_num));
			y_item->setFlags(Qt::NoItemFlags);
			ROITable->setItem(i + ROIstep, 4, y_item);

			int w_item_num = std::get<1>(std::get<2>(AllROIs[j])[i])[2];
			QTableWidgetItem * w_item = new QTableWidgetItem(QString::number(w_item_num));
			w_item->setFlags(Qt::NoItemFlags);
			ROITable->setItem(i + ROIstep, 5, w_item);

			int h_item_num = std::get<1>(std::get<2>(AllROIs[j])[i])[3];
			QTableWidgetItem * h_item = new QTableWidgetItem(QString::number(h_item_num));
			h_item->setFlags(Qt::NoItemFlags);
			ROITable->setItem(i + ROIstep, 6, h_item);

		}
	}
}