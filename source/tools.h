#ifndef TOOLS_H_
# define TOOLS_H_

#include <vector>
#include <opencv2/opencv.hpp>

bool compareContourAreas(const cv::RotatedRect& rec_1, const cv::RotatedRect& rec_2);

#endif // TOOLS_H_
