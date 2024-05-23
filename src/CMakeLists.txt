set(HEADER_LIST
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/alloc/inline_allocator.hpp
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/alloc/inline_allocator.inl
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/delegate/delegate.hpp
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/delegate/delegate_handle.hpp
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/delegate/delegate_handle.inl
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/delegate/delegate_kind.hpp
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/delegate/lambda_delegate.hpp
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/delegate/lambda_delegate.inl
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/delegate/member_function.hpp
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/delegate/multicast_delegate.hpp
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/delegate/multicast_delegate.inl
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/delegate/raw_delegate.hpp
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/delegate/raw_delegate.inl
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/delegate/shared_ptr_delegate.hpp
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/delegate/shared_ptr_delegate.inl
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/delegate/static_delegate.hpp
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/delegate/static_delegate.inl
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/detail/err_handling_api.hpp
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/detail/string_api_set.hpp
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/detail/check_result.hpp
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/detail/check_result.inl
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/detail/d3d_ptr.hpp
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/detail/shader.hpp
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/concepts.hpp
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/math.hpp
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/collision.hpp
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/transform.hpp
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/game.hpp
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/game.inl
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/timer.hpp
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/window.hpp
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/input.hpp
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/input_key.hpp
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/component.hpp
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/scene_component.hpp
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/scene_component.inl
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/camera.hpp
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/camera_manager.hpp
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/viewport.hpp
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/viewport_manager.hpp
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/triangle_component.hpp
        ${PROJECT_SOURCE_DIR}/include/computer_graphics/box_component.hpp)
set(SOURCE_LIST
        delegate/delegate.cpp
        delegate/delegate_handle.cpp
        delegate/delegate_kind.cpp
        detail/err_handling_api.cpp
        detail/string_api_set.cpp
        detail/check_result.cpp
        detail/shader.cpp
        math.cpp
        collision.cpp
        transform.cpp
        game.cpp
        timer.cpp
        window.cpp
        input.cpp
        component.cpp
        scene_component.cpp
        camera.cpp
        camera_manager.cpp
        viewport.cpp
        viewport_manager.cpp
        triangle_component.cpp
        box_component.cpp)

find_package(directxtk CONFIG REQUIRED)

add_library(computer_graphics ${SOURCE_LIST} ${HEADER_LIST})
target_include_directories(computer_graphics PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_features(computer_graphics PUBLIC cxx_std_20)
target_link_libraries(computer_graphics PUBLIC
        d3d11.lib dxgi.lib d3dcompiler.lib dxguid.lib
        Microsoft::DirectXTK
)

message(STATUS "Using toolchain file: ${CMAKE_TOOLCHAIN_FILE}")
