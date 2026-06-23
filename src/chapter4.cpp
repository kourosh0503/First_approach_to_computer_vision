//-------Draw shapes and texts on images-------

#include <iostream>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

void main(){
    //----------Blank images----------
    //Size : 512 (h) x 512 (w) //First height then width
    //CV_8UC3: 8-bit unsigned, 3 color channels (BGR order)
    //Good practice is to use Scalar(B,G,R) to set the color
    Mat img(512,512,CV_8UC3,Scalar(255,255,255));
    //----------Circle----------
    //1) Where is the circle added -> On img
    //2) Point(256,256) -> datatype named Point used to set the center of the circle
    //3) 155 -> The radius
    //4) The color
    //5) The tickness of the outline (if ommited 1 by default, filled if -1 or FILLED)
    circle(img,Point(256,256),155,Scalar(0,69,255),FILLED);
    
    //----------Rectangle----------
    //Can either be defined by points or coordinates + size
    // >>By points
    //first the top left corner then bottom right
    // >>By size and coordinates
    //replace the two points by a Rect object (x,y,width,height)
    rectangle(img,Point(130,226),Point(382,286),Scalar(255,255,255),FILLED);
    rectangle(img,Rect(0,0,50,10),Scalar(0,0,0),FILLED);

    //----------Line----------
    line(img, Point(130,296),Point(382,296),Scalar(255,255,255),2);

    //----------Text----------
    //...
    //Point -> Bottom left of the textbox
    //FONTNAME
    //Scale of the font
    //Color
    //Thickness
    putText(img,"STOP",Point(180,276),FONT_HERSHEY_DUPLEX,2,Scalar(0,0,0),2);

    imshow("Created image", img);
    waitKey(0);
}