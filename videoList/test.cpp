//#include<iostream>
//#include<opencv2/opencv.hpp>
//#include<ctime>
//using namespace std;
//using namespace cv;
//
//void main() {
//	VideoCapture cap(0);
//
//	string path = "./pic";
//	int count = 1;
//	while(!cap.isOpened());
//		cout << "����ͷδ��" << endl;;
//	Mat img1,img2,frame;
//	cap.read(img1);			   //Ԥ������
//	cap.read(img2);
//	flip(img1, img1, 1);
//	flip(img2, img2, 1);
//	cvtColor(img1, img1, CV_BGR2YCrCb);
//	cvtColor(img2, img2, CV_BGR2YCrCb);
//
//	int YCb_num = 0,
//		CrCb_num = 0,
//		YBg_YThre = 0,
//		CrBg_CrThre = 0,
//		Cb_CbMean = 0,//�����ж��㷨�������ʽ�����ص����
//		CbBg_total = 0;
//
//	clock_t start, finish;
//
//	while (1)
//	{
//		YCb_num = 0;
//		CrCb_num = 0;
//		YBg_YThre = 0;
//		CrBg_CrThre = 0;
//		Cb_CbMean = 0;//�����ж��㷨�������ʽ�����ص����
//		CbBg_total = 0;
//
//		
//
//		cap >> frame;
//		if (frame.empty())
//			break;
//		flip(frame, frame, 1);
//		cvtColor(frame, frame, CV_BGR2YCrCb);
//
//		start = clock();
//
//		Mat img_bg = Mat::zeros(frame.rows, frame.cols, frame.type());//rows=480 cols=640
//		//cout << frame.rows<<" "<<frame.cols;
//		for (int nrows = 0; nrows<frame.rows; nrows++)
//			for (int ncols = 0; ncols < frame.cols; ncols++)
//			{
//				for (int channle = 0; channle < 3; channle++)
//				{
//					//���㱳��
//					img_bg.at<Vec3b>(nrows, ncols)[channle] = (uchar)round((4 * (int)frame.at<Vec3b>(nrows, ncols)[channle]
//						+ 3 * (int)img2.at<Vec3b>(nrows, ncols)[channle] + (int)img1.at<Vec3b>(nrows, ncols)[channle]) / 8);
//
//				}
//				//Y>Cb ==> Լһ�����ص�����
//				if ((int)frame.at<Vec3b>(nrows, ncols)[0] >(int)frame.at<Vec3b>(nrows, ncols)[2])
//					YCb_num++;
//
//				//Cr>Cb
//				if ((int)frame.at<Vec3b>(nrows, ncols)[1] > (int)frame.at<Vec3b>(nrows, ncols)[2])
//					CrCb_num++;
//					//Y-����>Y��ֵ	��ֵ��ʱ�޷�ȷ�� �˴�	��ֵ��ʱ��Ϊ0
//				if ((int)(frame.at<Vec3b>(nrows, ncols)[0]) - (int)(img_bg.at<Vec3b>(nrows, ncols)[0])>0)
//					YBg_YThre++;
//
//					//cout<< (int)frame.at<Vec3b>(nrows, ncols)[0]<<"  "<<(int)img_bg.at<Vec3b>(nrows, ncols)[0]<<"  "<<"Y-������" << YBg_YThre << endl;
//				/*	int Y = (int)frame.at<Vec3b>(nrows, ncols)[0];
//					int Ybg = (int)img_bg.at<Vec3b>(nrows, ncols)[0];*/
//
//					//Cr-����>Cr��ֵ	��ֵ��ʱ�޷�ȷ�� �˴�	��ֵ��ʱ��Ϊ0
//				if ((int)(frame.at<Vec3b>(nrows, ncols)[1]) - (int)(img_bg.at<Vec3b>(nrows, ncols)[1]) > 0)
//					CrBg_CrThre++;		 
//				//cout<< (int)frame.at<Vec3b>(nrows, ncols)[1]<<"  "<<(int)img_bg.at<Vec3b>(nrows, ncols)[1]<<"  "<<"Cr-������" << CrBg_CrThre << endl;
//
//				//Cb<Cbmean  CbmeanΪ����ͼ���Cb��ֵ  �˴�ֻ���㱳��Cb��ֵ
//				CbBg_total += (int)(frame.at<Vec3b>(nrows, ncols)[2]);
//			}
//		finish = clock();
//
//		imwrite(path + format("/%d.jpg", count++), frame);
//		imshow("img1", img1);
//		imshow("img2", img2);
//		imshow("frame", frame);
//		imshow("img_bg", img_bg);
//
//		img1 = img2.clone();
//		img2 = frame.clone();
//		waitKey(1);
//		cout <<"pic"<<count-1<<"  Y>Cb: "<< YCb_num<<"  Cr>Cb: "<< CrCb_num <<"  Y-����>Y��ֵ��0����"<<YBg_YThre<<"   Cr-����>Cr��ֵ��0��: "<< CrBg_CrThre<<"   ����Cb��ֵ: "<<CbBg_total/(frame.rows*frame.cols)<< "  ��ʱ��"<<finish - start << "ms\n"<<endl;
//	}
//	cap.release();
//}