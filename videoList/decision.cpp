#include"decision.h"
//#include<vld.h>  //检测内存泄漏



int Decision::rowNumber = 120;                           //获取图像矩阵行数
int Decision::colNumber = 640 * 3;    //三通道图像每行元素个数为列数*通道数
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

 //初始化开始两张图片
void Decision::set2img(Mat pic1, Mat pic2)
{
	img1 = pic1.clone();
	img2 = pic2.clone();

}

//更新设置摄像头最新图像
void Decision::setFrame(Mat img)
{
	frame = img.clone();
}

//生成背景图像

//Mat Decision::toBgrImg0()
//{
//	////Mat img_bg = Mat::zeros(frame.rows, frame.cols, frame.type());//rows=480 cols=640															  //cout << frame.rows<<" "<<frame.cols;
//	//for (int nrows = 0; nrows<frame.rows; nrows++)
//	//	for (int ncols = 0; ncols < frame.cols; ncols++)
//	//	{
//	//		for (int channle = 0; channle < 3; channle++)
//	//		{
//	//			//计算背景
//	//			bgImg.at<Vec3b>(nrows, ncols)[channle] = (uchar)round((4 * (int)frame.at<Vec3b>(nrows, ncols)[channle]
//	//				+ 3 * (int)img2.at<Vec3b>(nrows, ncols)[channle] + (int)img1.at<Vec3b>(nrows, ncols)[channle]) / 8);
//	//		}
//	//		cbMean += bgImg.at<Vec3b>(nrows, ncols)[1];
//	//	}
//	//cbMean = cbMean / (bgImg.rows*bgImg.rows);
//	//return bgImg;
//		cbMean = 0;
//		int rowNumber = frame.rows;                           //获取图像矩阵行数
//		int colNumber = frame.cols*frame.channels();    //三通道图像每行元素个数为列数*通道数
//
//		for (int i = 0; i < rowNumber; i++)
//		{
//			uchar* pixelPtr = frame.ptr<uchar>(i);            //获取矩阵每行首地址指针
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
		uchar* pixelPtr = frame.ptr<uchar>(i);            //获取矩阵每行首地址指针
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
		uchar* pixelPtr = frame.ptr<uchar>(i);            //获取矩阵每行首地址指针
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
		uchar* pixelPtr = frame.ptr<uchar>(i);            //获取矩阵每行首地址指针
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
		uchar* pixelPtr = frame.ptr<uchar>(i);            //获取矩阵每行首地址指针
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
	cout << "cbmean: " << cbMean1 << "  " << cbMean2 << "  " << cbMean3 << "  " << cbMean4 << "  Cb均值：" << cbMean << "  ";
	return bgImg;
}

//判定算法 return一张图象的火花点数
int Decision::decision()
{
	int count = 0;//火花帧数
	for (int i = 0; i <frame.rows; i++)
	{
		uchar* pixelPtr = frame.ptr<uchar>(i);            //获取矩阵每行首地址指针
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
	//				//Y-背景>Y阈值  此处阈值暂设为0
	//				if (frame.at<Vec3b>(nrows, ncols)[0] - bgImg.at<Vec3b>(nrows, ncols)[0] > 0)
	//					//Cr-背景>Cr阈值 此处阈值暂设为0
	//					if (frame.at<Vec3b>(nrows, ncols)[1] - bgImg.at<Vec3b>(nrows, ncols)[1] > 0)
	//						//Cb<Cbmean  Cbmean为背景图像的Cb均值
	//						if (frame.at<Vec3b>(nrows, ncols)[1] < cbMean)
	//							count++;
	//	}
	return count;
}