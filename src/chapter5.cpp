//-------Warp perspective-------

#include <iostream>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

void main(){
    string path = "../assets/cards.png";
    Mat img = imread(path);

    //Set the 4 points on the source image
    //You have to give float points (Point2f)
    Point2f source_points[4] = {
        {547,148}, //Top left
        {806,198}, //Top right
        {416,413}, //Bottom left
        {705,479} //Bottom right
    };

    //Real aspect ratio based on real measures 5:7
    float w = 250, h = 350;

    //Set 4 destination points
    Point2f destination_points[4] = {
        {0.0f,0.0f}, //Top left
        {w,0.0f}, //Top right
        {0.0f,h}, //Bottom left
        {w,h} //Bottom right
    };

    //Now we need a transformation matrix to get find the warped version
    Mat matrix,imgWarp;
    matrix = getPerspectiveTransform(source_points,destination_points);
    warpPerspective(img,imgWarp,matrix,Point(w,h));

    imshow("Cards", img);
    imshow("Warped Card",imgWarp);
    waitKey(0);
}