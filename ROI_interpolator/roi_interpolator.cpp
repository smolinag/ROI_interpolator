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

			if (mindif_idx - 1 > 0)
			{
				KROI_prev = std::get<2>(KeyROIs[fID])[mindif_idx + 1];
			}

			//Insert new KROI
			std::get<2>(KeyROIs[fID]).insert(mindif_idx - 1, newKROI);
		}

		//Current indexed ROI's frame is equal to a previous one
		if (mindif == 0)
		{

		}
	}

	interpolation(KROI_prev, newKROI, KROI_next, fID);

	updateTable();
}

void ROI_interpolator::interpolation(KeyROI prev, KeyROI curr, KeyROI next, int fID)
{
	QVector<KeyROI> interpROI_states;

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

	//Linear interpolation until last
	if (std::get<1>(prev).size() == 0 != std::get<1>(next).size() == 0)
	{

	}
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

	std::cout << "x:" << states[0] << "y:" << states[1] << "w:" << states[2] << "h:" << states[3]<< std::endl;

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