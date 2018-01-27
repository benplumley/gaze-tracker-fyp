#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <tchar.h>
#include <strsafe.h>

struct EYE {
	int x;
	int y;
};

// struct EYELIKEDATA {
// 	int face_width;
// 	EYE left_eye;
// 	EYE right_eye;
// };

std::string message_global;
HANDLE hSlot;
LPTSTR Slot = TEXT("\\\\.\\mailslot\\gazetrack_eyelike_mailslot");

class EyeInterface {
	public:
		EyeInterface();
		struct EYELIKEDATA {
			int face_width;
			EYE left_eye;
			EYE right_eye;
		};
		EyeInterface::EYELIKEDATA getData();
};

// create a new type for our remote function
typedef EyeInterface::EYELIKEDATA (__stdcall *f_eyelikeGetData)();

f_eyelikeGetData r_eyelikeGetData; // initialise a global name for the remote function

BOOL ReadSlot();

BOOL WINAPI MakeSlot(LPTSTR lpszSlotName)
{
    hSlot = CreateMailslot(lpszSlotName,
        0,                             // no maximum message size
        MAILSLOT_WAIT_FOREVER,         // no time-out for operations
        (LPSECURITY_ATTRIBUTES) NULL); // default security

    if (hSlot == INVALID_HANDLE_VALUE)
    {
        printf("CreateMailslot failed with %d\n", GetLastError());
        return FALSE;
    }
    else printf("Mailslot created successfully.\n");
    return TRUE;
}

EyeInterface::EyeInterface(void) {
	MakeSlot(Slot);
	// HINSTANCE eyelikeproc = LoadLibrary("eyelike\\build\\Release\\eyelike.exe");
	// if (!eyelikeproc) {
	//     std::cout << "1Couldn't link eyelike.exe. Is it running?" << std::endl;
	//     return;
  	// }
	// // get the function from the other exe
	// r_eyelikeGetData = (f_eyelikeGetData)GetProcAddress(eyelikeproc, "eyelikeGetData");
	// if (!r_eyelikeGetData) {
	//     std::cout << "2Couldn't link eyelike.exe. Is it running?" << std::endl; // TODO errors here
	//     return;
  	// }
	// std::cout << "eyelike.exe linked successfully." << std::endl;
}

// read all the messages in the mailslot to get the most recent
EyeInterface::EYELIKEDATA EyeInterface::getData() {
	std::string message;
	EYELIKEDATA data;
	while (ReadSlot() == TRUE) {
		message = message_global;
	}
	// TODO convert string message into EYELIKEDATA to return
	// if (!r_eyelikeGetData) {
	// 	std::cout << "Attempted to call remote procedure but not linked to eyelike." << std::endl;
	// }
	// EyeInterface::EYELIKEDATA data = r_eyelikeGetData();
	// return data;
	return data;
}

BOOL ReadSlot() {
    DWORD cbMessage, cMessage, cbRead;
    BOOL fResult;
    LPTSTR lpszBuffer;
    TCHAR achID[80];
    DWORD cAllMessages;
    HANDLE hEvent;
    OVERLAPPED ov;

    cbMessage = cMessage = cbRead = 0;

    hEvent = CreateEvent(NULL, FALSE, FALSE, TEXT("ExampleSlot"));
    if( NULL == hEvent )
        return FALSE;
    ov.Offset = 0;
    ov.OffsetHigh = 0;
    ov.hEvent = hEvent;

    fResult = GetMailslotInfo( hSlot, // mailslot handle
        (LPDWORD) NULL,               // no maximum message size
        &cbMessage,                   // size of next message
        &cMessage,                    // number of messages
        (LPDWORD) NULL);              // no read time-out

    if (!fResult)
    {
        printf("GetMailslotInfo failed with %d.\n", GetLastError());
        return FALSE;
    }

    if (cbMessage == MAILSLOT_NO_MESSAGE)
    {
        printf("Waiting for a message...\n");
        return FALSE;
    }

    cAllMessages = cMessage;

    while (cMessage != 0)  // retrieve all messages
    {
        // Create a message-number string.

        StringCchPrintf((LPTSTR) achID,
            80,
            TEXT("\nMessage #%d of %d\n"),
            cAllMessages - cMessage + 1,
            cAllMessages);

        // Allocate memory for the message.

        lpszBuffer = (LPTSTR) GlobalAlloc(GPTR,
            lstrlen((LPTSTR) achID)*sizeof(TCHAR) + cbMessage);
        if( NULL == lpszBuffer )
            return FALSE;
        lpszBuffer[0] = '\0';

        fResult = ReadFile(hSlot,
            lpszBuffer,
            cbMessage,
            &cbRead,
            &ov);

        if (!fResult)
        {
            printf("ReadFile failed with %d.\n", GetLastError());
            GlobalFree((HGLOBAL) lpszBuffer);
            return FALSE;
        }

        // Concatenate the message and the message-number string.

        StringCbCat(lpszBuffer,
                    lstrlen((LPTSTR) achID)*sizeof(TCHAR)+cbMessage,
                    (LPTSTR) achID);

        // Display the message.

        _tprintf(TEXT("Contents of the mailslot: %s\n"), lpszBuffer);
		message_global = lpszBuffer;
        GlobalFree((HGLOBAL) lpszBuffer);

        fResult = GetMailslotInfo(hSlot,  // mailslot handle
            (LPDWORD) NULL,               // no maximum message size
            &cbMessage,                   // size of next message
            &cMessage,                    // number of messages
            (LPDWORD) NULL);              // no read time-out

        if (!fResult)
        {
            printf("GetMailslotInfo failed (%d)\n", GetLastError());
            return FALSE;
        }
    }
    CloseHandle(hEvent);
    return TRUE;
}
