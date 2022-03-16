#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <vector>
#include<iostream>

using namespace cv;
using namespace std;

#define IMG_FRONT_PATH "data/front.png"
#define IMG_BACK_PATH "data/back.png"
#define IMG_RESULT_PATH "data/result.png"

#define IMG_BLUR_COEF 9
#define BLUR_DEPTH 3

#define DEPLACEMENT_COL -250
#define DEPLACEMENT_ROW -30

#define COLOR_NUMBER 3
#define INDEX_BLUE 2
#define INDEX_GREEN 1
#define INDEX_RED 0


int main( int argc, char** argv )
{
	// Data initialization
	Mat imgBack;
	Mat imgFront;

	Mat imgBackBlur;
	Mat imgFrontBlur;

	Mat imgBackBinary;
	Mat imgFrontBinary;

	Mat imgSubtract;
	Mat imgSubtractBinary;
	Mat imgSubtractDilated;
	Mat imgSubtractEroded;

	vector<Mat> imgFrontColorSplit;
	vector<Mat> imgResult;
	Mat imgResultColor;

	// Read input images
	imgBack = imread( IMG_BACK_PATH, 1 );
	imgFront = imread( IMG_FRONT_PATH, 1 );

	if(!imgBack.data || !imgFront.data )
	{
		cout << "No image data \n";
		return -1;
    }

	// Adapt the size of input images
	Size size;
	if(imgBack.size < imgFront.size)
	{
		size = imgBack.size();
		resize(imgFront, imgFront, size);
	}
	else if(imgBack.size > imgFront.size)
	{
		size = imgFront.size();
		resize(imgBack, imgBack, size);
	}

	// Initializes all other matrices
	imgResultColor = imgBack.clone();
	imgFrontBinary.create(size, CV_8U);
	imgBackBinary.create(size, CV_8U);
	imgResultColor.create(size, CV_8U);

	// Gaussian blur to reduce noise due to the size reduction
	GaussianBlur(imgFront, imgFrontBlur, Size(IMG_BLUR_COEF, IMG_BLUR_COEF), 18, 0, 4);
	GaussianBlur(imgBack, imgBackBlur, Size(IMG_BLUR_COEF, IMG_BLUR_COEF), 18, 0, 4);

	// Transformation into gray images
	cvtColor(imgBackBlur, imgBackBinary, COLOR_BGR2GRAY);
	cvtColor(imgFrontBlur, imgFrontBinary, COLOR_BGR2GRAY);

	// Subtraction of the 2 binary images to detect their differences
	subtract(imgBackBinary, imgFrontBinary, imgSubtract);

	// Noise reduction with Gaussian Blur
	for(int j = 0; j < BLUR_DEPTH; j++)
	{
		GaussianBlur(imgSubtract, imgSubtract, Size(3, 3), 15, 0, 4);
	}

	/*
	 * Added after the teacher's correction
	 */

	// Binarization
	threshold(imgSubtract, imgSubtractBinary, 50, 255, THRESH_OTSU + THRESH_BINARY);

	// Dilation to fill the selected object
	dilate(imgSubtractBinary, imgSubtractDilated, Mat(), Point(-1, -1), 18);

	// Erosion
	erode(imgSubtractDilated, imgSubtractEroded, Mat(), Point(-1, -1), 16);

	/*
	 * End of the added part after the teacher's correction
	 */

	// Split images color
	split(imgFront, imgFrontColorSplit);
	split(imgBack, imgResult);

	// Draw selected object in the back image, with a different position
	for (int x = 0; x < imgResultColor.rows; x++)
	{
		for (int y = 0; y < imgResultColor.cols; y++)
		{
			if(imgSubtractEroded.at<uchar>(x, y) > 0 &&
					(y + DEPLACEMENT_COL > 0 && y + DEPLACEMENT_COL <= imgResultColor.cols) &&
					(x + DEPLACEMENT_ROW > 0 && x + DEPLACEMENT_ROW <= imgResultColor.rows))
			{
				for(int i = 0; i < COLOR_NUMBER; i++)
				{
					imgResult[i].at<uchar>(x + DEPLACEMENT_ROW, y + DEPLACEMENT_COL) = imgFrontColorSplit[i].at<uchar>(x, y);
				}

			}
		}
	}

	// Restore result image colors
	Mat channels[COLOR_NUMBER] = {imgResult[INDEX_RED], imgResult[INDEX_GREEN], imgResult[INDEX_BLUE]};
	merge(channels, COLOR_NUMBER, imgResultColor);

	// Save result
	imwrite(IMG_RESULT_PATH, imgResultColor);

	// Display initial images and result
//	namedWindow( "Back", WINDOW_AUTOSIZE );
//	namedWindow( "Front", WINDOW_AUTOSIZE );
//	namedWindow( "Back Blur", WINDOW_AUTOSIZE );
//	namedWindow( "Front Blur", WINDOW_AUTOSIZE );
//	namedWindow( "Back Binary", WINDOW_AUTOSIZE );
//	namedWindow( "Front Binary", WINDOW_AUTOSIZE );
//	namedWindow( "Subtract", WINDOW_AUTOSIZE );
//	namedWindow( "Subtract Binary", WINDOW_AUTOSIZE );
//	namedWindow( "Dilated", WINDOW_AUTOSIZE );
//	namedWindow( "Eroded", WINDOW_AUTOSIZE );
	namedWindow( "Result Color", WINDOW_AUTOSIZE );

//	imshow( "Back", imgBack );
//	imshow( "Front", imgFront );
//	imshow( "Back Blur", imgBackBlur );
//	imshow( "Front Blur", imgFrontBlur );
//	imshow( "Front Binary", imgFrontBinary );
//	imshow( "Back Binary", imgBackBinary );
//	imshow( "Subtract", imgSubtract );
//	imshow( "Subtract Binary", imgSubtractBinary);
//	imshow( "Dilated", imgSubtractDilated);
//	imshow( "Eroded", imgSubtractEroded);
	imshow( "Result Color", imgResultColor );

//	for(uchar i = 0; i < COLOR_NUMBER; i++)
//	{
//		imshow( "Front Split  " + to_string(i), imgFrontColorSplit[i]);
//		imshow( "Result " + to_string(i), imgResult[i]);
//	}

	// Close all windows when a key is pressed
	waitKey(0);
	destroyAllWindows();

  return EXIT_SUCCESS;
}
