#include <string>
#include <windows.h>

HINSTANCE hInst;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
DWORD WinErrorMsg(const std::string function);
int CALLBACK wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
  PWSTR pCmdLine, int nCmdShow);

// extracted from Windows Kits\10\Include\10.0.18362.0\shared\windef.h
DECLARE_HANDLE(DPI_AWARENESS_CONTEXT);

// typedef enum DPI_AWARENESS {
//     DPI_AWARENESS_INVALID           = -1,
//     DPI_AWARENESS_UNAWARE           = 0,
//     DPI_AWARENESS_SYSTEM_AWARE      = 1,
//     DPI_AWARENESS_PER_MONITOR_AWARE = 2
// } DPI_AWARENESS;

#define DPI_AWARENESS_CONTEXT_UNAWARE               ((DPI_AWARENESS_CONTEXT)-1)
#define DPI_AWARENESS_CONTEXT_SYSTEM_AWARE          ((DPI_AWARENESS_CONTEXT)-2)
#define DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE     ((DPI_AWARENESS_CONTEXT)-3)
#define DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2  ((DPI_AWARENESS_CONTEXT)-4)
#define DPI_AWARENESS_CONTEXT_UNAWARE_GDISCALED     ((DPI_AWARENESS_CONTEXT)-5)

// extracted from Windows Kits\10\Include\10.0.18362.0\um\WinUser.h
WINUSERAPI
DPI_AWARENESS_CONTEXT
WINAPI
SetThreadDpiAwarenessContext(
    _In_ DPI_AWARENESS_CONTEXT dpiContext);
