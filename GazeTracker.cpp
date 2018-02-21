#define _WIN32_WINNT _WIN32_WINNT_VISTA
#define _AFXDLL

#include <chrono>
#include <thread>
#include <conio.h>
#include <iostream>
#include <atomic>
#include <mutex>

#include "GazeTracker.h"
// #include "gaze_calc/main.h"

#include "gaze_calc/rt_nonfinite.h"
#include "gaze_calc/gaze_calc.h"
// #include "gaze_calc/main.h"
#include "gaze_calc/gaze_calc_terminate.h"
#include "gaze_calc/gaze_calc_initialize.h"

std::atomic_bool ending = false;
HANDLE next = CreateEvent(NULL, FALSE, FALSE, NULL); // auto-reset, starts unset
bool calibrate_done = false;
std::mutex tid_mutex;
TRACKIRDATA tid_global;
EYELIKEDATA ei_global;
cv::vector<cv::Point2f> eyeOffset_global;
cv::Mat H2l, H2r;

// cv::Mat calibrate_corner(cv::vector<cv::Point2f> eyeOffset) {
// 	cv::Mat H2l;
// 	std::cout << "Look at the top-left corner of the monitor and press Enter." << '\n';
// 	WaitForSingleObject(next, INFINITE);
// 	std::cout << "Look at the top-right corner of the monitor and press Enter." << '\n';
// 	WaitForSingleObject(next, INFINITE);
// 	std::cout << "Look at the bottom-left corner of the monitor and press Enter." << '\n';
// 	WaitForSingleObject(next, INFINITE);
// 	std::cout << "Look at the bottom-right corner of the monitor and press Enter." << '\n';
// 	WaitForSingleObject(next, INFINITE);
// 	// TODO
// 	H2l = cv::Mat::eye(2, 2, CV_32F); // TODO temporary, remove later
// 	calibrate_corner_done = true;
// 	return H2l;
// }

void poll_loop(DataCollector dc, EyeInterface ei) {
	TRACKIRDATA tid_temp = tid_global;
	while (!ending) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1)); // loops faster than polling rate, wasting CPU
		tid_temp = dc.client_HandleTrackIRData();
		{
			std::lock_guard<std::mutex> lock(tid_mutex); // lock tid to write it
			tid_global = tid_temp;
		} // tid_mutex is unlocked when it passes out of this scope
		ei_global = ei.getData(); // non-blocking, returns the most recent value
	}
}

void control_loop() {
	char c;
	while (!ending && (c = _getch())) { // until ending or EOF
		switch (c) {
			case 27: // Escape pressed
				ending = true;
				break;
			case 13: // Enter pressed
				SetEvent(next);
				break;
			case 114: // r pressed
				// calibrate_corner_done = 0; // trigger recalibration TODO
				break;
		}
	}
}

