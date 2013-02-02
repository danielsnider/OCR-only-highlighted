#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>

#include "MyFuncs.h"

using std::cout;
using std::system;

using namespace cv;

void KindleHighlightOCR(char* img_path, char* hi_r, char* hi_g, char* hi_b)
{
  Mat img;
  int r, g, b;

  // Convert colour of highlight from char to int
  r = atoi(hi_r);
  g = atoi(hi_g);
  b = atoi(hi_b);

  // Load image
  img = imread(img_path, 1);
  if (img.empty())
  {
    cout << "\nCannot open image!\n";
    exit(1);
  }

  // Other than text highlighted in a given colour make everything white
  img = KeepHighlightsOnly(img, r, g, b);

  // OCR pieces with Tesseract and cout results
  OCR(img);

  // Clean up
  cleanUp();
}

int main(int argc, char** argv)
{
  // cout << "Usage: $0 [image] [colour of highlighted colour, red intensity] [green intensity] [blue intensity]\n";
  // cout << "A common iOS kindle highlight colour is (251,226,152).\n";

  if( argc != 5)
  {
   cout << "Usage: $0 [image] [colour of highlighted colour, red intensity] [green intensity] [blue intensity]\nA common iOS kindle highlight colour is (251,226,152).\n\n";
   return -1;
  }

  KindleHighlightOCR(argv[1], argv[2], argv[3], argv[4]);
}
