#include <vector>
#include <stdio.h>
#include "opencv2/opencv.hpp"
#include <boost/thread/thread.hpp>
#define eq ==

using namespace cv;
using namespace std;
Mat* frame;
VideoCapture *cap;
void Prepare()
{
	*cap >> *frame;
	frame->convertTo(*frame, -1, 2, 0);
}


int main(int ARGC,char** ARGV)
{
 	cap = new VideoCapture(1); 
    if(!(*cap).isOpened())  
       	(*cap).open(0);
	assert((*cap).isOpened());
	Mat edges;	
    namedWindow("capture" , 0);
    int counter=0;
    char filename[512];
	int param1 = 90,param2 = 80,param3 = 8,param4 = 5,param5 = 0;
	char mode = 0;int alpha = 3,beta = -2;
    frame = new Mat();

    while(true)
	{
		boost::thread thread_get_frame(&Prepare);
		cvtColor(*frame, edges, CV_BGR2GRAY);
    	Canny(edges, edges, 50, 200, 3, 1);	
		vector<Vec4i> lines;
   		HoughLinesP( edges, lines, 1, CV_PI/180, param1, param2, param3 );
		cvtColor(edges, edges, CV_GRAY2BGR );
   		for( int i = 0; i < lines.size(); i++ )
    	{
        	if(mode) line( *frame, Point(lines[i][0], lines[i][1]),
            Point(lines[i][2], lines[i][3]), Scalar(0,0,255), 3, 8 );
			else line( edges, Point(lines[i][0], lines[i][1]),
            Point(lines[i][2], lines[i][3]), Scalar(0,0,255), 3, 8 );
    	}			

        if(mode) imshow("capture", *frame);
        else imshow("capture", edges);
        char c = waitKey(33);
        switch(c)
		{
			case 0x61: param1+=2; 
					   printf("%d %d %d  :    %d %d\n",param1,param2,param3,param4,param5);
			break;
			case 0x7a: param1-=2;
					   printf("%d %d %d  :    %d %d\n",param1,param2,param3,param4,param5);
			break;
			case 0x73: param2+=2;
					   printf("%d %d %d  :    %d %d\n",param1,param2,param3,param4,param5);
			break;
			case 0x78: param2-=2;
					   printf("%d %d %d  :    %d %d\n",param1,param2,param3,param4,param5);
			break;
			case 0x64: param3+=2;
					   printf("%d %d %d  :    %d %d\n",param1,param2,param3,param4,param5);
			break;
			case 0x63: param3-=2;
					   printf("%d %d %d  :    %d %d\n",param1,param2,param3,param4,param5);
			break;
			case 0x6d: mode = (mode + 1)%2;
					   printf("%d %d %d  :    %d %d\n",param1,param2,param3,param4,param5);
			break;
			case 0x66: param4+=1;
					   printf("%d %d %d  :    %d %d\n",param1,param2,param3,param4,param5);
			break;
			case 0x76: param4-=1;
					   printf("%d %d %d  :    %d %d\n",param1,param2,param3,param4,param5);
			break;
			case 0x67: param5+=1;
					   printf("%d %d %d  :    %d %d\n",param1,param2,param3,param4,param5);
			break;
			case 0x62: param5-=1;
					   printf("%d %d %d  :    %d %d\n",param1,param2,param3,param4,param5);
			break;
		
		}
		if (c == 27)
		{ 
            break;
        }
        else if(c == 13) 
		{
            sprintf(filename, "Image%d.jpg", counter);
            printf("[i] capture... %s\n", filename);
			printf("counter = %d\n",counter);
            if(mode) imwrite(filename, *frame);
        	else imwrite(filename, edges);
            counter++;
        }
				
        }
	return 0;
}
