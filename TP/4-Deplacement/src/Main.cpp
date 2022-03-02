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
  Mat imageBlur;
  Mat imageBlurG;
  Mat imageBlurM;
  Mat imageFilterBilateral;
  Mat imageFilterBox;
  Mat imageSobel1;
  Mat imageSobel2;
  Mat imageSobel3;
  Mat imageScharr1;
  Mat imageScharr2;
  Mat imageLaplacien;
  Mat canny;

  imageColor = imread( IMG_PATH, 1 );

  if(!imageColor.data )
    {
	  std::cout << "No image data \n";
      return -1;
    }

  blur(imageColor, imageBlur, Size(9, 9), Point(-1, -1), BORDER_DEFAULT);
  GaussianBlur(imageColor, imageBlurG, Size(9, 9), 0, 0, BORDER_DEFAULT);
  medianBlur(imageColor, imageBlurM, 9);
  bilateralFilter(imageColor, imageFilterBilateral, 9, 75, 75, BORDER_DEFAULT);
  boxFilter(imageColor, imageFilterBox, -1, Size(9, 9), Point(-1, -1), true, BORDER_DEFAULT);
  Sobel(imageColor, imageSobel1, -1, 0, 1, 3, 1, 0, BORDER_DEFAULT);
  Sobel(imageColor, imageSobel2, -1, 1, 0, 3, 1, 0, BORDER_DEFAULT);
  Sobel(imageColor, imageSobel3, -1, 1, 1, 3, 1, 0, BORDER_DEFAULT);
  Scharr(imageColor, imageScharr1, -1, 1, 0, 1, 0, BORDER_DEFAULT);
  Scharr(imageColor, imageScharr2, -1, 0, 1, 1, 0, BORDER_DEFAULT);
  Laplacian(imageColor, imageLaplacien, -1, 1, 1, 0, BORDER_DEFAULT);
  Canny(imageColor, canny, 100, 200, 3, false);

  namedWindow( "Initial Image", WINDOW_AUTOSIZE );
  namedWindow( "Blur", WINDOW_AUTOSIZE );
  namedWindow( "Gaussien Blur", WINDOW_AUTOSIZE );
  namedWindow( "Median Blur", WINDOW_AUTOSIZE );
  namedWindow( "Bilateral Filter", WINDOW_AUTOSIZE );
  namedWindow( "Box Filter", WINDOW_AUTOSIZE );
  namedWindow( "Sobel 1", WINDOW_AUTOSIZE );
  namedWindow( "Sobel 2", WINDOW_AUTOSIZE );
  namedWindow( "Sobel 3", WINDOW_AUTOSIZE );
  namedWindow( "Scharr 1", WINDOW_AUTOSIZE );
  namedWindow( "Scharr 2", WINDOW_AUTOSIZE );
  namedWindow( "Laplacien", WINDOW_AUTOSIZE );
  namedWindow( "Canny", WINDOW_AUTOSIZE );



  imshow( "Initial Image", imageColor );
  imshow( "Blur", imageBlur );
  imshow( "Gaussien Blur", imageBlurG );
  imshow( "Median Blur", imageBlurM );
  imshow( "Bilateral Filter", imageFilterBilateral );
  imshow( "Box Filter", imageFilterBox );
  imshow( "Sobel 1", imageSobel1 );
  imshow( "Sobel 2", imageSobel2 );
  imshow( "Sobel 3", imageSobel3 );
  imshow( "Scharr 1", imageScharr1 );
  imshow( "Scharr 2", imageScharr2 );
  imshow( "Laplacien", imageLaplacien );
  imshow( "Canny", canny );

  waitKey(0);

  return EXIT_SUCCESS;
}
