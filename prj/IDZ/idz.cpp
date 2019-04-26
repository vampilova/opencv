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

// Alpha blending using multiply and add functions
Mat& blend(Mat& alpha, Mat& foreground, Mat& background, Mat& outImage)
{
    Mat fore, back;
    GaussianBlur(alpha, alpha, Size(5,5), 0);
    imshow("Mask after GaussianBlur", alpha);
    multiply(alpha, foreground, fore);
    
    //imshow("after 1", fore);
    multiply(Scalar::all(1.0)-alpha, background, back);
   // imshow("after 2", back);

    //convert to HSV
    Mat hsv1;
    cvtColor(fore, hsv1, COLOR_BGR2HSV);
    Mat hsv2;
    cvtColor(back, hsv2, COLOR_BGR2HSV);
    Scalar v1 = sum(hsv1) / (hsv1.rows * hsv1.cols);
    Scalar v2 = sum(hsv2) / (hsv2.rows * hsv2.cols);
    
    Mat fore2;
    vector<Mat> V;
    split(hsv1,V);
    V[0]=V[0]*(v1[0] + v2[0]) / (2 * v1[0]);
    V[1]=V[1]*(v1[1] + v2[1]) / (2 * v1[1]);
    V[2]=V[2]*(v1[2] + v2[2]) / (2 * v1[2]);
    merge(V,hsv1);
    cvtColor(hsv1, fore2, COLOR_HSV2BGR);
    imshow("Object", fore/255);
    
    add(fore2, back, outImage);
    outImage = outImage/255;
    
    return outImage;
}

int main(int argc, char** argv)
{
    // Read in the png foreground asset file that contains both rgb and alpha information
    Mat foreGroundImage = imread("fore3.png", -1);
    Mat bgra[4];
    split(foreGroundImage, bgra);//split png foreground
    
    // Save the foregroung RGB content into a single Mat
    vector<Mat> foregroundChannels;
    foregroundChannels.push_back(bgra[0]);
    foregroundChannels.push_back(bgra[1]);
    foregroundChannels.push_back(bgra[2]);
    Mat foreground = Mat::zeros(foreGroundImage.size(), CV_8UC3);
    merge(foregroundChannels, foreground);
    
    // Save the alpha information into a single Mat
    vector<Mat> alphaChannels;
    alphaChannels.push_back(bgra[3]);
    alphaChannels.push_back(bgra[3]);
    alphaChannels.push_back(bgra[3]);
    Mat alpha = Mat::zeros(foreGroundImage.size(), CV_8UC3);
    merge(alphaChannels, alpha);
    
    // Convert Mat to float data type
    foreground.convertTo(foreground, CV_32FC3);
    alpha.convertTo(alpha, CV_32FC3,1.0/255); // keeps the alpha values betwen 0 and 1
    imshow("Original mask", alpha);
    
    // Read background image4
    cout << "Укажите количество фонов (от 1 до 4)" << endl;
    int n;
    cin >> n;
    if (n==1){
        Mat background1 = imread("back2.jpg");
        resize(background1, background1,foreGroundImage.size());
        background1.convertTo(background1, CV_32FC3);
        
        // Alpha blending using functions multiply and add
        Mat outImage1= Mat::zeros(foreground.size(), foreground.type());
        outImage1 = blend(alpha, foreground, background1, outImage1);
        imshow("1", outImage1);
        waitKey(0);
    }
    else if (n==2){
        Mat background1 = imread("back2.jpg");
        Mat background2 = imread("back3.jpg");
        resize(background1, background1,foreGroundImage.size());
        resize(background2, background2,foreGroundImage.size());
        background1.convertTo(background1, CV_32FC3);
        background2.convertTo(background2, CV_32FC3);
        
        // Alpha blending using functions multiply and add
        Mat outImage1= Mat::zeros(foreground.size(), foreground.type());
        Mat outImage2= Mat::zeros(foreground.size(), foreground.type());
        outImage1 = blend(alpha, foreground, background1, outImage1);
        outImage2 = blend(alpha, foreground, background2, outImage2);
        Mat newImage1;
        hconcat(outImage1, outImage2, newImage1);
        imshow("2", newImage1);
    }
    else if (n==3){
        Mat background1 = imread("back2.jpg");
        Mat background2 = imread("back3.jpg");
        Mat background3 = imread("back5.jpg");
        resize(background1, background1,foreGroundImage.size());
        resize(background2, background2,foreGroundImage.size());
        resize(background3, background3,foreGroundImage.size());
        background1.convertTo(background1, CV_32FC3);
        background2.convertTo(background2, CV_32FC3);
        background3.convertTo(background3, CV_32FC3);
        
        // Alpha blending using functions multiply and add
        Mat outImage1= Mat::zeros(foreground.size(), foreground.type());
        Mat outImage2= Mat::zeros(foreground.size(), foreground.type());
        Mat outImage3= Mat::zeros(foreground.size(), foreground.type());
        outImage1 = blend(alpha, foreground, background1, outImage1);
        outImage2 = blend(alpha, foreground, background2, outImage2);
        outImage3 = blend(alpha, foreground, background3, outImage3);
        Mat newImage1,newImage2;
        hconcat(outImage1, outImage2, newImage1);
        hconcat(newImage1, outImage3, newImage2);
        imshow("3", newImage2);
    }
    else if (n==4){
        Mat background1 = imread("back2.jpg");
        Mat background2 = imread("back3.jpg");
        Mat background3 = imread("back5.jpg");
        Mat background4 = imread("back6.jpg");
        resize(background1, background1,foreGroundImage.size());
        resize(background2, background2,foreGroundImage.size());
        resize(background3, background3,foreGroundImage.size());
        resize(background4, background4,foreGroundImage.size());
        background1.convertTo(background1, CV_32FC3);
        background2.convertTo(background2, CV_32FC3);
        background3.convertTo(background3, CV_32FC3);
        background4.convertTo(background4, CV_32FC3);
        
        // Alpha blending using functions multiply and add
        Mat outImage1= Mat::zeros(foreground.size(), foreground.type());
        Mat outImage2= Mat::zeros(foreground.size(), foreground.type());
        Mat outImage3= Mat::zeros(foreground.size(), foreground.type());
        Mat outImage4= Mat::zeros(foreground.size(), foreground.type());
        outImage1 = blend(alpha, foreground, background1, outImage1);
        outImage2 = blend(alpha, foreground, background2, outImage2);
        outImage3 = blend(alpha, foreground, background3, outImage3);
        outImage4 = blend(alpha, foreground, background4, outImage4);
        Mat newImage1,newImage2, newImage3;
        hconcat(outImage1, outImage2, newImage1);
        hconcat(outImage3, outImage4, newImage2);
        vconcat(newImage1, newImage2, newImage3);
        imshow("4", newImage3);
    }
    else{
        cout << "Введите число от 1 до 4!";
    }
    waitKey(0);
    return 0;
}




