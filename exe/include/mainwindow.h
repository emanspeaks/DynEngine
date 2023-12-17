#pragma once

#include "basewindow.h"

class MainWindow : public BaseWindow<MainWindow> {
  public:
    MainWindow(): m_darkmode(true), m_firstload(true) {}

    PCWSTR className() const {return L"Main Window";}
    LRESULT onWm(UINT uMsg, WPARAM wParam, LPARAM lParam);
    void updateLayoutAndFonts(unsigned int dpi);

  private:
    bool m_darkmode, m_firstload;

    LRESULT onWmCreate();
    void onWmClose();
    LRESULT onWmCtlcolorstatic(HDC hdc);
    void onWmCommand(WPARAM wParam);
    LRESULT onWmSettingchange(LPARAM lParam);
    void onWmThemechanged();
    bool onWmErasebkgnd(HDC hdc);

    int calcStringWidth(std::string label);
    int calcStringWidth(const wchar_t *label);
};
