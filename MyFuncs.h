#ifndef __FUNCS_H_INCLUDED__
#define __FUNCS_H_INCLUDED__

#include "opencv2/core/core.hpp"
#include <vector>
#include <string>

using namespace cv;

Mat KeepHighlightsOnly(Mat img, int r, int g, int b);
void OCR(Mat img);
void cleanUp();


#endif // __FUNCS_H_INCLUDED__