#include "DataCollector.cpp"
#include <chrono>
#include <thread>

// #include "sdk/NPTest.cpp"
// #include "sdk/NPTestDlg.cpp"

int main(int argc, char const *argv[]) {
	bool ending = false;
	DataCollector dc;
	// CAboutDlg np;
	TRACKIRDATA tid;
	NPRESULT result;
	while (ending != true) {
		result = dc.client_HandleTrackIRData();
		// std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		if (result == NP_OK) {
			std::cout << "Got trackIR data" << '\n';
		}
	}
}
