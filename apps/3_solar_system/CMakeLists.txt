set(HEADER_LIST
        game.hpp
        celestials/mars/deimos.hpp
        celestials/earth/earth.hpp
        celestials/jupyter.hpp
        celestials/mars/mars.hpp
        celestials/mercury.hpp
        celestials/earth/moon.hpp
        celestials/neptune.hpp
        celestials/mars/phobos.hpp
        celestials/saturn/saturn.hpp
        celestials/sun.hpp
        celestials/uranus/uranus.hpp
        celestials/venus.hpp
        celestials/saturn/saturn_ring.hpp
        celestials/uranus/uranus_ring.hpp
        skybox.hpp)
set(SOURCE_LIST
        main.cpp
        game.cpp
        celestials/mars/deimos.cpp
        celestials/earth/earth.cpp
        celestials/jupyter.cpp
        celestials/mars/mars.cpp
        celestials/mercury.cpp
        celestials/earth/moon.cpp
        celestials/neptune.cpp
        celestials/mars/phobos.cpp
        celestials/saturn/saturn.cpp
        celestials/sun.cpp
        celestials/uranus/uranus.cpp
        celestials/venus.cpp
        celestials/saturn/saturn_ring.cpp
        celestials/uranus/uranus_ring.cpp
        skybox.cpp)

add_executable(3_solar_system ${SOURCE_LIST} ${HEADER_LIST})
target_compile_features(3_solar_system PRIVATE cxx_std_20)
target_link_libraries(3_solar_system PRIVATE computer_graphics)

add_custom_command(TARGET 3_solar_system POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources/ $<TARGET_FILE_DIR:3_solar_system>/resources
        VERBATIM)
