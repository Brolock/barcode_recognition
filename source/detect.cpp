#include "tools.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

void display_image(const std::string& title, const Mat& image, bool do_wait = true)
{
        namedWindow(title, CV_WINDOW_AUTOSIZE);
        imshow(title, image);
        if (do_wait)
        {
            waitKey(0);
            cvDestroyWindow(title.c_str());
        }
}

int DetectBarCode(Mat& image, bool with_debug = false, bool is_video = false)
{
    auto original = image;

    if (!image.data)
    {
        cout << "No image data" << std::endl;
        return -1;
    }

    /* convert image to GrayScale */
    cvtColor(image, image, CV_BGR2GRAY);

    if (with_debug)
        display_image("GrayScale", image);


    /* gradient to highlight vertical lines */
    Mat grad_x;
    int ddepth = CV_32F;

    Sobel(image, grad_x, ddepth, 1, 0, -1);

    image = grad_x;
    convertScaleAbs(image, image);

    if (with_debug)
        display_image("Gradiented!", image);

    /* Blurring */
    GaussianBlur(image, image, Size(9, 9), 20, 20);
    if (with_debug)
        display_image("Blur", image);

    /* Threshold */
    threshold(image, image, 225, 255, THRESH_BINARY);
    if (with_debug)
        display_image("Threshold", image);

    /* Filling the gaps */
    auto rectangle = getStructuringElement(MORPH_RECT, Size(24, 3));
    morphologyEx(image, image, MORPH_CLOSE, rectangle);
    if (with_debug)
        display_image("Gap closing", image);

    /* Erode */

    Mat element;
    for (int i = 0; i < 2; ++i)
        erode(image, image, element);
    for (int i = 0; i < 2; ++i)
        dilate(image, image, element);

    if (with_debug)
        display_image("Erode then dilate", image);

    /* Contours  and display rectangle*/
    vector<vector<Point>> contours;

    findContours(image, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    if (contours.size() == 0)
    {
      cout << "No barcode detected" << endl;
      display_image("Final Result", original, !is_video);
      return -1;
    }

    vector<RotatedRect> results(contours.size());
    for (const auto& contour : contours)
        results.push_back(minAreaRect(Mat(contour)));

    std::sort(results.begin(), results.end(), compareContourAreas);

    auto result = results[0];


    Point2f rect_points[4];
    result.points(rect_points);
    for (int i = 0; i < 4; ++i)
        line(original, rect_points[i], rect_points[(i + 1) % 4], Scalar(0, 255, 0), 3);


    display_image("Final Result", original, !is_video);

    return 0;
}

int DetectBarCode(const std::string& filename, bool with_debug)
{
    // load image
    auto image = imread(filename, CV_LOAD_IMAGE_COLOR);
    return DetectBarCode(image, with_debug);
}

int VideoBarCode(VideoCapture& camera)
{
    Mat frame; // The image frame
    while (true)
    {
        camera.grab();
        camera.retrieve(frame);
        DetectBarCode(frame, false, true); 

        if (waitKey(30) > 0)
            break;
    }
    return 0;
}

int VideoBarCode(const std::string& filename)
{
    auto camera = VideoCapture(filename);
    return VideoBarCode(camera);
}

int VideoBarCode()
{
    auto camera = VideoCapture(0);
    return VideoBarCode(camera);
}
