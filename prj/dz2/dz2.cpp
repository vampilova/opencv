
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
	Mat image1 = imread("girl.jpg");
	Mat image2;

	if (image1.empty())
	{
		cout << "No image" << endl;
		return -1;
	}

	int histSize = 256;
	float range[] = { 0, 256 };
	const float* histRange = { range };
	bool uniform = true; bool accumulate = false;
	Mat b_hist, g_hist, r_hist;

	namedWindow("My window", 1);
	namedWindow("Histogram", 1);
	int sliderValue = 50;
	createTrackbar("Contrast", "My window", &sliderValue, 100);

	Mat newImage;

	while (true)
	{
		double contrast = sliderValue / 50.0;
		image1.convertTo(image2, -1, contrast);
		hconcat(image1, image2, newImage);

		vector<Mat> bgr_image;
		split(image2, bgr_image);

		calcHist(&bgr_image[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);
		calcHist(&bgr_image[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
		calcHist(&bgr_image[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);
		int hist_w = 512; int hist_h = 400;
		int bin_w = cvRound((double)hist_w / histSize);

		Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
		normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
		normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
		normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
		for (int i = 1; i < histSize; i++)
		{
			line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
				Point(bin_w*(i), hist_h - cvRound(b_hist.at<float>(i))),
				Scalar(255, 0, 0), 2, 8, 0);
			line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
				Point(bin_w*(i), hist_h - cvRound(g_hist.at<float>(i))),
				Scalar(0, 255, 0), 2, 8, 0);
			line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
				Point(bin_w*(i), hist_h - cvRound(r_hist.at<float>(i))),
				Scalar(0, 0, 255), 2, 8, 0);
		}

		imshow("My window", newImage);
		imshow("Histogram", histImage);

		int iKey = waitKey(50);
		if (iKey == 27)
			break;
	}

	return 0;
}