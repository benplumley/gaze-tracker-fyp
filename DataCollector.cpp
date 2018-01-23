#include "sdk/NPClientWraps.cpp"
// #include "sdk/NPTest.h"
// #include "sdk/NPTestDlg.h"

#include <iostream>
#include <string>

using namespace std;

const LPTSTR dllPath = "C:\\Program Files (x86)\\NaturalPoint\\TrackIR5";

class DataCollector {
	public:
		DataCollector();
	private:
		void DisplayLine(CString);
		void TrackIR_Enhanced_Init();
};

DataCollector::DataCollector(void) { // default constructor, initialise here
	// NPRESULT result = NPClient_Init(dllPath);
	// if (result == NP_OK) {
	// 	cout << "TrackIR init success" << "\n";
	// } else {
	// 	cout << "TrackIR init failed" << "\n";
	// 	if (result == NP_ERR_DLL_NOT_FOUND) {
	// 		cout << "NP_ERR_DLL_NOT_FOUND" << "\n";
	// 		cout << "Is the TrackIR software running?" << "\n";
	// 	}
	// 	return;
	// }
	// result = NP_StartCursor();
	// if (result == NP_OK) {
	// 	cout << "Started TrackIR cursor" << "\n";
	// } else {
	// 	cout << "TrackIR cursor start failed" << "\n";
	// 	return;
	// }
	TrackIR_Enhanced_Init();
}

void DataCollector::DisplayLine(CString s) {
	std::cout << s << '\n';
}

// ************************************************************
// ***     TrackIR Enhanced SDK Initialization procedure    ***
// ***    This implementation uses the DLL wrapper module   ***
// ************************************************************
void DataCollector::TrackIR_Enhanced_Init() {

    NPRESULT result;

    // Zero TrackIR SDK Related counters
	unsigned long NPFrameSignature = 0;
	unsigned long NPStaleFrames = 0;

    // Initialize the the TrackIR Enhanced DLL
	result = NPClient_Init( dllPath );
	if( NP_OK == result )
		DisplayLine( "NPClient interface -- initialize OK." );
	else
		DisplayLine( "Error initializing NPClient interface!!" );


    // Register your applications Window Handle
	// result = NP_RegisterWindowHandle( GetSafeHwnd() );
	// if( NP_OK == result )
	// 	DisplayLine( "NPClient : Window handle registration successful." );
	// else
	// 	DisplayLine( "NPClient : Error registering window handle!!" );


	// Query for the NaturalPoint TrackIR software version
	unsigned short wNPClientVer;
	result = NP_QueryVersion( &wNPClientVer );
	if( NP_OK == result )
		{
		CString csMajorVer, csMinorVer, csVerMsg;
		csMajorVer.Format( "%d", (wNPClientVer >> 8) );
		csMinorVer.Format( "%02d", (wNPClientVer & 0x00FF) );
		csVerMsg.Format( "NaturalPoint software version is %s.%s", csMajorVer, csMinorVer );
		DisplayLine( csVerMsg );
		}
	else
		DisplayLine( "NPClient : Error querying NaturalPoint software version!!" );


    // Choose the Axes that you want tracking data for
	unsigned int DataFields = 0;

    // Rotation Axes
	DataFields |= NPPitch;
	DataFields |= NPYaw;
	DataFields |= NPRoll;

    // Translation Axes
	DataFields |= NPX;
	DataFields |= NPY;
	DataFields |= NPZ;

    // Register the Axes selection with the TrackIR Enhanced interface
	NP_RequestData(DataFields);


    // It is *required* that your application registers the Developer ID
    // assigned by NaturalPoint!

    // Your assigned developer ID needs to be inserted below!
    #define NP_DEVELOPER_ID 20135

    // NOTE : The title of your project must show up
    // in the list of supported titles shown in the Profiles
    // tab of the TrackIR software, if it does not then the
    // TrackIR software will *not* transmit data to your
    // application. If your title is not present in the list,
    // you may need to have the TrackIR software perform a
    // game list update (to download support for new Developer IDs)
    // using the menu item under the "Help" or "Update" menu.

    NP_RegisterProgramProfileID(NP_DEVELOPER_ID);


    // Stop the cursor
	result = NP_StopCursor();
	if (result == NP_OK)
		DisplayLine("Cursor stopped");
	else
		DisplayLine("NPClient : Error stopping cursor");


    // Request that the TrackIR software begins sending Tracking Data
	result = NP_StartDataTransmission();
	if (result == NP_OK)
		DisplayLine("Data transmission started");
	else
		DisplayLine("NPClient : Error starting data transmission");

}
