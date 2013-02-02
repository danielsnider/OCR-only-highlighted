#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <string>
#include "MyFuncs.h"

using namespace std;
using namespace cv;

Mat KeepHighlightsOnly(Mat img, int r, int g, int b)
// the order of r, g, b is incorrect, reality is that opencv stores channels in bgr format
{
  if (img.channels() != 3) {
    cout << "\nNope. That image didn't seem to be rgb tri-channel." << "\n";
    exit(3);
  }

  int channels = img.channels();
  int nRows = img.rows;
  int nCols = img.cols * channels;
  uchar* p; // will store row of pixels

  int j;
  int count = 0;
  int start, end;
  int row = 0;

  // Scan the image downwards looking for the specified rgb
  while (row < nRows) {
    p = img.ptr<uchar>(row);
    count = 0;

    //count the number of highlighed pixels in a row
    for (int i = 0; i < nCols-3; i = i + 3)
    {
      if (p[i] == b && p[i+1] == g && p[i+2] == r){ // if pixel colour matches
        count++;
      }
    }

    //if no highlighted pixels are found, set the row white
    if (count == 0 ){
      for (int i = 0; i < nCols; i++)
      {
        p[i] = 255;
      }
    }
    // else keep track of the start and continue
    else {
      start = row;
    }

    //if highlighted pixels are found, continue until a row with none is found
    while (count > 0)
    {
      count = 0;

      if (row+1 < nRows) {
        row++;
        p = img.ptr<uchar>(row);

        for (int i = 0; i < nCols-3; i = i + 3)
        {
          if (p[i] == b && p[i+1] == g && p[i+2] == r){ // if pixel colour matches
            count++;
          }
        }
      }

      // now that a highlighted row has been found, set the areas of the row that are not highlighted to white
      if (count == 0){
        row--;
        end = row;
        p = img.ptr<uchar>(end);

        // for each pixel in row
        for (int i = 0; i < nCols-3; i = i + 3)
        {
          // Assuming the bottom row of pixels of the highlight are always the exact same colour...
          // Scanning from left to right in the bottow consecutive row of a highlighted area,
          // If a highlight is not present, set that pixel and all the ones above until the top of
          // the highlighted area white.
          if (p[i] != b || p[i+1] != g || p[i+2] != r){
            for (int j = start; j <= end; ++j)
            {
              p = img.ptr<uchar>(j);
              p[i] = 255;
              p[i+1] = 255;
              p[i+2] = 255;
            }
          }
        }
      }
    }
    row++;
  }

  //remove all highlighting, leaving only the text that was highlighted
  for (int row = 0; row < nRows; ++row)
  {
    p = img.ptr<uchar>(row);
    for (int i = 0; i < nCols-3; i = i + 3)
    {
      if (p[i] == b && p[i+1] == g && p[i+2] == r){ // if pixel colour matches
        p[i] = 255;
        p[i+1] = 255;
        p[i+2] = 255;
      }
    }
  }

  // Mat im_gray;
  cvtColor(img,img,CV_RGB2GRAY);

  return img;
}

void OCR(Mat img) {
//Tesseract OCR one image at a time and return string result

  char cmd[] = "tesseract -l eng temp.jpg temp 1>/dev/null"; // Tesseract system command

  imwrite("temp.jpg", img);

  if (system(cmd) == 0) {
    system("cat temp.txt");
  }
  else {
    cout << "Error: tesseract command failed\n";
  }
}

void cleanUp() {
  system("rm temp.*");
}

