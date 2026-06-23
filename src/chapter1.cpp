//-------Importing images, videos and webcome inputs-------


#include <iostream>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

// Importing Images
void imgImport(){

    string path = "../assets/sidewalk.png";
    Mat img = imread(path); //Mat is a matrix containing the image
    imshow("Sidewalk image", img);
    waitKey(0); //Wait inf seconds (until key pressed)

}

//Importing Videos
void vidImport(){

    string path = "../assets/sheep.mp4";
    VideoCapture cap("../assets/sheep.mp4"); //Video capture object
    Mat img;

    //-------------------------------------
    // >>Find the FPS value of a video
    // Source : https://www.tutorialspoint.com/article/how-to-get-the-fps-value-in-opencv-using-cplusplus
    int FPS;
    FPS = cap.get(CAP_PROP_FPS);
    //-------------------------------------

    while(true){
        cap.read(img); //Read the image from the video
        imshow("Video",img); 
        waitKey(static_cast<int>(1000/FPS)); 
    }
    cap.release();
}

//Webcame capture
void webCamCapture(){
    VideoCapture cap(0); //The number corresponds to the webcam assigned number (0,1,2...)
    Mat img;

    while(true){
        cap.read(img);
        imshow("Webcam",img);
        waitKey(1);
    }
}

void main(){
    webCamCapture();
}
