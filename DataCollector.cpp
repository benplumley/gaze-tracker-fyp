#define _WIN32_WINNT _WIN32_WINNT_VISTA
#define _AFXDLL

#include "DataCollector.h"
#include <iostream>

using namespace std;

const LPTSTR dllPath = "C:\\Program Files (x86)\\NaturalPoint\\TrackIR5";
unsigned long NPFrameSignature;
unsigned long NPStaleFrames;

DataCollector::DataCollector(void) { // default constructor, initialise here
	TrackIR_Enhanced_Init();
}

DataCollector::~DataCollector(void) { // default destructor
	TrackIR_Enhanced_Shutdown();
}

void DataCollector::TrackIR_Enhanced_Shutdown( )
{

	// Request that the TrackIR software stop sending Tracking Data
	NP_StopDataTransmission();


	// Un-register your applications Windows Handle
	NP_UnregisterWindowHandle();
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

TRACKIRDATA DataCollector::client_HandleTrackIRData()
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

	return tid;
}

void DataCollector::recentre() {
	NPRESULT result = NP_ReCenter();
	if( NP_OK != result ) {
		std::cout << "Recentre failed" << '\n';
	} else {
		std::cout << "TrackIR recentred" << '\n';
	}
}
