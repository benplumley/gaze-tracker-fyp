#include "sdk/NPClientWraps.cpp"
#include <iostream>

using namespace std;

const LPTSTR dllPath = "C:\\Program Files (x86)\\NaturalPoint\\TrackIR5";

class DataCollector {
	public:
		DataCollector();
};

DataCollector::DataCollector(void) { // default constructor, initialise here
	NPRESULT result = NPClient_Init(dllPath);
	if (result == NP_OK) {
		cout << "TrackIR init success" << "\n";
	} else {
		cout << "TrackIR init failed" << "\n";
		if (result == NP_ERR_DLL_NOT_FOUND) {
			cout << "NP_ERR_DLL_NOT_FOUND" << "\n"; // TODO currently returns this
		}
	}
}
