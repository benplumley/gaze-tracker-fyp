#ifndef GAZETRACKER_H
#define GAZETRACKER_H

#include "DataCollector.h"
// #include "helpers2.h"
#include "EyeInterface.h"
class GazeTracker {
	private:
		void poll_loop(DataCollector dc, EyeInterface ei);
		void control_loop();
		void process_loop();
};


#endif
