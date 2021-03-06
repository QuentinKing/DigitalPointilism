#include "stdafx.h"

#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
using namespace cv;

string GetNewImagePath(const string orgFilePath)
{
	vector<string> result;
	stringstream ss(orgFilePath);
	string item;
	while (getline(ss, item, '.'))
	{
		result.push_back(item);
	}
	return result[0] + "_dp.jpg";
}

int main()
{
	string filePath;
	bool promptForInput = true;
	Mat img;

	while (promptForInput)
	{
		cout << "Please enter file path to image...\n";
		cin >> filePath;

		if (filePath == "exit")
			return 0;

		img = imread(filePath);

		if (img.data == NULL || img.channels() != 3)
		{
			cout << "Not a colour image! Or the file type is not supported";
		}
		else
		{
			promptForInput = false;
		}
	}


	Mat newImage(img.rows, img.cols, img.type());
	for (int y = 0; y < img.rows; y++)
	{
		for (int x = 0; x < img.cols; x++)
		{
			Vec3b color = img.at<Vec3b>(Point(x - (x % 8), y - (y % 8)));

			if ((x % 8 >= 2 && x % 8 <= 5) && (y % 8 >= 1 && y % 8 <= 4))
			{
				newImage.at<Vec3b>(Point(x, y)) = Vec3b(0, 0, color[2]);
			}
			else if ((x % 8 >= 0 && x % 8 <= 3) && (y % 8 >= 4 && y % 8 <= 7))
			{
				newImage.at<Vec3b>(Point(x, y)) = Vec3b(0, color[1], 0);
			}
			else if ((x % 8 >= 4 && x % 8 <= 7) && (y % 8 >= 4 && y % 8 <= 7))
			{
				newImage.at<Vec3b>(Point(x, y)) = Vec3b(color[0], 0, 0);
			}
			else
			{
				newImage.at<Vec3b>(Point(x, y)) = Vec3b(0, 0, 0);
			}
		}
	}

	namedWindow("result", WINDOW_KEEPRATIO);
	imshow("result", newImage);
	imwrite(GetNewImagePath(filePath), newImage);
	waitKey(0);

	return 0;
}

