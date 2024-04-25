set(HEADER_LIST
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/detail/err_handling_api.hpp
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/detail/string_api_set.hpp
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/detail/check_result.hpp
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/detail/check_result.inl
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/detail/d3d_ptr.hpp
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/game.hpp
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/timer.hpp
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/window.hpp
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/component.hpp
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/triangle_component.hpp)
set(SOURCE_LIST
        detail/err_handling_api.cpp
        detail/string_api_set.cpp
        detail/check_result.cpp
        game.cpp
        timer.cpp
        window.cpp
        component.cpp
        triangle_component.cpp)

add_library(computer_graphics ${SOURCE_LIST} ${HEADER_LIST})
target_include_directories(computer_graphics PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_features(computer_graphics PUBLIC cxx_std_20)
target_link_libraries(computer_graphics PUBLIC
        d3d11.lib dxgi.lib d3dcompiler.lib dxguid.lib
        #Microsoft::DirectXTK
)
