//-------Resize and crop-------


#include <iostream>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

void main(){
    string path = "../assets/sidewalk.png";
    Mat img,imgResized,imgCropped;
    img = imread(path);

    // >>Two ways to use resize
    //resize(imgOrigin,imgNew,Size(newX,newY))
    //resize(imgOrigin,imgNew,Size(),ratioX,ratioY)
    resize(img,imgResized,Size(),1,0.5);

    //Cropping
    //Rect(x,y,width,height)
    Rect roi(100,100,200,250);
    imgCropped = img(roi);

    imshow("Original Image",img);
    imshow("Resized Image",imgResized);
    imshow("Cropped Image",imgCropped);
    waitKey(0);
}