void process_loop(EyeInterface ei) {
	TRACKIRDATA tid;
	CString t_str;
	CString e_str;
	cv::Mat R; // rotation matrix
	cv::Point3f T; // translation vector
	cv::Mat H1, H2l;
	unsigned long NPFrameSignature = 0;
	unsigned long NPStaleFrames = 0;
	while (!ending) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1)); // loops faster than polling rate, wasting CPU
		{
			std::lock_guard<std::mutex> lock(tid_mutex); // lock tid to read it
			tid = tid_global;
		} // tid_mutex is unlocked when it passes out of this scope

		// Compare the last frame signature to the current one if
		// they are not the same then the data is new
		if (NPFrameSignature != tid.wPFrameSignature) {
			std::cout << "debug 1" << '\n';
			t_str.Format("[%d] translation cm (%04.02f, %04.02f, %04.02f); rotation deg (%04.02f, %04.02f, %04.02f)",
						  tid.wPFrameSignature,
						  tid.fNPX / centimetres,
						  tid.fNPY / centimetres,
						  tid.fNPZ / centimetres,
						  tid.fNPPitch / degrees,
						  tid.fNPYaw / degrees,
						  tid.fNPRoll / degrees
						);
			std::cout << t_str << '\n';
			NPFrameSignature = tid.wPFrameSignature;
			NPStaleFrames = 0;
			std::cout << "debug 2" << '\n';
			e_str.Format("width %d; left (%d, %d); right (%d, %d)",
						  ei_global.face_width,
						  ei_global.left_eye.x,
						  ei_global.left_eye.y,
						  ei_global.right_eye.x,
						  ei_global.right_eye.y);
			std::cout << e_str << '\n';
			std::cout << "debug 3" << '\n';
			int x = 5;
			double retmat[4] = {0.0f, 0.0f, 0.0f, 0.0f};
			double head_x = tid.fNPX / centimetres;
			double head_y = tid.fNPY / centimetres;
			double head_z = tid.fNPZ / centimetres;
			double head_roll = tid.fNPRoll / degrees;
			double head_pitch = tid.fNPPitch / degrees;
			double head_yaw = tid.fNPYaw / degrees;
			double left_eye_x = ei_global.left_eye.x;
			double left_eye_y = ei_global.left_eye.y;
			double right_eye_x = ei_global.right_eye.x;
			double right_eye_y = ei_global.right_eye.y;
			std::cout << "debug 4" << '\n';
			gaze_calc(head_x,
					  head_y,
					  head_z,
					  head_roll,
					  head_pitch,
					  head_yaw,
					  left_eye_x,
					  left_eye_y,
					  right_eye_x,
					  right_eye_y,
				  	  retmat);

			std::cout << "debug 4.1" << '\n';
			cv::vector<cv::Point2f> screenCoords;
			screenCoords.push_back(cv::Point2f(retmat[0], retmat[1]));
			screenCoords.push_back(cv::Point2f(retmat[2], retmat[3]));
			// screenCoords[0].x = retmat[0];
			// screenCoords[0].y = retmat[1];
			// screenCoords[1].x = retmat[2];
			// screenCoords[1].y = retmat[3];
			std::cout << "debug 5" << '\n';


			// R = getRotationMatrix(tid);
			// T = getTranslationVector(tid);
			// // Pick four arbitrary points (eg a unit square) in the face plane at calibration
			// cv::vector<cv::Point2f> unitbefore;
			// unitbefore.push_back(cv::Point2f(0, 0));
			// unitbefore.push_back(cv::Point2f(0, 1));
			// unitbefore.push_back(cv::Point2f(1, 0));
			// unitbefore.push_back(cv::Point2f(1, 1));
			// cv::vector<cv::Point3f> unit3f;
			//
			// // Multiply these points by the current rotation matrix and add the current translation
			// cv::convertPointsToHomogeneous(unitbefore, unit3f);
			// cv::transform(unit3f, unit3f, R); // rotation
			// for each (cv::Point3f p in unit3f) { // translation
			// 	p = p + T;
			// }
			//
			// // Make both quads (before and after rotation+translation) homogeneous then discard z
			// cv::vector<cv::Point2f> unitafter;
			// cv::convertPointsFromHomogeneous(unit3f, unitafter);
			//
			// // Use the four point pairs to get a homography H1 from the current face plane (after movement) to the face plane at calibration
			// H1 = cv::findHomography(unitafter, unitbefore);
			//
			// // Multiply current eye position by H1 and compare to eye position at C1 to get eye offset
			// cv::vector<cv::Point2f> eyepos;
			// float lx, ly, rx, ry;
			// lx = (float) ei_global.left_eye.x;
			// ly = (float) ei_global.left_eye.y;
			// rx = (float) ei_global.right_eye.x;
			// ry = (float) ei_global.right_eye.y;
			// eyepos.push_back(cv::Point2f(lx, ly));
			// eyepos.push_back(cv::Point2f(rx, ry));
			//
			// cv::convertPointsToHomogeneous(eyepos, unit3f);
			// cv::transform(unit3f, unit3f, H1);
			// cv::convertPointsFromHomogeneous(unit3f, eyepos);
			// // cv::vector<cv::Point2f> eyeOffset = ei.getOffset(eyepos);
			// cv::vector<cv::Point2f> eyeOffset = eyepos;
			//
			// // Start calibration C2 if it's not already been done (ie this is the first loop iteration)
			// if (!calibrate_done) {
			// 	eyeOffset_global = eyeOffset; // TODO protect with a mutex
			// 	continue; // don't try to display position on screen if calibration isn't done
			// }
			//
			// // if (calibrate_corner_done < 4) {
			// // 	bool first_pass = true;
			// // 	if (calibrate_corner_done == 0) {
			// // 		// calibrate top left corner
			// // 		if (first_pass) {
			// // 			std::cout << "Look at the top-left corner of the monitor and press Enter." << '\n';
			// // 			WaitForSingleObject(next, INFINITE);
			// // 			continue; // jump back to the start to get the eye position now they're looking in the right spot
			// // 		}
			// // 		first_pass = false;
			// // 		calibrate_corner()
			// // 	}
			// // 	H2l = calibrate_corner(eyeOffset);
			// // }
			//
			// // Multiply the eye offset by H2l to get a point on the screen
			// cv::vector<cv::Point2f> screenCoords;
			// cv::vector<cv::Point3f> screen3f;
			// cv::vector<cv::Point3f> eye3f;
			// screenCoords.push_back(cv::Point2f(0.0f, 0.0f));
			// screenCoords.push_back(cv::Point2f(0.0f, 0.0f));
			// // cv::Mat screenCoordsMat = new cv::Mat(4,2);
			// // screenCoordsMat = screenCoords;
			// cv::convertPointsToHomogeneous(eyeOffset, eye3f);
			// // cv::transform(eyeOffset, screenCoords, H2l);
			// std::cout << "debug 1" << '\n';
			// std::cout << "eyeOffset = "<< '\n' << " "  << eyeOffset << '\n';
			// std::cout << "screenCoords = "<< '\n' << " "  << screenCoords << '\n';
			// // cv::transform(eye3f, screen3f, H2l); // TODO errors here, even when H2l is full
			// // screen3f[0] = eye3f[0] * H2l;
			// // screen3f[1] = eye3f[1] * H2l;
			// cv::Mat eye3fMat = cv::Mat(eye3f);
			// cv::Mat screen3fMat;
			// std::cout << "eye3fMat = " << eye3fMat << '\n';
			//
			// H2l.convertTo(H2l, CV_32F);
			// eye3fMat.convertTo(eye3fMat, CV_32FC1);
			//
			// eye3fMat.mul(H2l);
			// screen3fMat = eye3fMat;
			// screen3f.push_back(cv::Point3f(screen3fMat.at<float>(0,0),
			// 							   screen3fMat.at<float>(0,1),
			// 							   screen3fMat.at<float>(0,2)));
			// screen3f.push_back(cv::Point3f(screen3fMat.at<float>(1,0),
			// 							   screen3fMat.at<float>(1,1),
			// 							   screen3fMat.at<float>(1,2)));
			//
			// // Multiply point on the screen by R and add T to account for head movement, then make homogeneous again because we moved the point in z
			// // cv::convertPointsToHomogeneous(screenCoords, screen3f);
			// std::cout << "debug 2" << '\n';
			// cv::transform(screen3f, screen3f, R.inv()); // TODO inverse R here?
			// for each (cv::Point3f p in screen3f) {
			// 	p = p - T;
			// }
			// cv::convertPointsFromHomogeneous(screen3f, screenCoords);

			CString s_str;
			s_str.Format("Left (%04.02f, %04.02f) Right (%04.02f, %04.02f)", screenCoords[0].x, screenCoords[0].y, screenCoords[1].x, screenCoords[1].y);
			std::cout << s_str << '\n';
			std::cout << "debug 6" << '\n';
			// gv.draw_point(screenCoords[0]);
			// gv.draw_point(screenCoords[1]);
		} else {
			// Either there is no tracking data, the user has paused the
			// trackIR, or the call happened before the TrackIR was able to
			// update the interface with new data
			if (NPStaleFrames == 30) {
				std::cout << "No target." << '\n';
			}
			NPStaleFrames++;
		}
	}
}

