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
    Mat img(600,600, CV_8UC1);
    int colorCircle[] = {127,0,255,255,127,0};
    int colorRect[] = {255,127,0,127,0,255};
    int k, z, index =0;
    for(int i=0;i<2;i++){
        for(int j=0;j<3;j++){
            if(i==1){
                rectangle(img, Point(k,z), Point(k+img.rows/3,z+img.rows/2),Scalar(colorRect[index]),FILLED);
                index++;
            } else {
                rectangle(img, Point(k,z), Point(k+img.rows/3,z+img.rows/2),Scalar(colorRect[index]),FILLED);
                index++;
            }
            k+=img.rows/3;
        }
        z+=img.rows/2;
        k=0;
    }
    index = 0;
    for(int i=0;i<img.cols;i++){
        for(int j=0;j<img.rows;j++){
            
            if ((j==img.rows/6||j==img.rows/2||j==img.rows/6*5)){
                if(i==img.rows/4){
                    circle(img, Point(j,i), img.rows/8, Scalar(colorCircle[index]),FILLED);
                    index++;
                } else if (i==img.rows/4*3){
                    circle(img, Point(j,i), img.rows/8, Scalar(colorCircle[index]),FILLED);
                    index++;
                }
            }
        }
    }

    Mat resFirst;
    Mat resSecond;
    const float kernelData1[] = {
        1.0, 0,
        0, -1.0};
    const Mat kernel1(2, 2, CV_32FC1,(float *)kernelData1);
    filter2D(img, resFirst, -1, kernel1, Point(-1, -1), 128, BORDER_REPLICATE);
    
    const float kernelData2[] = {
        0, 1.0,
        -1.0, 0};
    const Mat kernel2(2, 2, CV_32FC1,(float *)kernelData2);
    filter2D(img, resSecond, -1, kernel2, Point(-1, -1), 128, BORDER_REPLICATE);
    
    imshow("after filter1", resFirst);
    imshow("after filter2", resSecond);
    imshow("result",img);
    waitKey();
    destroyAllWindows();
    return 0;
}




