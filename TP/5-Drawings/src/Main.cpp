#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <vector>
#include<iostream>

using namespace cv;
using namespace std;


int main( int argc, char** argv )
{
	int drawingSizeW = 500;
	int drawingSizeH = 500;

	int x = 0;
	int y = 0;
	int width = drawingSizeW - x;
	int height = drawingSizeW - y;
	int thickness = 2;
	Scalar color;

	Mat drawing(drawingSizeW, drawingSizeH, CV_8UC3, Scalar::all(0));


	for(int i = 0; i < 4; i++)
	{
		switch (i % 4)
		{
		case 1 : color = Scalar(255, 0, 0);
			break;
		case 2 : color = Scalar(0, 255, 0);
			break;
		case 3 : color = Scalar(0, 0, 255);
			break;
		default : color = Scalar(255, 255, 255);
			break;
		}

		if( x >= drawingSizeW || y >= drawingSizeH)
		{
			cout << "Too much squares for the windows size. Maximal number : " << i << "\n";
			break;
		}
		rectangle(drawing, Point(x, y), Point(width, height), color, thickness);
		x += 50;
		y += 50;
		width = drawingSizeW - x;
		height = drawingSizeH - y;
	}

	cout << "Hello";
	imshow("Drawing", drawing);


  waitKey(0);

  return EXIT_SUCCESS;
}
