/********************************************************************************
** Form generated from reading UI file 'opencv_qt.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPENCV_QT_H
#define UI_OPENCV_QT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OpenCV_QtClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QSlider *horizontalSlider;
    QLabel *label_3;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *OpenCV_QtClass)
    {
        if (OpenCV_QtClass->objectName().isEmpty())
            OpenCV_QtClass->setObjectName(QStringLiteral("OpenCV_QtClass"));
        OpenCV_QtClass->resize(899, 765);
        centralWidget = new QWidget(OpenCV_QtClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setStyleSheet(QStringLiteral("Background-color: #000;"));

        verticalLayout_2->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        horizontalSlider = new QSlider(centralWidget);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(horizontalSlider);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout->addWidget(label_3);


        verticalLayout_2->addLayout(horizontalLayout);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout_2->addWidget(pushButton);

        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        verticalLayout_2->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        verticalLayout_2->addWidget(pushButton_3);

        verticalLayout_2->setStretch(0, 9);
        verticalLayout_2->setStretch(1, 1);

        verticalLayout->addLayout(verticalLayout_2);

        OpenCV_QtClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(OpenCV_QtClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 899, 21));
        OpenCV_QtClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(OpenCV_QtClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        OpenCV_QtClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(OpenCV_QtClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        OpenCV_QtClass->setStatusBar(statusBar);

        retranslateUi(OpenCV_QtClass);

        QMetaObject::connectSlotsByName(OpenCV_QtClass);
    } // setupUi

    void retranslateUi(QMainWindow *OpenCV_QtClass)
    {
        OpenCV_QtClass->setWindowTitle(QApplication::translate("OpenCV_QtClass", "OpenCV_Qt", 0));
        label->setText(QString());
        label_2->setText(QApplication::translate("OpenCV_QtClass", "0:00", 0));
        label_3->setText(QApplication::translate("OpenCV_QtClass", "0:00", 0));
        pushButton->setText(QApplication::translate("OpenCV_QtClass", "Load Video", 0));
        pushButton_2->setText(QApplication::translate("OpenCV_QtClass", "Play", 0));
        pushButton_3->setText(QApplication::translate("OpenCV_QtClass", "Update Background", 0));
    } // retranslateUi

};

namespace Ui {
    class OpenCV_QtClass: public Ui_OpenCV_QtClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPENCV_QT_H
