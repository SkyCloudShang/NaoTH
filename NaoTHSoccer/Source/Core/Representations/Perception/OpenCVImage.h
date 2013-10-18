#ifndef OPENCVIMAGE_H
#define OPENCVIMAGE_H

#include <Representations/Infrastructure/Image.h>
#include <Tools/naoth_opencv.h>

using namespace naoth;

class OpenCVImage
{
public:

  cv::Mat image;

  OpenCVImage();

  OpenCVImage(const Image& orig);

  static cv::Mat convertFromNaoImage(const Image& orig);
};

#endif // OPENCVIMAGE_H
