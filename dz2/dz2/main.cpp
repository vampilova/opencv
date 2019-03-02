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


int main(int argc, char** argv){
   Mat image1 = imread("/Users/erzenavampilova/Desktop/study/polevoy/test3/girl.jpg");
    
    if (image1.empty()){
        cout<<"No image"<<endl;
        return -1;
    }
    
    const int histSize = 256;
    float range[] = {0,256};
    const float* histRange = {range};
    Mat histR, histG, histB;
    int height = 1200;
    int binSize=5;
    int cols=histSize*binSize;

    namedWindow("My window",1);
    int sliderValue = 50;
    createTrackbar("Contrast", "My window", &sliderValue, 100);
    
    Mat newImage;
    Mat image2;
    
    while (true) {
        double contrast = sliderValue/50.0;
        image1.convertTo(image2, -1,contrast);
        hconcat(image1, image2, newImage);
        
        vector<Mat> bgr_image;
        split(image2, bgr_image);
        
        calcHist(&bgr_image[0], 1, 0, Mat(), histB, 1, &histSize, &histRange);
        calcHist(&bgr_image[1], 1, 0, Mat(), histG, 1, &histSize, &histRange);
        calcHist(&bgr_image[2], 1, 0, Mat(), histR, 1, &histSize, &histRange);
        Mat histImage(height,cols,CV_8UC3,Scalar::all(255));
        
        for (int i=0; i<histSize; ++i) {
            line(histImage, Point(binSize*(i-1),height-cvRound(histB.at<float>(i-1))),Point(binSize*i,height-cvRound(histB.at<float>(i))), Scalar(255,0,0));
            line(histImage, Point(binSize*(i-1),height-cvRound(histG.at<float>(i-1))),Point(binSize*i,height-cvRound(histG.at<float>(i))), Scalar(0,255,0));
            line(histImage, Point(binSize*(i-1),height-cvRound(histR.at<float>(i-1))),Point(binSize*i,height-cvRound(histR.at<float>(i))), Scalar(0,0,255));
        }
        
        imshow("My window", newImage);
        imshow("Histogram", histImage);
        
        int iKey=waitKey(50);
        if (iKey==25)
            break;
    }

    return 0;
}







