#include "opencv_qt.h"
#include <iostream>
#include <opencv2\core.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace cv;
using namespace std;

OpenCV_Qt::OpenCV_Qt(QWidget *parent)
	: QMainWindow(parent)
{

	myPlayer = new Player();
	QObject::connect(myPlayer, SIGNAL(processedImage(QImage)),
		this, SLOT(updatePlayerUI(QImage)));
	ui.setupUi(this);

	ui.pushButton_2->setEnabled(false);
	ui.horizontalSlider->setEnabled(false);

	//string fileName = "D:/Documents/Visual Studio 2013/Projects/OpenCV_App/Debug/Tennis1.mkv";
	//VideoCapture capture(fileName); // Read the file

	//if (!capture.isOpened()) // Check for invalid input
	//{
	//	cout << "Could not open or find the video" << std::endl;
	//	exit(-1);
	//}

	//namedWindow("Cont", CV_WINDOW_AUTOSIZE | CV_GUI_NORMAL); //create a window called "Control"
	//char* nameb1 = "button1";
	////cvCreateButton(nameb1, NULL, nameb1, CV_PUSH_BUTTON);
	//int iLowH = 13;
	//int iHighH = 50;

	//int iLowS = 68;
	//int iHighS = 175;

	//int iLowV = 110;
	//int iHighV = 255;

	////Create trackbars in "Control" window
	//cvCreateTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
	//cvCreateTrackbar("HighH", "Control", &iHighH, 179);

	//cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
	//cvCreateTrackbar("HighS", "Control", &iHighS, 255);

	//cvCreateTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
	//cvCreateTrackbar("HighV", "Control", &iHighV, 255);


	//namedWindow("Video Playback", 1); // Create a window for display.

	//Mat videoInput;
	//for (;;)
	//{
	//	Mat frame;
	//	capture >> frame;
	//	if (frame.empty())
	//		break;

	//	Mat imgHSV;

	//	cvtColor(frame, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

	//	//Mat imgThresholded;

	//	inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), videoInput); //Threshold the image

	//	//morphological opening (remove small objects from the foreground)
	//	//erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	//	//dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

	//	//morphological closing (fill small holes in the foreground)
	//	//dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	//	//erode(imgThresholded, videoInput, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

	//	//GaussianBlur(imgThresholded, videoInput, Size(15, 15), 0, 0);

	//	imshow("Thresholded", videoInput);

	//  vector<Vec3f> circles;

	//	//input, storage, detection, inverse ratio of resolution, minimum distance between circles, canny edge parameter, center detection threshold, minimum ratio, max radius
	//	/*HoughCircles(videoInput, circles, CV_HOUGH_GRADIENT, 1, videoInput.rows / 8, 100, 10, 0, 10);
	//	for (size_t i = 0; i < circles.size(); i++)
	//	{
	//	Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
	//	int radius = cvRound(circles[i][2]);
	//	circle(frame, center, 3, Scalar(0, 255, 0), -1, 8, 0);
	//	circle(frame, center, radius, Scalar(0, 0, 255), 3, 8, 0);
	//	}*/
	//	imshow("Video Playback", frame);
	//	if (waitKey(17) >= 0) break;;
	//}
	//exit(0);

}

OpenCV_Qt::~OpenCV_Qt()
{
	delete myPlayer;
}

void OpenCV_Qt::on_pushButton_clicked()
{
	QString filename = QFileDialog::getOpenFileName(this,
		tr("Open Video"), ".",
		tr("Video Files (*.avi *.mpg *.mp4)"));
	QFileInfo name = filename;
	if (!filename.isEmpty()){
		if (!myPlayer->loadVideo(filename.toStdString()))
		{
			QMessageBox msgBox;
			msgBox.setText("The selected video could not be opened!");
			msgBox.exec();
		}
		else{
			this->setWindowTitle(name.fileName());
			ui.pushButton_2->setEnabled(true);
			ui.horizontalSlider->setEnabled(true);
			ui.horizontalSlider->setMaximum(myPlayer->getNumberOfFrames());
			ui.label_3->setText(getFormattedTime((int)myPlayer->getNumberOfFrames() / (int)myPlayer->getFrameRate()));
		}
	}
}

QString OpenCV_Qt::getFormattedTime(int timeInSeconds){
	int seconds = (int)(timeInSeconds) % 60;
	int minutes = (int)((timeInSeconds / 60) % 60);
	int hours = (int)((timeInSeconds / (60 * 60)) % 24);
	QTime t(hours, minutes, seconds);
	if (hours == 0)
		return t.toString("mm:ss");
	else
		return t.toString("h:mm:ss");
}
void OpenCV_Qt::on_horizontalSlider_sliderPressed()
{
	myPlayer->Stop();
}
void OpenCV_Qt::on_horizontalSlider_sliderReleased()
{
	myPlayer->Play();
}
void OpenCV_Qt::on_horizontalSlider_sliderMoved(int position)
{
	myPlayer->setCurrentFrame(position);
	ui.label_2->setText(getFormattedTime(position / (int)myPlayer->getFrameRate()));
}
void OpenCV_Qt::on_pushButton_2_clicked()
{
	if (myPlayer->isStopped())
	{
		myPlayer->Play();
		ui.pushButton_2->setText(tr("Stop"));
	}
	else
	{
		myPlayer->Stop();
		ui.pushButton_2->setText(tr("Play"));
	}
}
void OpenCV_Qt::on_pushButton_3_clicked()
{
	myPlayer->Update();
}

void OpenCV_Qt::updatePlayerUI(QImage img)
{
	if (!img.isNull())
	{
		ui.label->setAlignment(Qt::AlignCenter);
		ui.label->setPixmap(QPixmap::fromImage(img).scaled(ui.label->size(),Qt::KeepAspectRatio, Qt::FastTransformation));

		ui.horizontalSlider->setValue(myPlayer->getCurrentFrame());
		ui.label_2->setText(getFormattedTime((int)myPlayer->getCurrentFrame() / (int)myPlayer->getFrameRate()));
	}
}