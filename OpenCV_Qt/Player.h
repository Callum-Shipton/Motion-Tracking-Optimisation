#ifndef PLAYER_H
#define PLAYER_H
#include <QMutex>
#include <QThread>
#include <QImage>
#include <QWaitCondition>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2\video\video.hpp>
#include <opencv2\video\tracking.hpp>
#include <opencv2\video\background_segm.hpp>

using namespace cv;
class Player : public QThread
{
	Q_OBJECT
private:
	bool stop;
	bool update_bg_model = false;
	bool update_hist_model = false;
	QMutex mutex;
	QWaitCondition condition;
	Mat frame;
	int frameRate;
	VideoCapture capture;
	Mat RGBframe;
	QImage img;
	int iLowH = 0;
	int iHighH = 255;

	int iLowS = 188;
	int iHighS = 255;

	int iLowV = 0;
	int iHighV = 255;
signals:
	//Signal to output frame to be displayed
	void processedImage(const QImage &image);
protected:
	void run();
public:
	//Constructor
	Player(QObject *parent = 0);
	//Destructor
	~Player();
	//Load a video from memory
	bool loadVideo(std::string filename);
	//Play the video
	void Play();
	//Stop the video
	void Stop();
	//Play the video
	void Update();
	//check if the player has been stopped
	bool isStopped() const;
	//check if the background is updating
	bool isUpdating() const;
	//set video current frame
	void setCurrentFrame(int frameNumber);
	//Get video properties
	double getFrameRate();
	double getCurrentFrame();
	double getNumberOfFrames();
};
#endif // VIDEOPLAYER_H