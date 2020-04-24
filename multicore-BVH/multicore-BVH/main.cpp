#include <iostream>
#include <opencv2/opencv.hpp>
#include "Object.h"
#include "defaultParameter.h"

using namespace std;
using namespace cv;
int main()
{
	Object objectList[100];
	cv::Mat bgImage = cv::Mat::zeros(Maxlength, MaxHeight,CV_8UC1);
	Mat img(Maxlength, MaxHeight, CV_8UC1);
	img.setTo(0);
	int npts = 3;

	for (int i = 0; i < 100; i++) {
		const Point* pts = (const cv::Point*) (objectList[i].points);
		polylines(img, &pts, &npts, 1, true, Scalar(255, 255, 255));
	}
	
	
	imshow("result", img);
	waitKey();
	return 0;
}