#include <locale>
#include <codecvt>
#include "windows_strings.h"

// following code adapted from:
// https://ryanclouser.com/2016/08/11/C-11-Convert-to-from-UTF-8-wchar-t/
std::string narrow(const std::wstring &wstr)
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t, 0x10ffff,
    std::codecvt_mode::little_endian>, wchar_t> convert;
	return convert.to_bytes(wstr);
}

std::wstring widen(const std::string &str)
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t, 0x10ffff,
    std::codecvt_mode::little_endian>, wchar_t> convert;
  std::wstring wstr(convert.from_bytes(str));
  // wchar_t* out = new wchar_t[wstr.length()];
	// return wcscpy(out, wstr.c_str());
  return wstr;
}
