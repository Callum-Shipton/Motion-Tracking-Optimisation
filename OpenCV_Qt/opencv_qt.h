#ifndef OPENCV_QT_H
#define OPENCV_QT_H

#include <QtWidgets/QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include "ui_opencv_qt.h"
#include <player.h>
#include <QTime>
namespace Ui {
	class MainWindow;
}

class OpenCV_Qt : public QMainWindow
{
	Q_OBJECT

public:
	explicit OpenCV_Qt(QWidget *parent = 0);
	~OpenCV_Qt();

private slots:
	//Display video frame in player UI
	void updatePlayerUI(QImage img);
	//Slot for the load video push button.
	void on_pushButton_clicked();
	// Slot for the play push button.
	void on_pushButton_2_clicked();
	// Slot for the update background button.
	void on_pushButton_3_clicked();

	QString getFormattedTime(int timeInSeconds);
	void on_horizontalSlider_sliderPressed();
	void on_horizontalSlider_sliderReleased();
	void on_horizontalSlider_sliderMoved(int position);

private:
	Ui::OpenCV_QtClass ui;
	Player* myPlayer;
};

#endif // OPENCV_QT_H
