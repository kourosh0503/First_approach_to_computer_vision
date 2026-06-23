//-------Changing the color space, edge detection, dilation and erosion-------


#include <iostream>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;


//Grayscale
void to_gray(const Mat &img){
    Mat imgGray;
    //cvtColor can be used for grayscaling or converting the BGR format to RGB
    cvtColor(img, imgGray,COLOR_BGR2GRAY); 
    imshow("Image Gray",imgGray);
}

//Blurring
void to_blur(const Mat &img){
    Mat imgBlur;
    GaussianBlur(img,imgBlur,Size(7,7),5,0);
    imshow("Image Blurred",imgBlur);
}

//Edge detection
void edges(const Mat &img){
    //It is a commmon practice to blur a litlle bit the image before edge detection
    Mat imgBlur;
    GaussianBlur(img,imgBlur,Size(3,3),3,0);

    //Canny is the most commonly used edge dectector
    Mat imgCanny;
    //How to chose the values for Canny ?
    //The values can be tunned for better results
    //They more or less correspond to the number of edges you want
    //For the tunning, we will later learn how to add trackbars to see the changes real-time
    Canny(imgBlur,imgCanny,50,150);

    //Edge detected are often not joined or too thin
    //Solution -> Dilation or erosion 
    //Dilation and erosion are opposite
    //Dilation means increasing edge thickness
    Mat imgDil,imgEro;
    //The size in the parameters give a magnitude of dilation or erosion
    Mat kernel = getStructuringElement(MORPH_RECT,Size(3,3)); //Size is odd in general (3,3) (5,5) ...
    dilate(imgCanny,imgDil,kernel);
    erode(imgCanny,imgEro,kernel);

    imshow("Edge detection",imgCanny);
    imshow("Edge dilted",imgDil);
    imshow("Edge eroded",imgEro);
}

void main(){
    string path = "../assets/sidewalk.png";
    
    Mat img = imread(path);
   
    //imshow("Image",img);
    //to_gray(img);
    //to_blur(img);
    edges(img);
    
    waitKey(0);
}