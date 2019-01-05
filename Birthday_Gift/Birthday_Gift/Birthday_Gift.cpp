#include "pch.h"
#include "cv.h"
#include "highgui.h"
#include <string>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	/*
		读取图像，对图像进行平滑处理
	*/
	constexpr auto filename = "C:\\Users\\BangBang\\Pictures\\Saved Pictures\\bg_test1.jpg";

	IplImage *input = cvLoadImage(filename, CV_LOAD_IMAGE_UNCHANGED), 
				*output = cvCreateImage(cvSize(input->width, input->height), input->depth, input->nChannels);
	
	/*
		分情况处理图像
	*/
	switch (input->nChannels)
	{
		case 1:
			break;
		case 3:
		#pragma region Case_2
			//设置中间处理模板
			IplImage *h_plane = cvCreateImage(CvSize(input->width, input->height), input->depth, 1),
					 *s_plane = cvCreateImage(CvSize(input->width, input->height), input->depth, 1),
					 *v_plane = cvCreateImage(CvSize(input->width, input->height), input->depth, 1),
					 *h_tmp = cvCreateImage(CvSize(input->width, input->height), input->depth, 1),
					 *s_tmp = cvCreateImage(CvSize(input->width, input->height), input->depth, 1),
					 *tmp_hs[2] = { h_plane, s_plane },
					 *tmp_bgr = cvCreateImage(CvSize(input->width, input->height), input->depth, 3),
					 *tmp_hsv = cvCreateImage(CvSize(input->width, input->height), input->depth, 3);

			//将BGR通道转换到HSV通道
			cvCvtColor(input, tmp_hsv, CV_BGR2HSV);

			//分割获得H平面和V平面
			cvSplit(tmp_hsv, h_plane, s_plane, v_plane, NULL);

			cvEqualizeHist(h_plane, h_tmp);
			cvEqualizeHist(s_plane, s_tmp);

			cvScale(h_tmp, h_plane, 1.0, 0.5);

			cvMerge(h_tmp, s_tmp, v_plane, NULL, tmp_bgr);

			cvCvtColor(tmp_bgr, output, CV_HSV2BGR);
			////创建直方图
			//cvCreateHist(2, );

			//for (int i = 0; i < input->nChannels; i++)
			//{
			//	for (int h = 0; h < input->height; h++)
			//	{
			//		for (int w = 0; w < input->width; w++)
			//			(tmp_input->imageData + h * tmp_input->widthStep)[w] = (output->imageData + h * input->widthStep)[w * output->nChannels + i];
			//	}

			//	cvSmooth(tmp_input, tmp_output, CV_GAUSSIAN, 3, 3);

			//	cvEqualizeHist(tmp_output, tmp_input);

			//	for (int h = 0; h < input->height; h++)
			//		for (int w = 0; w < input->width; w++)
			//			(output->imageData + h * output->widthStep)[w * output->nChannels + i] = (tmp_input->imageData + h * tmp_input->widthStep)[w];
			//}
			break;
		#pragma endregion

	}



	/*
		输出图像，查看效果
	*/
	cvNamedWindow("input");
	cvNamedWindow("output");
	cvShowImage("input", input);
	cvShowImage("output", output);

	cvWaitKey();

	cvReleaseImage(&input);
	cvReleaseImage(&output);
	cvDestroyWindow("input");
	cvDestroyWindow("output");
}
