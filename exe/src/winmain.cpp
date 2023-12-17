#include "winmain.h"

#include "mainwindow.h"
#include "windarkmode.h"

HINSTANCE hinst;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
  hinst = hInstance;

  SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
  SetThreadDpiHostingBehavior(DPI_HOSTING_BEHAVIOR_MIXED);

  WinDarkMode::initDarkMode();

  MainWindow win;
  if (!win.create()) return 0;
  ShowWindow(win.getHwnd(), nCmdShow);

  // Run the message loop.
  MSG msg = {};
  while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return (int)msg.wParam;
}
