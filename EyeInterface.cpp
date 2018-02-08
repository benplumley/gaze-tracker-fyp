#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <tchar.h>
#include <strsafe.h>
#include "EyeInterface.h"

std::string message_global;
HANDLE hSlot;
LPTSTR Slot = TEXT("\\\\.\\mailslot\\gazetrack_eyelike_mailslot");


// create a new type for our remote function
typedef EYELIKEDATA (__stdcall *f_eyelikeGetData)();

f_eyelikeGetData r_eyelikeGetData; // initialise a global name for the remote function

EYELIKEDATA origin;

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
}

// read all the messages in the mailslot to get the most recent
EYELIKEDATA EyeInterface::getData() {
	std::string message = message_global;
	EYELIKEDATA data;
	while (ReadSlot() == TRUE) {
		message = message_global;
	}
	const char * c = message.c_str();
	sscanf_s(c, "%d %d %d %d %d", &data.face_width, &data.right_eye.x, &data.right_eye.y, &data.left_eye.x, &data.left_eye.y);
	return data;
}

void EyeInterface::setOrigin() {
	origin = EyeInterface::getData();
	std::cout << "Origin left: " << origin.left_eye.x << " " << origin.left_eye.y << '\n';
}

cv::vector<cv::Point2f> EyeInterface::getOffset(cv::vector<cv::Point2f> eyepos) {
	cv::vector<cv::Point2f> offset;
	std::cout << "getOffset. eyepos[0].x = " << eyepos[0].x << '\n';
	offset.push_back(cv::Point2f(origin.left_eye.x - eyepos[0].x,
		 						 origin.left_eye.y - eyepos[0].y));
	offset.push_back(cv::Point2f(origin.right_eye.x - eyepos[1].x,
		 						 origin.right_eye.y - eyepos[1].y));
	// offset.push_back(cv::Point2f(eyepos[0].x - origin.left_eye.x,
	// 	 						 eyepos[0].y - origin.left_eye.y));
	// offset.push_back(cv::Point2f(eyepos[1].x - origin.right_eye.x,
	// 	 						 eyepos[1].y - origin.right_eye.y));
	return offset;
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
		return FALSE;
	}

	cAllMessages = cMessage;

	while (cMessage != 0)  // retrieve all messages
	{
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

		// _tprintf(TEXT("Contents of the mailslot: %s\n"), lpszBuffer);
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
