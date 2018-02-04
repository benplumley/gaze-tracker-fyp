#ifndef EYEINTERFACE_H
#define EYEINTERFACE_H

#include "eyelike/opencv2/calib3d/calib3d.hpp"

struct EYE {
	int x;
	int y;
};

struct EYELIKEDATA {
	int face_width;
	EYE left_eye;
	EYE right_eye;
};

class EyeInterface {
	public:
		EyeInterface();
		EYELIKEDATA getData();
		void setOrigin();
		cv::vector<cv::Point2f> getOffset(cv::vector<cv::Point2f> eyepos);
};

#endif
