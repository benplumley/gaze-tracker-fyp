#define _AFXDLL
#define degrees 91.016667f

#include "helpers2.h"

using namespace cv;



// get the homography from headplane to the screen
Mat getHomography(TRACKIRDATA headframe) {
	// construct four points in the x-y plane of the head frame
	vector<Point2f> pts_head;
	pts_head.push_back(Point2f(141, 131));
	// construct four points in the x-y plane of the screen frame
	vector<Point2f> pts_screen;

	Mat h = cv::findHomography(pts_head, pts_screen);
	return h;
}

Mat getRotationMatrix(TRACKIRDATA headframe) {
	double theta_x = headframe.fNPPitch / degrees;
	double theta_y = headframe.fNPYaw / degrees;
	double theta_z = headframe.fNPRoll / degrees;
	// Calculate rotation about x axis
    Mat R_x = (Mat_<double>(3,3) <<
               1,       0,              0,
               0,       cos(theta_x),   -sin(theta_x),
               0,       sin(theta_x),   cos(theta_x)
               );

    // Calculate rotation about y axis
    Mat R_y = (Mat_<double>(3,3) <<
               cos(theta_y),    0,      sin(theta_y),
               0,               1,      0,
               -sin(theta_y),   0,      cos(theta_y)
               );

    // Calculate rotation about z axis
    Mat R_z = (Mat_<double>(3,3) <<
               cos(theta_z),    -sin(theta_z),      0,
               sin(theta_z),    cos(theta_z),       0,
               0,               0,                  1);

    // Combined rotation matrix
    Mat R = R_z * R_y * R_x;
    return R;
}

Mat getTranslationMatrix(TRACKIRDATA headframe) {
	double x = headframe.fNPX;
	double y = headframe.fNPY;
	double z = headframe.fNPZ;
	// to transform a point (a, b, c), multiply (a, b, c, 1) by T
	Mat T = (Mat_<int>(4,4) <<
			 1, 0, 0, x,
			 0, 1, 0, y,
			 0, 0, 1, z,
			 0, 0, 0, 1);

	return T;
}
