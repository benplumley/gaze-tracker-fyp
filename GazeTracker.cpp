#define _WIN32_WINNT _WIN32_WINNT_VISTA
#define _AFXDLL

#include <chrono>
#include <thread>
#include <conio.h>
#include <iostream>
#include <atomic>
#include <mutex>

#include "GazeTracker.h"

std::atomic_bool ending = false;
HANDLE next = CreateEvent(NULL, FALSE, FALSE, NULL); // auto-reset, starts unset
BOOL calibrate_c2_done = false;
std::mutex tid_mutex;
TRACKIRDATA tid_global;
EYELIKEDATA ei_global;

cv::Mat calibrate_c2() {
	cv::Mat H2;
	// TODO
	calibrate_c2_done = true;
	return H2;
}

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
		}
	}
}

void process_loop(EyeInterface ei) {
	TRACKIRDATA tid;
	CString t_str;
	CString e_str;
	cv::Mat R; // rotation matrix
	cv::Point3f T; // translation vector
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

			e_str.Format("width %d; left (%d, %d); right (%d, %d)",
						  ei_global.face_width,
						  ei_global.left_eye.x,
						  ei_global.left_eye.y,
						  ei_global.right_eye.x,
						  ei_global.right_eye.y);
			std::cout << e_str << '\n';
			R = getRotationMatrix(tid);
			T = getTranslationVector(tid);

			// Pick four arbitrary points (eg a unit square) in the face plane at calibration
			cv::vector<cv::Point2f> unitbefore;
			unitbefore.push_back(cv::Point2f(0, 0));
			unitbefore.push_back(cv::Point2f(0, 1));
			unitbefore.push_back(cv::Point2f(1, 0));
			unitbefore.push_back(cv::Point2f(1, 1));
			cv::vector<cv::Point2f> unitafter;

			// Multiply these points by the current rotation matrix and add the current translation
			cv::convertPointsToHomogeneous(unitbefore, unitafter);
			cv::transform(unitafter, unitafter, R); // rotation
			for each (cv::Point3f p in unitafter) { // translation
				p = p + T;
			}

			// Make both quads (before and after rotation+translation) homogeneous then discard z
			cv::convertPointsFromHomogeneous(unitafter, unitafter);

			// Use the four point pairs to get a homography H1 from the current face plane (after movement) to the face plane at calibration
			cv::Mat H1 = cv::findHomography(unitafter, unitbefore);

			// Multiply current eye position by H1 and compare to eye position at C1 to get eye offset
			cv::vector<cv::Point2f> eyepos;
			float lx, ly, rx, ry;
			lx = (float) ei_global.left_eye.x;
			ly = (float) ei_global.left_eye.y;
			rx = (float) ei_global.right_eye.x;
			ry = (float) ei_global.right_eye.y;
			eyepos.push_back(cv::Point2f(lx, ly));
			eyepos.push_back(cv::Point2f(rx, ry));
			cv::transform(eyepos, eyepos, H1);
			cv::vector<cv::Point2f> eyeOffset = ei.getOffset(eyepos);

			// Start calibration C2 if it's not already been done (ie this is the first loop iteration)
			cv::Mat H2;
			if (!calibrate_c2_done) {
				H2 = calibrate_c2();
			}

			// Multiply the eye offset by H2 to get a point on the screen
			cv::vector<cv::Point2f> screenCoords;
			cv::transform(eyeOffset, screenCoords, H2);

			// Multiply point on the screen by R and add T to account for head movement, then make homogeneous again because this might have moved the point in z
			cv::vector<cv::Point3f> screen3f;
			cv::convertPointsToHomogeneous(screenCoords, screen3f);
			cv::transform(screen3f, screen3f, R.inv()); // TODO inverse R here?
			for each (cv::Point3f p in screen3f) {
				p = p - T;
			}
			cv::convertPointsFromHomogeneous(screen3f, screenCoords);
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

	std::cout << "Calibration complete!" << '\n';
}

int main(int argc, char const *argv[]) {
	std::thread control;
	control = std::thread(control_loop);
	// GazeViewer gv;
	DataCollector dc;
	EyeInterface ei;
	calibrate(dc, ei);
	std::thread poll;
	poll = std::thread(poll_loop, dc, ei);
	std::thread process;
	process = std::thread(process_loop, ei);
	// threads run until Escape pressed
	poll.join();
	control.join();
	process.join();
}
