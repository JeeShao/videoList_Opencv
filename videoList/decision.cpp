#include"decision.h"
//#include<vld.h>  //����ڴ�й©



int Decision::rowNumber = 120;                           //��ȡͼ���������
int Decision::colNumber = 640 * 3;    //��ͨ��ͼ��ÿ��Ԫ�ظ���Ϊ����*ͨ����
										  //cout <<"rownumber"<< rowNumber << endl;

Decision::Decision()
{
	img1 = NULL;
	img2 = NULL;
	frame = NULL;
	bgImg = Mat::zeros(480,640,16);
	//Mat bg1 = Mat::zeros(120, 640, 16);
	//Mat bg2 = Mat::zeros(120, 640, 16);
	//Mat bg3 = Mat::zeros(120, 640, 16);
	//Mat bg4 = Mat::zeros(120, 640, 16);

	cbMean = 0;
	cbMean1 = 0;
	cbMean2 = 0;
	cbMean3 = 0;
	cbMean4 = 0;


}

Decision::~Decision()
{

}

 //��ʼ����ʼ����ͼƬ
void Decision::set2img(Mat pic1, Mat pic2)
{
	img1 = pic1.clone();
	img2 = pic2.clone();

}

//������������ͷ����ͼ��
void Decision::setFrame(Mat img)
{
	frame = img.clone();
}

//���ɱ���ͼ��

//Mat Decision::toBgrImg0()
//{
//	////Mat img_bg = Mat::zeros(frame.rows, frame.cols, frame.type());//rows=480 cols=640															  //cout << frame.rows<<" "<<frame.cols;
//	//for (int nrows = 0; nrows<frame.rows; nrows++)
//	//	for (int ncols = 0; ncols < frame.cols; ncols++)
//	//	{
//	//		for (int channle = 0; channle < 3; channle++)
//	//		{
//	//			//���㱳��
//	//			bgImg.at<Vec3b>(nrows, ncols)[channle] = (uchar)round((4 * (int)frame.at<Vec3b>(nrows, ncols)[channle]
//	//				+ 3 * (int)img2.at<Vec3b>(nrows, ncols)[channle] + (int)img1.at<Vec3b>(nrows, ncols)[channle]) / 8);
//	//		}
//	//		cbMean += bgImg.at<Vec3b>(nrows, ncols)[1];
//	//	}
//	//cbMean = cbMean / (bgImg.rows*bgImg.rows);
//	//return bgImg;
//		cbMean = 0;
//		int rowNumber = frame.rows;                           //��ȡͼ���������
//		int colNumber = frame.cols*frame.channels();    //��ͨ��ͼ��ÿ��Ԫ�ظ���Ϊ����*ͨ����
//
//		for (int i = 0; i < rowNumber; i++)
//		{
//			uchar* pixelPtr = frame.ptr<uchar>(i);            //��ȡ����ÿ���׵�ַָ��
//			for (int j = 0; j < colNumber; j++)
//			{
//				bgImg.ptr<uchar>(i)[j] = round((4 * pixelPtr[j] + 3 * img2.ptr<uchar>(i)[j] + img1.ptr<uchar>(i)[j]) / 8);
//				if (j % 3 == 1)
//					cbMean += bgImg.at<Vec3b>(i, j/3)[1];
//			}
//				
//
//		}
//		cbMean = cbMean / (bgImg.rows*bgImg.cols);
//		return bgImg;
//	
//}


void Decision::blockImg1(int rowNumber,int colNumber)
{
	for (int i = 0; i < rowNumber; i++)		//rowNumber=120
	{
		uchar* pixelPtr = frame.ptr<uchar>(i);            //��ȡ����ÿ���׵�ַָ��
		for (int j = 0; j < colNumber; j++)
		{
			bgImg.ptr<uchar>(i)[j] = uchar(round((4 * pixelPtr[j] + 3 * img2.ptr<uchar>(i)[j] + img1.ptr<uchar>(i)[j]) >>3 ));
			if (j % 3 == 2)
				cbMean1 += bgImg.ptr<uchar>(i)[j];

		}
		//delete pixelPtr;
	}
	cbMean1 = cbMean1 / (rowNumber * bgImg.cols);
}

void Decision::blockImg2(int rowNumber, int colNumber)
{
	for (int i = rowNumber; i <2*rowNumber; i++)
	{
		uchar* pixelPtr = frame.ptr<uchar>(i);            //��ȡ����ÿ���׵�ַָ��
		for (int j = 0; j < colNumber; j++)
		{
			bgImg.ptr<uchar>(i)[j] = uchar(round((4 * pixelPtr[j] + 3 * img2.ptr<uchar>(i)[j] + img1.ptr<uchar>(i)[j]) >> 3));
			if (j % 3 == 2)
				cbMean2 += bgImg.ptr<uchar>(i)[j];
		}
	}
	cbMean2 = cbMean2 / (rowNumber * bgImg.cols);
}

