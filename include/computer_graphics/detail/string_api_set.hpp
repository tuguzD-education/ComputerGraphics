#pragma once

#ifndef DETAIL_STRING_API_SET_HPP_INCLUDED
#define DETAIL_STRING_API_SET_HPP_INCLUDED

#include <windows.h>

#include <string>

namespace computer_graphics::detail {

std::wstring MultiByteToWideChar(
    UINT code_page, DWORD dw_flags, std::string_view view
);

std::string WideCharToMultiByte(
    UINT code_page, DWORD dw_flags, std::wstring_view view,
    const char *default_char = nullptr,
    bool *used_default_char = nullptr
);

std::basic_string<TCHAR> MultiByteToTChar(
    [[maybe_unused]] UINT code_page,
    [[maybe_unused]] DWORD dw_flags, std::string_view view
);

}

#endif  // DETAIL_STRING_API_SET_HPP_INCLUDED
