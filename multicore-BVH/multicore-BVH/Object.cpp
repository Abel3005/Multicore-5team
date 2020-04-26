#include "Object.h"
#include "defaultParameter.h"
using namespace cv;
Object::Object(Point a, Point b, Point c) {
	points[0] = a;
	points[1] = b;
	points[2] = c;
	middlePoint = { 0,0 };
}
Object::Object() {
	points[0].x = rand() % Maxlength;
	points[0].y = rand() % MaxHeight ;
	points[1].x = rand() % Maxlength;
	points[1].y = rand() % MaxHeight;
	points[2].x = rand() % Maxlength;
	points[2].y = rand() % MaxHeight;
	middlePoint = { 0, 0};
}
Object::~Object() {}
void Object::calMidPoint(){
	middlePoint.x = (points[0].x + points[1].x + points[2].x) / 3;
	middlePoint.y = (points[0].y + points[1].y + points[2].y) / 3;
}
void Object::drawObject(cv::InputOutputArray img) {
	int npts = 3;
	scalarValue = 100+ (rand() % 156);
	const Point* pts = (const cv::Point*) points;
	fillPoly(img, &pts, &npts, 1,  Scalar(scalarValue, scalarValue, scalarValue));
}


