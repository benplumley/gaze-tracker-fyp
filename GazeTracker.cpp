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
std::mutex tid_mutex;
TRACKIRDATA tid_global;
EYELIKEDATA ei_global;

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
	while (!ending) {
		c = _getch();
		if (c==27) { // Escape pressed
			ending = true;
		}
	}
}

void process_loop() {
	TRACKIRDATA tid;
	CString t_str;
	CString e_str;
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



int main(int argc, char const *argv[]) {
	// GazeViewer gv;
	DataCollector dc;
	EyeInterface ei;
	std::thread poll;
	poll = std::thread(poll_loop, dc, ei);
	std::thread control;
	control = std::thread(control_loop);
	std::thread process;
	process = std::thread(process_loop);
	// threads run until Escape pressed
	poll.join();
	control.join();
	process.join();
}
