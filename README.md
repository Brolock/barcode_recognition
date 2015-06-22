# barcode_recognition
A very simple barcode recognition using OpenCV.

# Requierement:
OpenCV (recent version prefered)
A C++ compiler supporting C++14 (gcc-4.9, clang-3.5)

A webcam if willing to go with video recognition.

# Installation
Create a build directory, call cmake then make from it.
Binary tirf should be built in it.

mkdir build
cd build
cmake ..
make
./tirf ...

# Basic use

Recognition on an image:

./tirf [--debug] path/to/image

Recognition on a video:

Will capture the video stream from the webcam:

./tirf --video

Will play the video on path:

./tirf --video path/to/video
