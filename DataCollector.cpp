#include "sdk/NPClientWraps.cpp"
#include <iostream>

const LPTSTR dllPath = "C:\Program Files (x86)\NaturalPoint\TrackIR5";

class DataCollector {
	DataCollector() { // default constructor, initialise here
		NPRESULT result = NPClient_Init(dllPath);
		if (result == NP_OK) {
			cout << "TrackIR init success" << "\n";
		} else {
			cout << "TrackIR init failed" << "\n";
		}
	}
}
