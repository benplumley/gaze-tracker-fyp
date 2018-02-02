#include <windows.h>
#include <winuser.h>
// #include "eyelike/objdetect.hpp"
#include "eyelike/highgui.hpp"
#include "eyelike/imgproc.hpp"

class GazeViewer {
	public:
		GazeViewer();
};

GazeViewer::GazeViewer() {
	// HINSTANCE hinst;
	// HWND hwndMain;
    //
	// // Create the main window.
    //
	// hwndMain = CreateWindowEx(
	//     0,                      // no extended styles
	//     "GazeViewer",           // class name
	//     "Main Window",          // window name
	//     WS_OVERLAPPEDWINDOW,	// overlapped window
	//     CW_USEDEFAULT,          // default horizontal position
	//     CW_USEDEFAULT,          // default vertical position
	//     CW_USEDEFAULT,          // default width
	//     CW_USEDEFAULT,          // default height
	//     (HWND) NULL,            // no parent or owner window
	//     (HMENU) NULL,           // class menu used
	//     hinst,             		// instance handle
	//     NULL);                  // no window creation data
    //
	// if (!hwndMain)
	//     std::cout << "Failed to create GazeViewer window" << '\n';

	// Show the window using the flag specified by the program
	// that started the application, and send the application
	// a WM_PAINT message.

	// HWND hWnd = CreateWindowEx(WS_EX_LAYERED|WS_EX_TRANSPARENT, Static, "Main Window", NULL, 0, 0, 640, 480, NULL, 0, GetModuleHandle(NULL), 0);

	// ShowWindow(hWnd, SW_SHOWDEFAULT);
	// UpdateWindow(hWnd);
}

void SetSplashImage(HWND hwndSplash, HBITMAP hbmpSplash)
{
    // get the size of the bitmap
    BITMAP bm;
    GetObject(hbmpSplash, sizeof(bm), &bm);
    SIZE sizeSplash = { bm.bmWidth, bm.bmHeight };

    // get the primary monitor's info
    POINT ptZero = { 0 };
    HMONITOR hmonPrimary = MonitorFromPoint(ptZero, MONITOR_DEFAULTTOPRIMARY);
    MONITORINFO monitorinfo = { 0 };
    monitorinfo.cbSize = sizeof(monitorinfo);
    GetMonitorInfo(hmonPrimary, &monitorinfo);

    // center the splash screen in the middle of the primary work area
    const RECT & rcWork = monitorinfo.rcWork;
    POINT ptOrigin;
    ptOrigin.x = rcWork.left + (rcWork.right - rcWork.left - sizeSplash.cx) / 2;
    ptOrigin.y = rcWork.top + (rcWork.bottom - rcWork.top - sizeSplash.cy) / 2;

    // create a memory DC holding the splash bitmap
    HDC hdcScreen = GetDC(NULL);
    HDC hdcMem = CreateCompatibleDC(hdcScreen);
    HBITMAP hbmpOld = (HBITMAP) SelectObject(hdcMem, hbmpSplash);

    // use the source image's alpha channel for blending
    BLENDFUNCTION blend = { 0 };
    blend.BlendOp = AC_SRC_OVER;
    blend.SourceConstantAlpha = 255;
    blend.AlphaFormat = AC_SRC_ALPHA;

    // paint the window (in the right location) with the alpha-blended bitmap
    UpdateLayeredWindow(hwndSplash, hdcScreen, &ptOrigin, &sizeSplash,
        hdcMem, &ptZero, RGB(0, 0, 0), &blend, ULW_ALPHA);

    // delete temporary objects
    SelectObject(hdcMem, hbmpOld);
    DeleteDC(hdcMem);
    ReleaseDC(NULL, hdcScreen);
}
