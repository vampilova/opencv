//
//  main.cpp
//  test2
//
//  Created by Эржена Вампилова on 18/02/2019.
//  Copyright © 2019 Эржена Вампилова. All rights reserved.
//

#include <opencv2/opencv.hpp>

#include <iostream>
#include <string>

using namespace cv;
using namespace std;


int main() {
	Mat img(400, 400, CV_8UC1);
	Mat res;
	Mat res2;
	int colorCircle = 0;
	int colorRect = 255;
	int k = 0;
	int z = 0;

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			rectangle(img, Point(k, z), Point(k + img.rows / 3, z + img.rows / 2), Scalar(colorRect), FILLED);
			k += img.rows / 3;
			colorRect -= 255 / 12;    //0,128,255 (цвет белый, синий,
		}
		z += img.rows / 2;
		k = 0;
	}
	for (int j = 0; j < img.rows; j++) {
		for (int i = 0; i < img.cols; i++) {
			if ((j == img.rows / 6 || j == img.rows / 2 || j == img.rows / 6 * 5) && (i == img.rows / 4 || i == img.rows / 4 * 3)) {
				circle(img, Point(j, i), img.rows / 7, Scalar(colorCircle), FILLED);
				colorCircle += 255 / 6;
			}
		}
	}

	imshow("res", img);

	const float kernelData[] = {
		1.0f, 0,
		0, -1.0f };
	const Mat kernel(2, 2, CV_32FC1, (float *)kernelData);
	filter2D(img, res, -1, kernel);

	imshow("after filter", res);

	const float kernelData2[] = {
		0, 1.0f,
		-1.0f, 0 };
	const Mat kernel2(2, 2, CV_32FC1, (float *)kernelData2);
	filter2D(img, res2, -1, kernel2);

	imshow("after filter2", res2);

	waitKey();
	destroyAllWindows();
	return 0;
}




