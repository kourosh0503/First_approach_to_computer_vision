//-------Color detection-------

#include <iostream>
#include <Windows.h>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

void main(){
    string path = "../assets/shapes.png";
    Mat img = imread(path);
    Mat imgHSV;

    //For more info about HSV color space: https://medium.com/@dijdomv01/a-beginners-guide-to-understand-the-color-models-rgb-and-hsv-244226e4b3e3
    cvtColor(img,imgHSV,COLOR_BGR2HSV);

    //-----Creating a trackbar-----
    
    // >>nameWindow
    // 1) window name
    // 2) size of the windws (w,h)
    namedWindow("Trackbars",WINDOW_NORMAL); //Create the window first
    resizeWindow("Trackbars",640,200);
    
    // >>createTrabar
    // 1) Name of the bar
    // 2) Name of the window containing the trackbar
    // 3) Address of the value to change
    // 4) Max value
    createTrackbar("Hue min", "Trackbars", nullptr,179);
    createTrackbar("Saturation min", "Trackbars", nullptr,255);
    createTrackbar("Value min", "Trackbars", nullptr,255);
    createTrackbar("Hue max", "Trackbars", nullptr,179);
    createTrackbar("Saturation max", "Trackbars", nullptr,255);
    createTrackbar("Value max", "Trackbars", nullptr,255);

    //-----------------------------

    while(true){
        if(GetAsyncKeyState(VK_ESCAPE) & 0x8000){
            break;
        }

        //Paramters for the Mask
        int hmin = getTrackbarPos("Hue min","Trackbars"), 
        smin = getTrackbarPos("Saturation min","Trackbars"),
        vmin = getTrackbarPos("Value min","Trackbars");
        
        int hmax = getTrackbarPos("Hue max","Trackbars"),
        smax = getTrackbarPos("Saturation max","Trackbars"),
        vmax = getTrackbarPos("Value max","Trackbars");

        //Generating a mask based on a range of values
        Mat mask;
        Scalar lower(hmin,smin,vmin);
        Scalar upper(hmax,smax,vmax);
        inRange(imgHSV,lower,upper,mask);


        imshow("Source image",img);
        imshow("HSV image",imgHSV);
        imshow("mask", mask);


        waitKey(1);
    }
}