void Decision::blockImg3(int rowNumber, int colNumber)
{
	for (int i = 2* rowNumber; i < 3*rowNumber; i++)
	{
		uchar* pixelPtr = frame.ptr<uchar>(i);            //��ȡ����ÿ���׵�ַָ��
		for (int j = 0; j < colNumber; j++)
		{
			bgImg.ptr<uchar>(i)[j] = uchar(round((4 * pixelPtr[j] + 3 * img2.ptr<uchar>(i)[j] + img1.ptr<uchar>(i)[j]) >> 3));
			if (j % 3 == 2)
				//cbMean3 += bgImg.at<Vec3b>(i, j / 3)[2];
				cbMean3 += bgImg.ptr<uchar>(i)[j];
		}
	}
	cbMean3 = cbMean3 / (rowNumber * bgImg.cols);
}

void Decision::blockImg4(int rowNumber, int colNumber)
{
	for (int i = 3 * rowNumber; i <frame.rows; i++)
	{
		uchar* pixelPtr = frame.ptr<uchar>(i);            //��ȡ����ÿ���׵�ַָ��
		for (int j = 0; j < colNumber; j++)
		{
			bgImg.ptr<uchar>(i)[j] = uchar(round((4 * pixelPtr[j] + 3 * img2.ptr<uchar>(i)[j] + img1.ptr<uchar>(i)[j]) >> 3));
			if (j % 3 == 2)
				//cbMean4 += bgImg.at<Vec3b>(i, j / 3)[2];
				cbMean4 += bgImg.ptr<uchar>(i)[j];
		}
	}
	cbMean4 = cbMean4 / (rowNumber * frame.cols);
}

Mat Decision::toBgrImg()
{
	cbMean = 0;
	cbMean1 = 0;
	cbMean2 = 0;
	cbMean3 = 0;
	cbMean4 = 0;
	thread thread1(&Decision::blockImg1, this, rowNumber, colNumber);			
	thread thread2(&Decision::blockImg2, this, rowNumber, colNumber);
	thread thread3(&Decision::blockImg3, this, rowNumber, colNumber);
	thread thread4(&Decision::blockImg4, this, rowNumber, colNumber);
	thread1.join();
	thread2.join();
	thread3.join();
	thread4.join();
	cbMean = round((cbMean1 + cbMean2 + cbMean3 + cbMean4) >>2 );
	cout << "cbmean: " << cbMean1 << "  " << cbMean2 << "  " << cbMean3 << "  " << cbMean4 << "  Cb��ֵ��" << cbMean << "  ";
	return bgImg;
}

//�ж��㷨 returnһ��ͼ��Ļ𻨵���
int Decision::decision()
{
	int count = 0;//��֡��
	for (int i = 0; i <frame.rows; i++)
	{
		uchar* pixelPtr = frame.ptr<uchar>(i);            //��ȡ����ÿ���׵�ַָ��
		for (int j = 0; j < colNumber; j+=3)
		{
			if (frame.ptr<uchar>(i)[j] > frame.ptr<uchar>(i)[j + 2])
				if (frame.ptr<uchar>(i)[j + 1] > frame.ptr<uchar>(i)[j + 2])
					if (frame.ptr<uchar>(i)[j] - bgImg.ptr<uchar>(i)[j] > 0)
						if (frame.ptr<uchar>(i)[j + 1] - bgImg.ptr<uchar>(i)[j + 1] > 0)
							if (frame.ptr<uchar>(i)[j + 2] < cbMean)
								count++;	
		}
	}
	//for (int nrows = 0; nrows<frame.rows; nrows++)
	//	for (int ncols = 0; ncols < frame.cols; ncols++)
	//	{
	//		//Y>Cb
	//		if (frame.at<Vec3b>(nrows, ncols)[0]>frame.at<Vec3b>(nrows, ncols)[2])
	//			//Cr>Cb
	//			if (frame.at<Vec3b>(nrows, ncols)[1]>frame.at<Vec3b>(nrows, ncols)[2])
	//				//Y-����>Y��ֵ  �˴���ֵ����Ϊ0
	//				if (frame.at<Vec3b>(nrows, ncols)[0] - bgImg.at<Vec3b>(nrows, ncols)[0] > 0)
	//					//Cr-����>Cr��ֵ �˴���ֵ����Ϊ0
	//					if (frame.at<Vec3b>(nrows, ncols)[1] - bgImg.at<Vec3b>(nrows, ncols)[1] > 0)
	//						//Cb<Cbmean  CbmeanΪ����ͼ���Cb��ֵ
	//						if (frame.at<Vec3b>(nrows, ncols)[1] < cbMean)
	//							count++;
	//	}
	return count;
}