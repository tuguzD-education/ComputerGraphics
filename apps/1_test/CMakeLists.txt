set(HEADER_LIST
        square_component.hpp
        game.hpp)
set(SOURCE_LIST
        main.cpp)

add_executable(1_test ${SOURCE_LIST} ${HEADER_LIST})
target_compile_features(1_test PRIVATE cxx_std_20)
target_link_libraries(1_test PRIVATE computer_graphics)

add_custom_command(TARGET 1_test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources/ $<TARGET_FILE_DIR:1_test>/resources
        VERBATIM)
