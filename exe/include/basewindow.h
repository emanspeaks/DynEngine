#pragma once

#include "winmain.h"
#include "utf8/utf8.h"

#define SCALEFORDPI(dpi, i) (MulDiv((i), (dpi), 96))
#define UNSCALEFORDPI(dpi, i) (MulDiv((i), 96, (dpi)))

template <class DERIVED_TYPE> class BaseWindow {
  public:
    static LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
      DERIVED_TYPE *pThis = NULL;

      if (uMsg == WM_NCCREATE) {
        CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
        pThis = (DERIVED_TYPE*)pCreate->lpCreateParams;
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);
        pThis->m_hwnd = hwnd;
      } else pThis = (DERIVED_TYPE*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

      switch (uMsg) {
        case WM_DESTROY:
          pThis->clearFont();
          break;

        case WM_DPICHANGED:
          pThis->updateDpi(HIWORD(wParam), reinterpret_cast<RECT*>(lParam));
          break;

        default:
          break;
      }

      if (pThis) return pThis->onWm(uMsg, wParam, lParam);
      else return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    BaseWindow(): m_hwnd(NULL) {}

    BOOL create(
      const std::string& title = appName,
      DWORD dwStyle = WS_OVERLAPPEDWINDOW,
      DWORD dwExStyle = 0,
      int x = CW_USEDEFAULT,
      int y = CW_USEDEFAULT,
      int nWidth = CW_USEDEFAULT,
      int nHeight = CW_USEDEFAULT,
      HWND hWndParent = 0,
      HMENU hMenu = 0
    ) {
      WNDCLASSEX wcex = {};
      wcex.cbSize = sizeof(wcex);
      wcex.style = CS_HREDRAW | CS_VREDRAW;
      wcex.lpfnWndProc   = DERIVED_TYPE::WndProc;
      wcex.hInstance = hinst;
      wcex.hCursor = LoadCursorW(nullptr, IDC_ARROW);
      wcex.hbrBackground = (HBRUSH)(COLOR_3DFACE + 1);
      wcex.lpszClassName = className();

      RegisterClassEx(&wcex);

      m_hwnd = CreateWindowEx(
        dwExStyle, className(), utf8::widen(title).data(), dwStyle, x, y,
        nWidth, nHeight, hWndParent, hMenu, hinst, this
      );

      return (m_hwnd ? TRUE : FALSE);
    }

    HWND getHwnd() const {return m_hwnd;}

    void clearFont() {
      SendMessage(m_hwnd, WM_SETFONT, (WPARAM)nullptr, MAKELPARAM(FALSE, 0));
      DeleteObject(getFont());
    }

    void updateDpi(unsigned int dpi, RECT* newrect) {
      if (newrect != nullptr) SetWindowPos(m_hwnd, nullptr, newrect->left, newrect->top,
        newrect->right - newrect->left, newrect->bottom - newrect->top,
        SWP_NOZORDER | SWP_NOACTIVATE);

      updateLayoutAndFonts(dpi);
    }

  protected:
    HWND m_hwnd;

    virtual PCWSTR  className() const = 0;
    virtual LRESULT onWm(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
    virtual void updateLayoutAndFonts(unsigned int dpi) = 0;

    HFONT getFont() {
      return (HFONT)SendMessage(m_hwnd, WM_GETFONT, 0L, 0L);
    }

    unsigned int getDpi() {
      return GetDpiForWindow(m_hwnd);
    }

    void updateFonts(unsigned int dpi) {
      HFONT hfontold = getFont();
      LOGFONT font = {};
      SystemParametersInfoForDpi(SPI_GETICONTITLELOGFONT, sizeof(font), &font, FALSE, dpi);
      HFONT hfont = CreateFontIndirect(&font);
      if (hfont) {
        DeleteObject(hfontold);
        EnumChildWindows(m_hwnd, [](HWND hWnd, LPARAM lParam) -> BOOL {
          SendMessage(hWnd, WM_SETFONT, (WPARAM)lParam, MAKELPARAM(TRUE, 0));
          return TRUE;
        }, (LPARAM)hfont);
      }
    }
};
