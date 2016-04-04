#include "Player.h"


Player::Player(QObject *parent)
	: QThread(parent)
{
	stop = true;
}

Player::~Player()
{
	mutex.lock();
	stop = true;
	capture.release();
	condition.wakeOne();
	mutex.unlock();
	wait();
}
void Player::Stop()
{
	stop = true;
}
bool Player::isStopped() const{
	return this->stop;
}

bool Player::isUpdating() const{
	return this->update_hist_model;
}
void Player::run()
{
	ulong delay = (1000 / frameRate);

	namedWindow("Control", CV_WINDOW_AUTOSIZE | CV_GUI_NORMAL); //create a window called "Control"

	cvCreateTrackbar("LowH", "Control", &iLowH, 255); //Hue (0 - 179)
	cvCreateTrackbar("HighH", "Control", &iHighH, 255);

	cvCreateTrackbar("LowL", "Control", &iLowS, 255); //Lightness (0 - 255)
	cvCreateTrackbar("HighL", "Control", &iHighS, 255);

	cvCreateTrackbar("LowS", "Control", &iLowV, 255); //Saturation (0 - 255)
	cvCreateTrackbar("HighS", "Control", &iHighV, 255);

	Mat src_base, hsv_base, hsv_frame;

	MatND hist_base, hist_frame;
	Mat fgmask,bgimg,fgimg;

	int h_bins = 50; int s_bins = 60;
	int histSize[] = { h_bins, s_bins };

	// hue varies from 0 to 179, saturation from 0 to 255
	float h_ranges[] = { 0, 180 };
	float s_ranges[] = { 0, 256 };

	const float* ranges[] = { h_ranges, s_ranges };

	// Use the o-th and 1-st channels
	int channels[] = { 0, 1 };

	Mat fgimg2, fgimg3, fgimg4, fgimg5;

	Ptr<BackgroundSubtractor> bg_model = createBackgroundSubtractorMOG2(100,64, false).dynamicCast<BackgroundSubtractor>();

	while (!stop){
		if (!capture.read(frame))
		{
			stop = true;
		}
		if (frame.channels() == 3){
			//Rect myROI(192, 150, 900, 544);
			Rect myROI(400, 50, 1230, 830);
			// Crop the full image to that image contained by the rectangle myROI
			// Note that this doesn't copy the data

			

			Mat croppedImage = frame(myROI);
			//GaussianBlur(croppedImage, croppedImage, Size(5, 5), 4.5, 4.5);

			

			if (update_hist_model){
				//Code for replacing hist
				src_base = frame.clone();
				cvtColor(src_base, hsv_base, COLOR_BGR2HSV);

				calcHist(&hsv_base, 1, channels, Mat(), hist_base, 2, histSize, ranges, true, false);
				normalize(hist_base, hist_base, 0, 1, NORM_MINMAX, -1, Mat());

				update_hist_model = false;
			}

			cvtColor(frame, hsv_frame, COLOR_BGR2HSV);

			calcHist(&hsv_frame, 1, channels, Mat(), hist_frame, 2, histSize, ranges, true, false);
			normalize(hist_frame, hist_frame, 0, 1, NORM_MINMAX, -1, Mat());

			

			if (!src_base.empty()){
				double base = compareHist(hist_base, hist_frame, 0);
				printf("%d", base);
				if (base > 0.98) update_bg_model = true;
				else update_bg_model = false;
			}
			if (update_bg_model){
				bg_model->apply(croppedImage, fgmask, update_bg_model ? -10 : 0);
				bg_model->getBackgroundImage(bgimg);
				fgimg = Scalar::all(0);
				Mat court = croppedImage.clone();
				cvtColor(court, court, COLOR_BGR2HLS); //Convert the captured frame from BGR to HSV
				inRange(court, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), court); //Threshold the image
				dilate(court, court, getStructuringElement(MORPH_ELLIPSE, Size(7, 7)));
				fgmask = fgmask - court;
				//// morphological opening (remove small objects from the foreground)
				erode(fgmask, fgmask, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)));
				dilate(fgmask, fgmask, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)));

				//  morphological closing (fill small holes in the foreground)
					dilate(fgmask, fgmask, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)));
					erode(fgmask, fgmask, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)));
					fgimg5 = fgimg4.clone();
					fgimg4 = fgimg3.clone();
					fgimg3 = fgimg2.clone();
					fgimg2 = fgimg.clone();
				croppedImage.copyTo(fgimg, fgmask);
				imshow("foreground mask", fgmask);
				imshow("foreground image", fgimg);
				imshow("court", court);
				if (!bgimg.empty())
					imshow("mean background image", bgimg);
			}
			cv::cvtColor(frame, frame, CV_BGR2RGB);
			img = QImage((const unsigned char*)(frame.data),
				frame.cols, frame.rows, QImage::Format_RGB888);

		}
		else
		{
			img = QImage((const unsigned char*)(frame.data),
				frame.cols, frame.rows, QImage::Format_Indexed8);
		}
		emit processedImage(img);
		this->msleep(delay);
	}
}

void Player::Play()
{
	if (!isRunning()) {
		if (isStopped()){
			stop = false;
		}
		start(LowPriority);
	}
}

void Player::Update()
{
	update_hist_model = true;
}

bool Player::loadVideo(std::string filename) {
	capture.open(filename);
	if (capture.isOpened())
	{
		frameRate = (int)capture.get(CV_CAP_PROP_FPS);
		return true;
	}
	else
		return false;
}

double Player::getCurrentFrame(){
	return capture.get(CV_CAP_PROP_POS_FRAMES);
}
double Player::getNumberOfFrames(){
	return capture.get(CV_CAP_PROP_FRAME_COUNT);
}
double Player::getFrameRate(){
	return frameRate;
}
void Player::setCurrentFrame(int frameNumber)
{
	capture.set(CV_CAP_PROP_POS_FRAMES, frameNumber);
}
