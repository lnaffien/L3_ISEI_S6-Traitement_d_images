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
#include<iostream>

using namespace cv;

#define IMG_PATH "data/c_img1.png"

int main( int argc, char** argv )
{
  Mat imageColor;
  Mat imageGray;
  Mat histGray;

  imageColor = imread( IMG_PATH, 1 );

  if(!imageColor.data )
    {
	  std::cout << "No image data \n";
      return -1;
    }
  cvtColor(imageColor, imageGray, COLOR_BGR2GRAY);

  int histSize = 256;
  float range[] = { 0, 256 };
  const float* histRange = { range };
  bool uniform = true;
  bool accumulate = false;

  calcHist(&imageGray, 1, 0, Mat(), histGray, 1, &histSize, &histRange, uniform, accumulate);
  Mat histGrayNormalized;
  int hist_w = 1024;
  int hist_h = 800;
  int bin_w = cvRound((double) hist_w / histSize);
  Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(0, 0, 0));
  normalize(histGray, histGrayNormalized, 0, histImage.rows, NORM_MINMAX, -1, Mat());

  for(int i = 1; i < histSize; i++)
  {
	  line(histImage,
			  Point(bin_w * (i - 1), hist_h - cvRound(histGrayNormalized.at<float>(i - 1))),
			  Point(bin_w * i, hist_h - cvRound(histGrayNormalized.at<float>(i))),
			  Scalar(255, 255, 255),
			  2, 8, 0);
  }

  namedWindow( "Display Image Color", WINDOW_AUTOSIZE );
  namedWindow( "Display Image Gray", WINDOW_AUTOSIZE );
  namedWindow( "Display Histogram Gray", WINDOW_AUTOSIZE );

  imshow( "Display Image Color", imageColor );
  imshow( "Display Image Gray", imageGray );
  imshow( "Display Histogram Gray", histImage );

  waitKey(0);

  return EXIT_SUCCESS;
}
