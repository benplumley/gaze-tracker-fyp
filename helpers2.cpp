#define _WIN32_WINNT _WIN32_WINNT_VISTA
#define _AFXDLL

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

Mat getTranslationMatrix3f(TRACKIRDATA headframe) {
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

// Mat getTranslationMatrix2f(TRACKIRDATA headframe) {
// 	double x = headframe.fNPX;
// 	double y = headframe.fNPY;
// 	// to transform a point (a, b, c), multiply (a, b, c, 1) by T
// 	Mat T = (Mat_<int>(4,4) <<
// 			 1, 0, 0, x,
// 			 0, 1, 0, y,
// 			 0, 0, 1, z,
// 			 0, 0, 0, 1);
//
// 	return T;
// }

Mat getTranslationMatrixA(TRACKIRDATA headframe) {
	double x = headframe.fNPX;
	double y = headframe.fNPY;
	double z = headframe.fNPZ;
	// to transform a point (a, b, c), add (a, b, c) to T
	Mat T = (Mat_<int>(4,3) <<
			 x, y, z,
		 	 x, y, z,
			 x, y, z,
			 x, y, z);

	return T;
}

Point3f getTranslationVector(TRACKIRDATA headframe) {
	double x = headframe.fNPX;
	double y = headframe.fNPY;
	double z = headframe.fNPZ;
	// to transform a point (a, b, c), add (a, b, c) to T
	Point3f T = Point3f(x, y, z);

	return T;
}

Mat makeHomogeneous(Mat m, int rowno, int colno) {
	if (rowno >= 0) {
		m = m / m.row(rowno);
	} else if (colno >= 0) {
		m = m / m.col(colno);
	}
	return m;
}
