#ifndef DATACOLLECTOR_H
#define DATACOLLECTOR_H

#include <string>
// #include "sdk/helpers.h"

#include "sdk/StdAfx.h"
#include "sdk/resource.h"
#include "sdk/NPClient.h"
#include "sdk/NPClientWraps.h"
#include "helpers2.h"

// class DataCollector;

class DataCollector {
	public:
		DataCollector();
		~DataCollector();
		TRACKIRDATA client_HandleTrackIRData();
	private:
		void DisplayLine(CString);
		void TrackIR_Enhanced_Init();
		void TrackIR_Enhanced_Shutdown();
};
// void DataCollector();
// TRACKIRDATA client_HandleTrackIRData();
// void DisplayLine(CString);
// void TrackIR_Enhanced_Init();
// void TrackIR_Enhanced_Shutdown();

#endif
