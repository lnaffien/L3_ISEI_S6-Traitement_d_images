/*
 * 1- Convertir une image BGR en Image de gris.
 * 2- Tracer l’histogramme d’une image couleur puis l’histogramme de son image de gris.
 * 3- Tracer l’histogramme cumulé normalisé d’une image de gris.
 * 4- Afficher la correction d’une image de gris en utilisant une égalisation d’histogramme.*
 * 5- Afficher l’image binaire d’une image de gris avec :
 *      a - THRESH_BINARY puis THRESH_BINARY_INV
 *      b - THRESH_OTSU
 *      c - THRESH_TRIANGLE
 */

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <vector>
#include<iostream>

using namespace cv;

#define IMG_PATH "data/c_img1.png"

int main( int argc, char** argv )
{
  Mat imageColor;

  imageColor = imread( IMG_PATH, 1 );

  if(!imageColor.data )
    {
	  std::cout << "No image data \n";
      return -1;
    }

  std::vector<Mat> imageColorSplit;
  split( imageColor, imageColorSplit);

  int histSize = 256;
  float range[] = { 0, 256 };
  const float* histRange = { range };
  bool uniform = true;
  bool accumulate = false;

  Mat histBlue;
  Mat histGreen;
  Mat histRed;

  calcHist( &imageColorSplit[0], 1, 0, Mat(), histBlue, 1, &histSize, &histRange, uniform, accumulate );
  calcHist( &imageColorSplit[1], 1, 0, Mat(), histGreen, 1, &histSize, &histRange, uniform, accumulate );
  calcHist( &imageColorSplit[2], 1, 0, Mat(), histRed, 1, &histSize, &histRange, uniform, accumulate );


  Mat histNormBlue;
  Mat histNormGreen;
  Mat histNormRed;

  int hist_w = 1024;
  int hist_h = 800;
  int bin_w = cvRound((double) hist_w / histSize);
  Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(0, 0, 0));

  normalize(histBlue, histNormBlue, 0, histImage.rows, NORM_MINMAX, -1, Mat());
  normalize(histGreen, histNormGreen, 0, histImage.rows, NORM_MINMAX, -1, Mat());
  normalize(histRed, histNormRed, 0, histImage.rows, NORM_MINMAX, -1, Mat());

  for(int i = 1; i < histSize; i++)
  {
	  line(histImage,
				  Point(bin_w * (i - 1), hist_h - cvRound(histNormBlue.at<float>(i - 1))),
				  Point(bin_w * i, hist_h - cvRound(histNormBlue.at<float>(i))),
				  Scalar(255, 0, 0),
				  2, 8, 0);
	  line(histImage,
	  			  Point(bin_w * (i - 1), hist_h - cvRound(histNormGreen.at<float>(i - 1))),
	  			  Point(bin_w * i, hist_h - cvRound(histNormGreen.at<float>(i))),
	  			  Scalar(0, 255, 0),
	  			  2, 8, 0);
	  line(histImage,
	  			  Point(bin_w * (i - 1), hist_h - cvRound(histNormRed.at<float>(i - 1))),
	  			  Point(bin_w * i, hist_h - cvRound(histNormRed.at<float>(i))),
	  			  Scalar(0, 0, 255),
	  			  2, 8, 0);
  }

  namedWindow( "Display Image Color", WINDOW_AUTOSIZE );
  namedWindow( "Display Histogram Color", WINDOW_AUTOSIZE );

  imshow( "Display Image Color", imageColor );
  imshow( "Display Histogram Color", histImage );

  waitKey(0);

  return EXIT_SUCCESS;
}
