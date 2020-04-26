#include <iostream>
#include <opencv2/opencv.hpp>
#include "Object.h"
#include "defaultParameter.h"
#include "ObjectReader.h"
#include "Box.h"
#include "DS_timer.h"
#include "DS_definitions.h"
#include "Tree.h"

using namespace std;
using namespace cv;
TreeNode* serial_execute(Object* List, int objectNum, int depth, InputOutputArray img);
void version1_execute(int depth);
void version2_execute(int depth);
int main()
{
	/*ObjectReader objectReader;
	objectReader.readTxt("input.txt");

	Object* objectList = objectReader.objectList;
	*/int num = ObjectNums;
	Object objectList[100];
	DS_timer timer(2);
	timer.setTimerName(0, (char*)"Serial");
	timer.setTimerName(1, (char*)"Parallel");

	cv::Mat bgImage = cv::Mat::zeros(Maxlength, MaxHeight,CV_8UC1);
	Mat img(Maxlength, MaxHeight, CV_8UC3);
	img.setTo(0);
	int npts = 3;

	for (int i = 0; i < ObjectNums; i++) {
		objectList[i].drawObject(img);
	}
	Tree tree(serial_execute(objectList, ObjectNums, 3, img));
	/*Box box(objectList, num);
	box.serial_calBox();
	box.drawBox(img);*/

	
	imshow("result", img);
	waitKey();
	return 0;
}
TreeNode* serial_execute(Object* List, int objectNum, int depth, cv::InputOutputArray img)
{
	if (depth == 0 && objectNum <= 1)
	{
		return nullptr;
	}
	Box box(List, objectNum);
	box.serial_calBox();
	box.drawBox(img);
	TreeNode* node = new TreeNode(box);
	Object* lList = new Object[objectNum];
	Object* RList = new Object[objectNum];
	int lnums = 0;
	int rnums = 0;
	for (int i =0; i < objectNum; i++)
	{
		if (box.middlePoint.x < List[i].middlePoint.x)
		{
			RList[rnums] = List[i];
			rnums++;
		}
		else
		{
			lList[lnums] = List[i];
			lnums++;
		}
	}
	node->left = serial_execute(lList, lnums, depth - 1, img);
	node->right = serial_execute(RList, rnums, depth - 1, img);
	return node;

}