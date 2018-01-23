#include "sdk/NPClientWraps.cpp"
// #include "sdk/NPTest.h"
// #include "sdk/NPTestDlg.h"

#include <iostream>
#include <string>
// #include <CWnd>

using namespace std;

const LPTSTR dllPath = "C:\\Program Files (x86)\\NaturalPoint\\TrackIR5";
unsigned long NPFrameSignature;
unsigned long NPStaleFrames;

class DataCollector {
	public:
		DataCollector();
		NPRESULT client_HandleTrackIRData();
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
	NPFrameSignature = 0;
	NPStaleFrames = 0;

    // Initialize the the TrackIR Enhanced DLL
	result = NPClient_Init( dllPath );
	if( NP_OK == result )
		DisplayLine( "NPClient interface -- initialize OK." );
	else
		DisplayLine( "Error initializing NPClient interface!!" );


    // Register your applications Window Handle
	HWND handle;
	handle=FindWindowA(NULL, "Windows PowerShell"); // TODO name the window something a bit more unique
	result = NP_RegisterWindowHandle( handle );
	if( NP_OK == result )
		DisplayLine( "NPClient : Window handle registration successful." );
	else
		DisplayLine( "NPClient : Error registering window handle!!" );


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
    #define NP_DEVELOPER_ID 20135
    NP_RegisterProgramProfileID(NP_DEVELOPER_ID);
    // NP_RegisterProgramProfileID(20135);


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


	// Start the cursor
	result = NP_StartCursor();
	if (result == NP_OK)
		DisplayLine("Cursor started");
	else
		DisplayLine("NPClient : Error starting cursor");
}

NPRESULT DataCollector::client_HandleTrackIRData()
{
	TRACKIRDATA tid;
    CString csDataRxMsg;
	CString t_str;

    // Query the TrackIR Enhanced Interface for the latest data
	NPRESULT result = NP_GetData( &tid );

    // If the call succeeded, then we have data to process
	if( NP_OK == result )
	{
        // Make sure the remote interface is active
		if (tid.wNPStatus == NPSTATUS_REMOTEACTIVE)
		{
            // Compare the last frame signature to the current one if
            // they are not the same then the data is new
			if (true)
			// if (NPFrameSignature != tid.wPFrameSignature)
			{

                // In your own application, this is where you would utilize
                // the Tracking Data for View Control / etc.

				// Display the Tracking Data
				t_str.Format( "Rotation : NPPitch = %04.02f, NPYaw = %04.02f, NPRoll = %04.02f \r\nTranslation : NPX = %04.02f, NPY = %04.02f, NPZ = %04.02f \r\nInformation NPStatus = %d, Frame = %d",
                               tid.fNPPitch,
                               tid.fNPYaw,
                               tid.fNPRoll,
                               tid.fNPX,
                               tid.fNPY,
                               tid.fNPZ,
                               tid.wNPStatus,
                               tid.wPFrameSignature );
				DisplayLine(t_str);
				NPFrameSignature = tid.wPFrameSignature;
				NPStaleFrames = 0;

				//
				// All other data fields in TRACKIRDATA can be handled in a similar way.
				//
			}
			else
			{
				// Either there is no tracking data, the user has
				// paused the trackIR, or the call happened before
				// the TrackIR was able to update the interface
				// with new data

				if (NPStaleFrames > 30)
				{
					t_str.Format("No New Data. Paused or Not Tracking?", NPStaleFrames);
				}
				else
				{
                    NPStaleFrames++;
					t_str.Format("No New Data for %d frames", NPStaleFrames);
				}
				DisplayLine(t_str);
				result = NP_ERR_NO_DATA;
			}
		}
		else
		{
			// The user has set the device out of trackIR Enhanced Mode
			// and into Mouse Emulation mode with the hotkey
			t_str.Format("User Disabled");
			DisplayLine(t_str);
			result = NP_ERR_NO_DATA;
		}

	}

	return result;
}
