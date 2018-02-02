#ifndef DATACOLLECTOR_H
#define DATACOLLECTOR_H

#include <string>
#include "sdk/StdAfx.h"
#include "sdk/resource.h"
#include "sdk/NPClient.h"
#include "sdk/NPClientWraps.h"
#include "helpers2.h"

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

#endif
