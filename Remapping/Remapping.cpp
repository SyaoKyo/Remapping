#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
using namespace cv;

// ȫ�ֱ���
Mat src, dst;
Mat map_x, map_y;
char* remap_window = "Remap demo";
int ind = 0;

void update_map()
{
	ind = ind % 4;
	for (int j = 0; j < src.rows; j++)
	{
		for (int i = 0; i < src.cols; i++)
		{
			switch (ind)
			{
			case 0:
				map_x.at<float>(j, i) = i;
				map_y.at<float>(j, i) = j;
				break;
			case 1:
				map_x.at<float>(j, i) = i;
				map_y.at<float>(j, i) = src.rows - j;
				break;
			case 2:
				map_x.at<float>(j, i) = src.cols - i;
				map_y.at<float>(j, i) = j;
				break;
			case 3:
				map_x.at<float>(j, i) = src.cols - i;
				map_y.at<float>(j, i) = src.rows - j;
				break;
			}
		}
	}
	ind++;
}


int main()
{
	// ����ͼƬ
	src = imread("cat.jpg");

	// ����Ŀ��ͼ�������ӳ�����( x �� y )
	dst.create(src.size(), src.type());
	map_x.create(src.size(), CV_32FC1);
	map_y.create(src.size(), CV_32FC1);

	// ��������
	namedWindow(remap_window, CV_WINDOW_AUTOSIZE);

	// ѭ��
	while (true)
	{
		// ��ESC���˳�ѭ��
		int c = waitKey(1000);

		if ((char)c == 27)
		{
			break;
		}

		update_map();
		remap(src, dst, map_x, map_y, CV_INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0));

		// ��ʾ���
		imshow(remap_window, dst);
	}
	return 0;
}

