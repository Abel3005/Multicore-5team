#pragma once
#include <opencv2/opencv.hpp>
class Object
{
private:
	
	
public:
	cv::Point points[3];
	cv::Point middlePoint;
	int scalarValue;

	Object(cv::Point a, cv::Point b, cv::Point c);
	Object();
	~Object();

	void calMidPoint();
	void drawObject(cv::InputOutputArray img);
};

