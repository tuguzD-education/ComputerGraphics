set(HEADER_LIST
        viewport_manager.hpp
        player.hpp
        field.hpp
        game.hpp
        objects/sign.hpp
        objects/gear.hpp)
set(SOURCE_LIST
        main.cpp
        player.cpp
        game.cpp)

add_executable(4_katamari ${SOURCE_LIST} ${HEADER_LIST})
target_compile_features(4_katamari PRIVATE cxx_std_20)
target_link_libraries(4_katamari PRIVATE computer_graphics)

add_custom_command(TARGET 4_katamari POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources/ $<TARGET_FILE_DIR:4_katamari>/resources
        VERBATIM)
