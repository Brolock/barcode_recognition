#include "tools.h"

bool compareContourAreas(const cv::RotatedRect& rec_1, const cv::RotatedRect& rec_2)
{
    auto i = rec_1.size.height * rec_1.size.width;
    auto j = rec_2.size.height * rec_2.size.width;

    return i > j;
}
