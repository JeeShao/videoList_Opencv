//#include<iostream>
//#include<opencv2\opencv.hpp>
//using namespace std;
//using namespace cv;
//
//void main()
//{
//	Mat  img = imread("./pic/1.jpg");
//	cout << img.rows << " " << img.cols << "  " << img.type();
//	system("pause");
//}
//
////
////using namespace std;
////using namespace cv;
////
////void main()
////{
////	Mat frame;
////	vector<Mat>	frames(10);
////	VideoCapture cap(0);
////	Mat img = Mat::zeros(frames[0].rows, frames[0].cols, frames[0].type());
////
////	while (true)
////	{
////
////		for (int i = 0; i < 8; i++)
////		{
////			cap.read(frame);
////			flip(frame, frame, 1);
////			frames[i] = frame.clone();
////		}
////		addWeighted(frames[0], 0.5, frames[1], 0.5, 0.0, frames[0]);
////		addWeighted(frames[2], 0.5, frames[3], 0.5, 0.0, frames[2]);
////		addWeighted(frames[4], 0.5, frames[5], 0.5, 0.0, frames[4]);
////		addWeighted(frames[6], 0.5, frames[7], 0.5, 0.0, frames[6]);
////
////		addWeighted(frames[0], 0.5, frames[2], 0.5, 0.0, frames[0]);
////		addWeighted(frames[4], 0.5, frames[6], 0.5, 0.0, frames[4]);
////
////		addWeighted(frames[0], 0.5, frames[4], 0.5, 0.0, img);
////
////
////
////
////
////		//int rowNumber = frames[0].rows;                           //获取图像矩阵行数
////		//int colNumber = frames[0].cols*frames[0].channels();    //三通道图像每行元素个数为列数x通道数
////
////		//for (int i = 0; i < rowNumber; i++)
////		//	for (int j = 0; j < colNumber; j++)
////		//	{
////		//		for (int n = 0; n < 4; n++)
////		//		{
////
////		//			//uchar* pixelPtr = frames[j].ptr<uchar>(i);            //获取矩阵每行首地址指针
////		//			//pixelPtr[j] = pixelPtr[j];
////		//			img.ptr<uchar>(i)[j] += frames[n].ptr<uchar>(i)[j];
////		//		}
////		//		img.ptr<uchar>(i)[j] = round(img.ptr<uchar>(i)[j] / 2);
////		//	}
////		imshow("img", img);
////		waitKey(1);
////
////	}
////}