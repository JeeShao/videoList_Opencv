#include<iostream>
#include<thread>
#include<ctime>
#include<mutex>
#include<opencv2\opencv.hpp>
#include"video.h"
#include"decision.h"
#include"cycleQueue.h"

using namespace std;
using namespace cv;
mutex mu;
cycleQueue<Mat> q(50);


void combin(vector<Mat> frames, Mat &dstImage, int div)
{
	//for (int i = 0; i < 8; i++)
	//{
	//	cap.read(frame);
	//	flip(frame, frame, 1);
	//	frames[i] = frame.clone();
	//}
	//addWeighted(frames[0], 0.5, frames[1], 0.5, 0.0, frames[0]);
	//addWeighted(frames[2], 0.5, frames[3], 0.5, 0.0, frames[2]);
	//addWeighted(frames[4], 0.5, frames[5], 0.5, 0.0, frames[4]);
	//addWeighted(frames[6], 0.5, frames[7], 0.5, 0.0, frames[6]);

	//addWeighted(frames[0], 0.5, frames[2], 0.5, 0.0, frames[0]);
	//addWeighted(frames[4], 0.5, frames[6], 0.5, 0.0, frames[4]);	 

	addWeighted(frames[0], 0.5, frames[1], 0.5, 0.0, dstImage);
	//return dstImage;
}

void getImgs()
{
	clock_t start, finish;

	Mat  frame0/*,frame1,frame2*/;
	Video video;
	int i;
	vector<Mat>	frames(8);
	frame0 = video.getYCrCbFrame();
	Mat frame = Mat::zeros(frame0.rows, frame0.cols, frame0.type());

	while (1)
	{
		if (!q.isFull()) {
			start = clock();

			for (i = 0; i < 2; i++)     //耗时代码150ms 
				frames[i] = video.getYCrCbFrame();
			//{
			//	
			//}
			//frame1 = video.getYCrCbFrame();
			//frame2 = video.getYCrCbFrame();
			//addWeighted(frame1, 0.5, frame2, 0.5, 0.0, frame);


			combin(frames, frame, 4);	  //耗时代码110ms
			finish = clock();

			//mu.lock();
			q.push(frame);
			cout << "读取合成耗时： " << finish - start << "ms" << "  ";
			//mu.unlock();
		}
		/*else {
			cout << "队列已满" << endl;
		}*/
		
	}
}

void readImgs(Mat img1,Mat img2)
	{
		Mat oriFrame;
		clock_t s, f;

		//int rowNumber = frames[0].rows;                           //获取图像矩阵行数
		//int colNumber = frames[0].cols*frames[0].channels();    //三通道图像每行元素个数为列数x通道数
		//for (i = 0; i < rowNumber; i++)
		//	for (int j = 0; j < colNumber; j++)
		//	{
		//		for (int n = 0; n < 10; n++)
		//		{
		//			//uchar* pixelPtr = frames[j].ptr<uchar>(i);            //获取矩阵每行首地址指针
		//			//pixelPtr[j] = pixelPtr[j];
		//			frame.ptr<uchar>(i)[j] += frames[n].ptr<uchar>(i)[j];
		//		}
		//		frame.ptr<uchar>(i)[j] = round(frame.ptr<uchar>(i)[j] / 10);
		//	}
		//string path = "./pic";
		//int count = 1;
		Mat frame,bg_img;
		Decision decision;
		while (true)
		{
			if (!q.isEmpty())
			{
				s = clock();

				decision.set2img(img1, img2);
				//mu.lock();
				frame = q.pop();
				//imwrite(path + format("/%d.jpg", count++), frame);
				//mu.unlock();
				decision.setFrame(frame);
				bg_img = decision.toBgrImg();			   //耗时代码 300ms

				cout << "火花点数：" << decision.decision() << "   " << endl << endl;				//耗时代码 100ms
				f = clock();
				cvtColor(frame, oriFrame, CV_YCrCb2BGR);
				imshow("frame", oriFrame);
				imshow("背景", bg_img);
				img1 = img2.clone();
				img2 = frame.clone();
				cout << "背景转换耗时：" << f - s << "ms" << "  ";
				waitKey(1);
			}
			else
				cout << "队列为空" << endl;	 
		}
	}

void saveImg(){
	int count = 1;
	string path = "./pic";
	while (true)
	{
		if (!q.isEmpty()) {
			imwrite(path + format("/%d.jpg", count++), q.getTop());
		}
	}
	
}

void main()
{
	Mat img1, img2;
	VideoCapture cap(0);
	cap.read(img1);
	cap.read(img2);
	//img1=imread("./pic/117.jpg");
	//img2=imread("./pic/117.jpg");

	//flip(img1, img1, 1);
	//flip(img2, img2, 1);
	cvtColor(img1, img1, CV_BGR2YCrCb);
	cvtColor(img1, img1, CV_BGR2YCrCb);



	thread thread1(getImgs);
	thread thread2(readImgs, img1, img2);
	thread thread3(saveImg);

	thread1.join();
	thread2.join();
	thread3.join();
}
	
