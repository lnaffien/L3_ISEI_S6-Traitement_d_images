#include <opencv2/highgui.hpp>

using namespace cv;

#define IMG_PATH "data/c_img1.png"

int main( int argc, char** argv )
{
  Mat image;

  image = imread( IMG_PATH, 1 );
  if(!image.data )
    {
      printf( "No image data \n" );
      return -1;
    }
  namedWindow( "Display Image", WINDOW_AUTOSIZE );
  imshow( "Display Image", image );
  waitKey(0);
  return 0;
}
