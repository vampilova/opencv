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

int main()
{
    Mat image = imread("/Users/erzenavampilova/opencv/dz1/dress.jpg");
    Mat image2;
    
    if(image.empty())
    {
        cout<<"There is no any picture"<<endl;
        cin.get();
        return -1;
    }
    
    String normalImage = "Normal image";
    String grayImage = "Gray image";
    String histImage = "Grayscale histogram";
    
    namedWindow(normalImage);
    namedWindow(grayImage);
    namedWindow(histImage);
    
    cvtColor(image, image2, COLOR_BGR2GRAY);
    
    int histogram_intens[256];
    for (int i=0; i<256;++i)
        histogram_intens[i]=0;
    
    for (int y=0; y<image2.rows;++y)
        for (int x=0; x<image2.cols; ++x)
            histogram_intens[(int)image2.at<uchar>(y,x)]++;
    
    for (int i=0; i<256; ++i)
        cout<<histogram_intens[i]<<" ";
    
    int hist_w = 500, hist_h = 400;
    int bin_w = cvRound((double)hist_w/256);
    
    Mat hist_image(hist_h,hist_w,CV_8UC1, Scalar(255,255,255));
    
    int max = histogram_intens[0];
    for (int i=0; i<256; ++i){
        if (max<histogram_intens[i])
            max = histogram_intens[i];
    }
    
    for (int i=0;i<256;++i)
        histogram_intens[i]=((double)histogram_intens[i]/max)*hist_image.rows;
    
    for (int i=0; i<256; ++i){
        line(hist_image, Point(bin_w*i, hist_h), Point(bin_w*i, hist_h-histogram_intens[i]), Scalar(0,0,0),1,8,0);
    }
    
    imshow(normalImage, image);
    imshow(grayImage, image2);
    imshow(histImage, hist_image);
    
    waitKey(0);
    destroyAllWindows();
    return 0;
}




