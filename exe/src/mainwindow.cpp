#include "winmain.h"
#include "mainwindow.h"
#include "windarkmode.h"

#define ID_CHKDARKMODE 1002
const std::string darkmodelabel = "Enable dark mode";
const int checkheight = 25;

LRESULT MainWindow::onWm(UINT uMsg, WPARAM wParam, LPARAM lParam) {
  switch (uMsg) {
    case WM_DESTROY:
      WinDarkMode::destroyDarkMode();
      PostQuitMessage(0);
      return 0;

    case WM_CTLCOLORSTATIC:
      return onWmCtlcolorstatic(reinterpret_cast<HDC>(wParam));

    case WM_CREATE:
      return onWmCreate();

    case WM_SETTINGCHANGE:
      return onWmSettingchange(lParam);

    case WM_THEMECHANGED:
      onWmThemechanged();
      break;

    case WM_COMMAND:
      onWmCommand(wParam);
      break;

    case WM_CLOSE:
      onWmClose();
      break;

    case WM_SIZE:
      updateLayoutAndFonts(getDpi());
	    break;

    case WM_ERASEBKGND:
      if (onWmErasebkgnd(reinterpret_cast<HDC>(wParam))) break;

    case WM_SHOWWINDOW:
      if (!lParam && m_firstload) {
        m_firstload = false;
      }

    default:
      return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
  }
  return TRUE;
}

bool MainWindow::onWmErasebkgnd(HDC hdc) {
  return (LRESULT)WinDarkMode::onWmErasebkgnd(m_hwnd, hdc);
}

void MainWindow::onWmThemechanged() {
  WinDarkMode::onWmThemechanged(m_hwnd);
}

LRESULT MainWindow::onWmSettingchange(LPARAM lParam) {
  return (LRESULT)WinDarkMode::onWmSettingchange(m_hwnd, lParam);
}

int MainWindow::calcStringWidth(std::string label) {
  const std::wstring wlabel = utf8::widen(label);
  // needs to be separate from line above so string is not destroyed
  return calcStringWidth(wlabel.data());
}

int MainWindow::calcStringWidth(const wchar_t *wclabel) {
  HDC hDC = GetDC(m_hwnd);
  RECT r;
  DrawText(hDC, wclabel, -1, &r, DT_CALCRECT | DT_NOPREFIX | DT_SINGLELINE);
  ReleaseDC(m_hwnd, hDC);
  return abs(r.right - r.left);
}

void MainWindow::updateLayoutAndFonts(unsigned int dpi) {
  HWND hwnd;
  RECT cr;

  const int xpad = 20;
  const int ypad = 20;
  const int buffer = 5;

	GetClientRect(m_hwnd, &cr);
  int maxwidth = UNSCALEFORDPI(dpi, cr.right - cr.left) - 2*xpad;
  int maxheight = UNSCALEFORDPI(dpi, cr.bottom - cr.top) - 2*ypad;

  int checkx = xpad;
  int checkwidth = 120;

  if ((hwnd = GetDlgItem(m_hwnd, ID_CHKDARKMODE)) == nullptr) return;
  SetWindowPos(hwnd, nullptr, SCALEFORDPI(dpi, checkx), SCALEFORDPI(dpi, ypad),
    SCALEFORDPI(dpi, checkwidth), SCALEFORDPI(dpi, checkheight), SWP_NOZORDER | SWP_NOACTIVATE);
  checkx += checkwidth + buffer;

  updateFonts(dpi);
  return;
}

void MainWindow::onWmCommand(WPARAM wParam) {
  switch(LOWORD(wParam)) {
    case ID_CHKDARKMODE:
      {
        switch (HIWORD(wParam)) {
          case BN_CLICKED:
            m_darkmode = !IsDlgButtonChecked(m_hwnd, ID_CHKDARKMODE);
            CheckDlgButton(m_hwnd, ID_CHKDARKMODE, m_darkmode);
            WinDarkMode::setWndAllowDarkMode(m_hwnd, m_darkmode);
            WinDarkMode::refreshWindowDarkMode(m_hwnd);
            break;
        }
      }
      break;
  }
}

LRESULT MainWindow::onWmCtlcolorstatic(HDC hdc) {
  return (LRESULT)WinDarkMode::onWmCtlcolor(m_hwnd, hdc);
}

void MainWindow::onWmClose() {
  if (utf8::MessageBox(m_hwnd, "Are you sure you want to exit?", appName, MB_OKCANCEL) == IDOK) {
    DestroyWindow(m_hwnd);
  }
}

LRESULT MainWindow::onWmCreate() {
  // dark mode checkbox/setup
  HWND hwnd;

  hwnd = CreateWindow(L"BUTTON", utf8::widen(darkmodelabel).data(),
    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
    0, 0, 0, 0, m_hwnd, (HMENU)ID_CHKDARKMODE, hinst, nullptr
  );
  if (hwnd == nullptr) return -1;
  CheckDlgButton(m_hwnd, ID_CHKDARKMODE, m_darkmode);
  WinDarkMode::setWndAllowDarkMode(m_hwnd, m_darkmode);
  WinDarkMode::refreshWindowDarkMode(m_hwnd);

  updateLayoutAndFonts(getDpi());

  return 0;
}
