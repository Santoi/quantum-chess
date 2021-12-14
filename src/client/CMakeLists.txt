cmake_minimum_required(VERSION 3.12)

set(This client)

project(${This} C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic -pedantic-errors -O3 -ggdb -DDEBUG -fno-inline -D _POSIX_C_SOURCE=200809L")

file(GLOB Sources "*.cpp")
file(GLOB Headers "*.h")

# SDL2
include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
pkg_check_modules(SDL2_Mixer REQUIRED IMPORTED_TARGET SDL2_mixer)
pkg_search_module(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS})

# SDL2PP
include_directories(${SDL2PP_INCLUDE_DIRS})

add_subdirectory(sdl)
add_subdirectory(game)
add_subdirectory(logic)
add_subdirectory(login)
add_subdirectory(communication)

file(GLOB Tests "*.cpp")

add_executable(${This} ${Sources} main.cpp)

target_link_libraries(${This} ${SDL2_LIBRARIES} SDL2
        SDL2_mixer SDL2_image
        ${SDL2_LIBRARY} ${SDL2} ${SDL2_MIXER}
        ${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES}
        ${SDL2_TTF_LIBRARIES} -lSDL2_ttf)
target_link_libraries(${This} ${SDL2PP_LIBRARIES})
target_link_libraries(${This} sdl-lib game-lib login-lib logic-lib communication-client-lib common)
