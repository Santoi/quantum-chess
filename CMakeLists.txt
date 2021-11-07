cmake_minimum_required(VERSION 3.12)

set(This quantum-chess-proj)

project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(SDL2PP_WITH_IMAGE ON) # if you need SDL_image support
set(SDL2PP_WITH_MIXER ON) # if you need SDL_mixer support
set(SDL2PP_WITH_TTF ON) # if you need SDL_ttf support
add_subdirectory(extlib/libSDL2pp)
add_subdirectory(extlib/googletest)
add_subdirectory(src)
add_subdirectory(test)
