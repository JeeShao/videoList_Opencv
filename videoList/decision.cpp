#include"decision.h"

Decision::Decision(Mat frame0)
{
	img1 = NULL;
	img2 = NULL;
	frame = frame0;
	bgImg = Mat::zeros(frame.rows, frame.cols, frame.type());
	cbMean = 0;

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
Mat Decision::toBgrImg()
{
	//Mat img_bg = Mat::zeros(frame.rows, frame.cols, frame.type());//rows=480 cols=640															  //cout << frame.rows<<" "<<frame.cols;
	for (int nrows = 0; nrows<frame.rows; nrows++)
		for (int ncols = 0; ncols < frame.cols; ncols++)
		{
			for (int channle = 0; channle < 3; channle++)
			{
				//���㱳��
				bgImg.at<Vec3b>(nrows, ncols)[channle] = (uchar)round((4 * (int)frame.at<Vec3b>(nrows, ncols)[channle]
					+ 3 * (int)img2.at<Vec3b>(nrows, ncols)[channle] + (int)img1.at<Vec3b>(nrows, ncols)[channle]) / 8);
			}
			cbMean += bgImg.at<Vec3b>(nrows, ncols)[1];
		}
	cbMean = cbMean / (bgImg.rows*bgImg.rows);
	return bgImg;
}

//�ж��㷨 returnһ��ͼ��Ļ𻨵���
int Decision::decision()
{
	int count = 0;//��֡��
	for (int nrows = 0; nrows<frame.rows; nrows++)
		for (int ncols = 0; ncols < frame.cols; ncols++)
		{
			//Y>Cr
			if (frame.at<Vec3b>(nrows, ncols)[0]>frame.at<Vec3b>(nrows, ncols)[2])
				//Cr>Cb
				if (frame.at<Vec3b>(nrows, ncols)[1]>frame.at<Vec3b>(nrows, ncols)[2])
					//Y-����>Y��ֵ  �˴���ֵ����Ϊ0
					if (frame.at<Vec3b>(nrows, ncols)[0] - bgImg.at<Vec3b>(nrows, ncols)[0] > 0)
						//Cr-����>Cr��ֵ �˴���ֵ����Ϊ0
						if (frame.at<Vec3b>(nrows, ncols)[1] - bgImg.at<Vec3b>(nrows, ncols)[1] > 0)
							//Cb<Cbmean  CbmeanΪ����ͼ���Cb��ֵ
							if (frame.at<Vec3b>(nrows, ncols)[1] < cbMean)
								count++;

		}
	return count;
}