#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/video/background_segm.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdio.h>
#include <unistd.h>
using namespace std;
using namespace cv;
 
 
int main(int argc, const char** argv)
{
	VideoCapture cap;
	bool update_bg_model = true;
CommandLineParser parser(argc, argv, "{help h||}{@input||}"); 
	string input = parser.get<std::string>("@input");
    	if (input.empty())
        	cap.open(0);
    	else
        	cap.open(samples::findFileOrKeep(input));

	//cap.open("1.avi");
 
	if( !cap.isOpened() )
	{
		printf("can not open camera or video file\n");
		return -1;
	}
 
	namedWindow("image", WINDOW_AUTOSIZE);
	namedWindow("foreground mask", WINDOW_AUTOSIZE);
	namedWindow("foreground image", WINDOW_AUTOSIZE);
	namedWindow("mean background image", WINDOW_AUTOSIZE);
 
	cv::Ptr<BackgroundSubtractorMOG2> bg_model=createBackgroundSubtractorMOG2();
	 bg_model->setNMixtures(5);
 
	Mat img, fgmask, fgimg;
 
	for(;;)
	{
		usleep(100000);
		cap >> img;
 
		if( img.empty() )
			break;
 
 
		if( fgimg.empty() )
			fgimg.create(img.size(), img.type());
 
		//update model
		bg_model->apply(img, fgmask, update_bg_model ? -1 : 0);
 			
		fgimg = Scalar::all(0);
		img.copyTo(fgimg, fgmask);
 
		Mat bgimg;
 
		imshow("image", img);
		imshow("foreground mask", fgmask);
		imshow("foreground image", fgimg);
		if(!bgimg.empty())
			imshow("mean background image", bgimg );
 
		char k = (char)waitKey(1);
		if( k == 27 ) break;
		if( k == ' ' )
		{
			update_bg_model = !update_bg_model;
			if(update_bg_model)
				printf("\t>Background update is enable\n");
			else
				printf("\t>Background update is disable\n");
		}
	}
 
	return 0;
}
