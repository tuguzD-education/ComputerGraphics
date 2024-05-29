set(HEADER_LIST
        player.hpp
        ball.hpp
        team.hpp
        game.hpp
        field.hpp)
set(SOURCE_LIST
        main.cpp)

add_executable(2_pong ${SOURCE_LIST} ${HEADER_LIST})
target_compile_features(2_pong PRIVATE cxx_std_20)
target_link_libraries(2_pong PRIVATE computer_graphics)

add_custom_command(TARGET 2_pong POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources/ $<TARGET_FILE_DIR:2_pong>/resources
        VERBATIM)
