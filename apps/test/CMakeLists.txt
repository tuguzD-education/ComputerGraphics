set(HEADER_LIST
        square_component.hpp
        test_game.hpp)
set(SOURCE_LIST
        main.cpp)

add_executable(test ${SOURCE_LIST} ${HEADER_LIST})
target_compile_features(test PRIVATE cxx_std_20)
target_link_libraries(test PRIVATE computer_graphics)

add_custom_command(TARGET test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources/ $<TARGET_FILE_DIR:test>/resources
        VERBATIM)
