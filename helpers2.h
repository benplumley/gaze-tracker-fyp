#ifndef HELPERS2_H
#define HELPERS2_H

#define degrees 91.016667f
#define centimetres 204.7875f
#include "DataCollector.h"
#include "eyelike/opencv2/calib3d/calib3d.hpp"
cv::Mat getRotationMatrix();
cv::Mat getTranslationMatrix();
cv::Mat getHomography();

#endif