// void calibrate(DataCollector dc, EyeInterface ei) {
void calibrate(DataCollector dc, EyeInterface ei) {
	std::cout << "Press Enter to begin calibration procedure." << '\n';
	WaitForSingleObject(next, INFINITE);
	// gv.draw_point(screen centre);
	std::cout << "Press Enter while looking at the point in the centre of the screen." << '\n';
	WaitForSingleObject(next, INFINITE);
	// centre the TrackIR using its built-in centre function
	dc.recentre();

	// centre the EyeInterface by saving the current position as the origin
	ei.setOrigin();

	cv::vector<cv::Point2f> eyeOffset;
	cv::vector<cv::Point2f> leftEyeOffsets;
	cv::vector<cv::Point2f> rightEyeOffsets;
	cv::vector<cv::Point2f> calibrationPoints;

	calibrationPoints.push_back(cv::Point2f(0.0f,0.0f));
	calibrationPoints.push_back(cv::Point2f(1920.0f,0.0f));
	calibrationPoints.push_back(cv::Point2f(0.0f,1080.0f));
	calibrationPoints.push_back(cv::Point2f(1920.0f,1080.0f)); // TODO read screen size
	// leftEyeOffsets.push_back(cv::Point2f(0,0));
	// leftEyeOffsets.push_back(cv::Point2f(-100,-100));
	// leftEyeOffsets.push_back(cv::Point2f(100,-100));
	// leftEyeOffsets.push_back(cv::Point2f(-100,100));
	// leftEyeOffsets.push_back(cv::Point2f(100,100));
	CString instruction;
	for each (cv::Point2f screenPoint in calibrationPoints) {
		instruction.Format("Look at %04.0f, %04.0f and press Enter.", screenPoint.x, screenPoint.y);
		std::cout << instruction << '\n';
		// gv.draw_point(screenPoint); TODO
		WaitForSingleObject(next, INFINITE);
		eyeOffset = eyeOffset_global; // TODO protect with a mutex
		leftEyeOffsets.push_back(eyeOffset[0]);
		std::cout << "left eye offset = "<< '\n' << " "  << eyeOffset[0] << '\n';
		rightEyeOffsets.push_back(eyeOffset[1]);
	}
	// leftEyeOffsets.push_back(cv::Point2f(0,0));
	// calibrationPoints.push_back(cv::Point2f(960,540));
	H2l = cv::findHomography(leftEyeOffsets, calibrationPoints, CV_RANSAC); // TODO test whether H2l actually got filled, retry if not - will crash later otherwise
	H2r = cv::findHomography(rightEyeOffsets, calibrationPoints, CV_RANSAC); // TODO test whether H2r actually got filled, retry if not - will crash later otherwise
	std::cout << "H2l has rows x cols " << H2l.rows << " x " << H2l.cols << '\n';
	std::cout << "H2l = "<< '\n' << " "  << H2l << '\n';
	calibrate_done = true;
	std::cout << "Calibration complete!" << '\n';
	while (!ending) {
		// TODO find a better way to wait
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}

int main(int argc, char const *argv[]) {
	gaze_calc_initialize();
	std::thread control;
	control = std::thread(control_loop);
	// GazeViewer gv;
	DataCollector dc;
	EyeInterface ei;
	// calibrate(dc, ei); // TODO causes dc to not return updated values because the destructor is called when it passes out of scope
	std::thread poll;
	poll = std::thread(poll_loop, dc, ei);
	std::thread process;
	process = std::thread(process_loop, ei);
	// std::thread calibrate_thread;
	// calibrate_thread = std::thread(calibrate, dc, ei);
	// threads run until Escape pressed
	// calibrate_thread.join();
	poll.join();
	control.join();
	process.join();
	gaze_calc_terminate();
}
