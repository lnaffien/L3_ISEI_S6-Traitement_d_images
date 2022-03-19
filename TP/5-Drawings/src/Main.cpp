#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <vector>
#include<iostream>

using namespace cv;
using namespace std;

void nestedSquares(int drawingSizeW, int drawingSizeH, int thickness);
void alignedSquares(int drawingSizeW, int drawingSizeH, int thickness);
Scalar getColor(int squareNumber);

int main( int argc, char** argv )
{
	int drawingSizeW = 500;
	int drawingSizeH = 500;
	int squareThickness = 2;

	nestedSquares(drawingSizeW, drawingSizeH, squareThickness);
	alignedSquares(drawingSizeW, drawingSizeH, squareThickness);

	cout << "Hello";

	waitKey(0);

	return EXIT_SUCCESS;
}

void nestedSquares(int drawingSizeW, int drawingSizeH, int thickness)
{
	int x = 0;
	int y = 0;
	int width = drawingSizeW - x;
	int height = drawingSizeW - y;

	Scalar color;

	Mat drawing(drawingSizeW, drawingSizeH, CV_8UC3, Scalar::all(0));


	for(int i = 0; i < 4; i++)
	{
		color = getColor(i);

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

	imshow("Nested", drawing);

}

void alignedSquares(int drawingSizeW, int drawingSizeH, int thickness)
{
	int space = 30;
	int x = space;
	int y = space;
	int width = drawingSizeW / 2 - space;
	int height = drawingSizeW / 2 - space;
	Scalar color;

	Mat drawing(drawingSizeW, drawingSizeH, CV_8UC3, Scalar::all(0));

	for(int i = 0; i < 4; i++)
	{
		color = getColor(i);
		rectangle(drawing, Point(x, y), Point(width, height), color, thickness);

		if(x + width > drawingSizeW - space)
		{
			// Il faut changer cette partie la
			y += space + height;
			height += space + height;
			width = 0;
			// Jusque la
			cout << "Heeeey\n";
		}

		x += space + width;
		width += space + width;
	}



	imshow("Aligned", drawing);
}

Scalar getColor(int squareNumber)
{
	switch (squareNumber % 4)
	{
		case 1 : return Scalar(255, 0, 0);
		case 2 : return Scalar(0, 255, 0);
		case 3 : return Scalar(0, 0, 255);
		default : return Scalar(255, 255, 255);
	}
}
