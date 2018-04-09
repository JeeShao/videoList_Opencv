#include"video.h"

Video::Video()
{
	frame = NULL;
}

Video::~Video()
{
}

Mat Video::getYCrCbFrame()			 //获取YCrCb色度空间图像
{
	Mat YCrCbFrame;
	readCap();

	cvtColor(frame, YCrCbFrame, CV_BGR2YCrCb);
	//flip(YCrCbFrame, YCrCbFrame, 1);
	return YCrCbFrame;
}

Mat Video::readCap()				//摄像头读取图像
{
	if (!cap.isOpened())
		cap.open(1);
	bool ret;
	ret = cap.read(frame);
	if (ret)
		//flip(frame, frame, 1);
		return frame;
	cout << string("video.cpp:未读取到图像！");
}

void Video::releaseCap()
{
	if (cap.isOpened())
		cap.release();
}