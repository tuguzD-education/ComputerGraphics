set(HEADER_LIST
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/detail/err_handling_api.hpp
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/detail/string_api_set.hpp
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/detail/check_result.hpp
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/detail/check_result.inl
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/detail/d3d_ptr.hpp
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/Game.hpp
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/Timer.hpp
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/Window.hpp
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/Component.hpp
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/TriangleComponent.hpp)
set(SOURCE_LIST
        detail/err_handling_api.cpp
        detail/string_api_set.cpp
        detail/check_result.cpp
        Game.cpp
        Timer.cpp
        Window.cpp
        Component.cpp
        TriangleComponent.cpp)

add_library(computer_graphics ${SOURCE_LIST} ${HEADER_LIST})
target_include_directories(computer_graphics PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_features(computer_graphics PUBLIC cxx_std_20)
