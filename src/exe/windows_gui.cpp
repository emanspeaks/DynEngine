#include "dynenginelib.h"
#include "gui.h"
#include "windows_gui.h"
#include "windows_strings.h"

int CALLBACK wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
  PWSTR pCmdLine, int nCmdShow)
{
  // Store instance handle in our global variable
  hInst = hInstance;

  //#ifndef MINGW
  SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE);
  //#endif

  // this is just for testing the WinErrorMsg function
  //if(!GetProcessId(NULL)) WinErrorMsg("GetProcessId");

  std::wstring wWindowClass = widen(windowClass);
  std::wstring wWindowTitle = widen(windowTitle);
  const wchar_t* szWindowClass = wWindowClass.c_str();
  const wchar_t* szTitle = wWindowTitle.c_str();

  WNDCLASSEXW wcex;
  wcex.cbSize = sizeof(WNDCLASSEXW);
  wcex.style = CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc = WndProc;
  wcex.cbClsExtra = 0;
  wcex.cbWndExtra = 0;
  wcex.hInstance = hInstance;
  wcex.hIcon = LoadIconW(hInstance, IDI_APPLICATION);
  wcex.hCursor = LoadCursorW(NULL, IDC_ARROW);
  wcex.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
  wcex.lpszMenuName = NULL;
  wcex.lpszClassName = szWindowClass;
  wcex.hIconSm = LoadIconW(wcex.hInstance, IDI_APPLICATION);
  if (!RegisterClassExW(&wcex))
  {
    MessageBoxW(NULL, L"Call to RegisterClassEx failed!", szTitle,
      MB_ICONEXCLAMATION | MB_OK);
    return 1;
  }

  HWND hWnd = CreateWindowW(szWindowClass, szTitle,
    WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1500, 1000, NULL, NULL,
    hInstance, NULL);
  if (!hWnd)
  {
    MessageBoxW(NULL, L"Call to CreateWindow failed!", szTitle,
      MB_ICONEXCLAMATION | MB_OK);
    return 1;
  }
  ShowWindow(hWnd, nCmdShow);
  UpdateWindow(hWnd);

  // Main message loop:
  MSG msg;
  BOOL ret;
  while (ret = GetMessageW(&msg, NULL, 0, 0))
  {
    if (ret > 0)
    {
      TranslateMessage(&msg);
      DispatchMessageW(&msg);
    }
    else return WinErrorMsg("GetMessage");
  }

  return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  PAINTSTRUCT ps;
  HDC hdc;
  std::wstring greeting;
  const wchar_t* greetingptr;

  switch (message)
  {
    case WM_PAINT:
      hdc = BeginPaint(hWnd, &ps);
      greeting = widen(get_window_message());
      greetingptr = greeting.c_str();
      TextOutW(hdc, 5, 5, greetingptr, wcslen(greetingptr));
      EndPaint(hWnd, &ps);
      break;

    case WM_CLOSE:
      DestroyWindow(hWnd);
       break;

    case WM_DESTROY:
      PostQuitMessage(0);
      break;

    default:
      return DefWindowProcW(hWnd, message, wParam, lParam);
      break;
  }

  return 0;
}

DWORD WinErrorMsg(const std::string function)
{
  std::string displaymsg(function);
  displaymsg += " failed with error ";
  DWORD errorcode = GetLastError();
  displaymsg += std::to_string(errorcode);
  wchar_t* errmsg = NULL;
  DWORD errmsglen = FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER
    | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL,
    errorcode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPWSTR)&errmsg, 0,
    NULL);
  if (errmsglen)
  {
    displaymsg += ": ";
    displaymsg += narrow(errmsg);
  }
  MessageBoxW(NULL, widen(displaymsg).c_str(), widen(windowTitle).c_str(),
    MB_OK);
  LocalFree(errmsg);
  return errorcode;
}
