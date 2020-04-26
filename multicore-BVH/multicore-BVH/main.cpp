#include <iostream>
#include <opencv2/opencv.hpp>
#include "Object.h"
#include "defaultParameter.h"
#include "ObjectReader.h"
#include "Box.h"

using namespace std;
using namespace cv;
int main()
{
	/*ObjectReader objectReader;
	objectReader.readTxt("input.txt");

	Object* objectList = objectReader.objectList;
	int num = objectReader.num;*/
	Object objectList[100];

	cv::Mat bgImage = cv::Mat::zeros(Maxlength, MaxHeight,CV_8UC1);
	Mat img(Maxlength, MaxHeight, CV_8UC3);
	img.setTo(0);
	int npts = 3;

	for (int i = 0; i < ObjectNums; i++) {
		objectList[i].drawObject(img);
	}
	Box box(objectList, ObjectNums);
	box.calBox();
	box.drawBox(img);

	
	imshow("result", img);
	waitKey();
	return 0;
}