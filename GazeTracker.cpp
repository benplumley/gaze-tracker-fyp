#include "DataCollector.cpp"
#include <chrono>
#include <thread>
#include <conio.h>
#include <iostream>
#include <atomic>

std::atomic_bool ending = false;

class GazeTracker {
	private:
		void poll_loop();
		void control_loop();
};

void poll_loop() {
	DataCollector dc;
	TRACKIRDATA tid;
	NPRESULT result;
	while (!ending) {
		result = dc.client_HandleTrackIRData();
		// std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		if (result != NP_OK) {
			// std::cout << "Got trackIR data" << '\n';
			ending = true;
		}
	}
}

void control_loop() {
	char c;
	while (!ending) {
		c = getch();
        if (c==27) { // Escape pressed
			ending = true;
		}
	}
}

int main(int argc, char const *argv[]) {
	std::thread poll;
	poll = std::thread(poll_loop);
	std::thread control;
	control = std::thread(control_loop);
	// both threads run until Escape pressed
	poll.join();
	control.join();
}
