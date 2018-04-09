#include"video.h"

Video::Video()
{
	frame = NULL;
}

Video::~Video()
{
}

Mat Video::getYCrCbFrame()			 //��ȡYCrCbɫ�ȿռ�ͼ��
{
	Mat YCrCbFrame;
	readCap();

	cvtColor(frame, YCrCbFrame, CV_BGR2YCrCb);
	//flip(YCrCbFrame, YCrCbFrame, 1);
	return YCrCbFrame;
}

Mat Video::readCap()				//����ͷ��ȡͼ��
{
	if (!cap.isOpened())
		cap.open(1);
	bool ret;
	ret = cap.read(frame);
	if (ret)
		//flip(frame, frame, 1);
		return frame;
	cout << string("video.cpp:δ��ȡ��ͼ��");
}

void Video::releaseCap()
{
	if (cap.isOpened())
		cap.release();
}