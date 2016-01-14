/********************************************************************************
** Form generated from reading UI file 'roi_interpolator.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROI_INTERPOLATOR_H
#define UI_ROI_INTERPOLATOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ROI_interpolatorClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_5;
    QGroupBox *groupBox;
    QWidget *verticalLayoutWidget_4;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label;
    QLineEdit *ID_edit;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_3;
    QLineEdit *x_edit;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_5;
    QLineEdit *w_edit;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_2;
    QLineEdit *frame_edit;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_4;
    QLineEdit *y_edit;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_6;
    QLineEdit *h_edit;
    QHBoxLayout *horizontalLayout_14;
    QSpacerItem *horizontalSpacer;
    QPushButton *addROI_button;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *deleteROI_button;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_6;
    QGroupBox *groupBox_2;
    QTableWidget *ROI_table;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *ROI_interpolatorClass)
    {
        if (ROI_interpolatorClass->objectName().isEmpty())
            ROI_interpolatorClass->setObjectName(QStringLiteral("ROI_interpolatorClass"));
        ROI_interpolatorClass->resize(351, 413);
        centralWidget = new QWidget(ROI_interpolatorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_5 = new QVBoxLayout(centralWidget);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayoutWidget_4 = new QWidget(groupBox);
        verticalLayoutWidget_4->setObjectName(QStringLiteral("verticalLayoutWidget_4"));
        verticalLayoutWidget_4->setGeometry(QRect(9, 19, 311, 151));
        verticalLayout_4 = new QVBoxLayout(verticalLayoutWidget_4);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label = new QLabel(verticalLayoutWidget_4);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMinimumSize(QSize(50, 0));

        horizontalLayout_8->addWidget(label);

        ID_edit = new QLineEdit(verticalLayoutWidget_4);
        ID_edit->setObjectName(QStringLiteral("ID_edit"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(ID_edit->sizePolicy().hasHeightForWidth());
        ID_edit->setSizePolicy(sizePolicy1);
        ID_edit->setMinimumSize(QSize(50, 0));
        ID_edit->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_8->addWidget(ID_edit);


        verticalLayout_2->addLayout(horizontalLayout_8);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_3 = new QLabel(verticalLayoutWidget_4);
        label_3->setObjectName(QStringLiteral("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        label_3->setMinimumSize(QSize(50, 0));

        horizontalLayout_10->addWidget(label_3);

        x_edit = new QLineEdit(verticalLayoutWidget_4);
        x_edit->setObjectName(QStringLiteral("x_edit"));
        sizePolicy1.setHeightForWidth(x_edit->sizePolicy().hasHeightForWidth());
        x_edit->setSizePolicy(sizePolicy1);
        x_edit->setMinimumSize(QSize(50, 0));
        x_edit->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_10->addWidget(x_edit);


        verticalLayout_2->addLayout(horizontalLayout_10);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_5 = new QLabel(verticalLayoutWidget_4);
        label_5->setObjectName(QStringLiteral("label_5"));
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);
        label_5->setMinimumSize(QSize(50, 0));

        horizontalLayout_9->addWidget(label_5);

        w_edit = new QLineEdit(verticalLayoutWidget_4);
        w_edit->setObjectName(QStringLiteral("w_edit"));
        sizePolicy1.setHeightForWidth(w_edit->sizePolicy().hasHeightForWidth());
        w_edit->setSizePolicy(sizePolicy1);
        w_edit->setMinimumSize(QSize(50, 0));
        w_edit->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_9->addWidget(w_edit);


        verticalLayout_2->addLayout(horizontalLayout_9);


        horizontalLayout_7->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label_2 = new QLabel(verticalLayoutWidget_4);
        label_2->setObjectName(QStringLiteral("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setMinimumSize(QSize(50, 0));

        horizontalLayout_11->addWidget(label_2);

        frame_edit = new QLineEdit(verticalLayoutWidget_4);
        frame_edit->setObjectName(QStringLiteral("frame_edit"));
        sizePolicy1.setHeightForWidth(frame_edit->sizePolicy().hasHeightForWidth());
        frame_edit->setSizePolicy(sizePolicy1);
        frame_edit->setMinimumSize(QSize(50, 0));
        frame_edit->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_11->addWidget(frame_edit);


        verticalLayout_3->addLayout(horizontalLayout_11);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        label_4 = new QLabel(verticalLayoutWidget_4);
        label_4->setObjectName(QStringLiteral("label_4"));
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);
        label_4->setMinimumSize(QSize(50, 0));

        horizontalLayout_13->addWidget(label_4);

        y_edit = new QLineEdit(verticalLayoutWidget_4);
        y_edit->setObjectName(QStringLiteral("y_edit"));
        sizePolicy1.setHeightForWidth(y_edit->sizePolicy().hasHeightForWidth());
        y_edit->setSizePolicy(sizePolicy1);
        y_edit->setMinimumSize(QSize(50, 0));
        y_edit->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_13->addWidget(y_edit);


        verticalLayout_3->addLayout(horizontalLayout_13);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        label_6 = new QLabel(verticalLayoutWidget_4);
        label_6->setObjectName(QStringLiteral("label_6"));
        sizePolicy.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy);
        label_6->setMinimumSize(QSize(50, 0));

        horizontalLayout_12->addWidget(label_6);

        h_edit = new QLineEdit(verticalLayoutWidget_4);
        h_edit->setObjectName(QStringLiteral("h_edit"));
        sizePolicy1.setHeightForWidth(h_edit->sizePolicy().hasHeightForWidth());
        h_edit->setSizePolicy(sizePolicy1);
        h_edit->setMinimumSize(QSize(50, 0));
        h_edit->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_12->addWidget(h_edit);


        verticalLayout_3->addLayout(horizontalLayout_12);


        horizontalLayout_7->addLayout(verticalLayout_3);


        verticalLayout_4->addLayout(horizontalLayout_7);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer);

        addROI_button = new QPushButton(verticalLayoutWidget_4);
        addROI_button->setObjectName(QStringLiteral("addROI_button"));

        horizontalLayout_14->addWidget(addROI_button);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_2);

        deleteROI_button = new QPushButton(verticalLayoutWidget_4);
        deleteROI_button->setObjectName(QStringLiteral("deleteROI_button"));

        horizontalLayout_14->addWidget(deleteROI_button);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_3);


        verticalLayout_4->addLayout(horizontalLayout_14);


        horizontalLayout_5->addWidget(groupBox);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        ROI_table = new QTableWidget(groupBox_2);
        ROI_table->setObjectName(QStringLiteral("ROI_table"));
        ROI_table->setGeometry(QRect(10, 30, 311, 121));

        horizontalLayout_6->addWidget(groupBox_2);


        verticalLayout->addLayout(horizontalLayout_6);


        verticalLayout_5->addLayout(verticalLayout);

        ROI_interpolatorClass->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(ROI_interpolatorClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ROI_interpolatorClass->addToolBar(Qt::TopToolBarArea, mainToolBar);

        retranslateUi(ROI_interpolatorClass);

        QMetaObject::connectSlotsByName(ROI_interpolatorClass);
    } // setupUi

    void retranslateUi(QMainWindow *ROI_interpolatorClass)
    {
        ROI_interpolatorClass->setWindowTitle(QApplication::translate("ROI_interpolatorClass", "ROI_interpolator", 0));
        groupBox->setTitle(QApplication::translate("ROI_interpolatorClass", "ROI input", 0));
        label->setText(QApplication::translate("ROI_interpolatorClass", "ID", 0));
        label_3->setText(QApplication::translate("ROI_interpolatorClass", "X", 0));
        label_5->setText(QApplication::translate("ROI_interpolatorClass", "W", 0));
        label_2->setText(QApplication::translate("ROI_interpolatorClass", "Frame", 0));
        label_4->setText(QApplication::translate("ROI_interpolatorClass", "Y", 0));
        label_6->setText(QApplication::translate("ROI_interpolatorClass", "H", 0));
        addROI_button->setText(QApplication::translate("ROI_interpolatorClass", "Add ROI", 0));
        deleteROI_button->setText(QApplication::translate("ROI_interpolatorClass", "Delete ROI", 0));
        groupBox_2->setTitle(QApplication::translate("ROI_interpolatorClass", "ROI summary", 0));
    } // retranslateUi

};

namespace Ui {
    class ROI_interpolatorClass: public Ui_ROI_interpolatorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROI_INTERPOLATOR_H
