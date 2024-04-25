#pragma once

#ifndef DETAIL_STRING_API_SET_HPP_INCLUDED
#define DETAIL_STRING_API_SET_HPP_INCLUDED

#include <windows.h>

#include <string>

namespace computer_graphics::detail {

std::wstring MultiByteToWideChar(UINT code_page, DWORD dw_flags, std::string_view string);

}

#endif  // DETAIL_STRING_API_SET_HPP_INCLUDED
