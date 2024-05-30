set(HEADER_LIST
        game.hpp
        celestials/deimos.hpp
        celestials/earth.hpp
        celestials/jupyter.hpp
        celestials/mars.hpp
        celestials/mercury.hpp
        celestials/moon.hpp
        celestials/neptune.hpp
        celestials/phobos.hpp
        celestials/saturn.hpp
        celestials/sun.hpp
        celestials/uranus.hpp
        celestials/venus.hpp
        celestials/saturn_ring.hpp
        celestials/uranus_ring.hpp)
set(SOURCE_LIST
        main.cpp
        game.cpp
        celestials/deimos.cpp
        celestials/earth.cpp
        celestials/jupyter.cpp
        celestials/mars.cpp
        celestials/mercury.cpp
        celestials/moon.cpp
        celestials/neptune.cpp
        celestials/phobos.cpp
        celestials/saturn.cpp
        celestials/sun.cpp
        celestials/uranus.cpp
        celestials/venus.cpp
        celestials/saturn_ring.cpp
        celestials/uranus_ring.cpp)

add_executable(3_solar_system ${SOURCE_LIST} ${HEADER_LIST})
target_compile_features(3_solar_system PRIVATE cxx_std_20)
target_link_libraries(3_solar_system PRIVATE computer_graphics)

add_custom_command(TARGET 3_solar_system POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources/ $<TARGET_FILE_DIR:3_solar_system>/resources
        VERBATIM)
