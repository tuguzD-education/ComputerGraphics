set(HEADER_LIST
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/Window.hpp
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/Timer.hpp
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/Game.hpp)
set(SOURCE_LIST
        Window.cpp
        Timer.cpp
        Game.cpp)

add_library(computer_graphics ${SOURCE_LIST} ${HEADER_LIST})
target_include_directories(computer_graphics PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_features(computer_graphics PUBLIC cxx_std_20)
