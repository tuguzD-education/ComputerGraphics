cmake_minimum_required(VERSION 3.28.1)
project(itmo_computer_graphics LANGUAGES CXX)

if (MSVC)
    set(CMAKE_VS_GLOBALS
            "UseMultiToolTask=true"
            "EnforceProcessCountAcrossBuilds=true")
endif ()

add_subdirectory(src)
add_subdirectory(apps)
