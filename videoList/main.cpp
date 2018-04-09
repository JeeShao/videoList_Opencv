//#include<iostream>
//#include<opencv2\opencv.hpp>
//#include"video.h"
//#include"decision.h"
//
//void main()
//{
//	Mat img1,img2,frame,bg_img;
//	Video video;				
//	img1 = video.getYCrCbFrame();
//	img2 = video.getYCrCbFrame();
//	frame = video.getYCrCbFrame();
//	Decision decision(frame);
//	while (1)
//	{
//		decision.set2img(img1, img2);
//		decision.setFrame(frame);
//		bg_img = decision.toBgrImg();			   //耗时代码
//		cout << decision.decision() << "   ";				//耗时代码
//		imshow("img1", img1);
//		imshow("img2", img2);
//		imshow("frame", frame);
//		imshow("背景", bg_img);	
//		img1 = img2.clone();
//		img2 = frame.clone();
//		frame = video.getYCrCbFrame();
//		waitKey(1);
//	}
//	
//
//}
