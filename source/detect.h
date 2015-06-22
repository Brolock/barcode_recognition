#ifndef DETECT_H_
# define DETECT_H_

#include <opencv2/opencv.hpp>

int DetectBarCode(const std::string& filename, bool with_debug = false);
int DetectBarCode(cv::Mat& image, bool with_debug = false);
int VideoBarCode(const std::string& filename);
int VideoBarCode();

#endif // DETECT_H_
