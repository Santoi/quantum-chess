cmake_minimum_required(VERSION 3.12)

set(This sdl-lib)

project(${This} C CXX)

file(GLOB Sources "*.cpp")
file(GLOB Headers "*.h")

add_subdirectory(drawables)
add_subdirectory(sprite_repositories)

include(FindPkgConfig)

# SDL2
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
pkg_check_modules(SDL2_Mixer REQUIRED IMPORTED_TARGET SDL2_mixer)
pkg_search_module(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS})

# SDL2PP
include_directories(${SDL2PP_INCLUDE_DIRS})

add_library(${This} STATIC ${Sources} ${Headers})

target_link_libraries(${This} ${SDL2_LIBRARIES} SDL2
        SDL2_mixer SDL2_image
        ${SDL2_LIBRARY} ${SDL2} ${SDL2_MIXER}
        ${SDL2_IMAGE_LIBRARIES} ${SDL2_MIXER_LIBRARIES}
        ${SDL2_TTF_LIBRARIES} -lSDL2_ttf)
target_link_libraries(${This} ${SDL2PP_LIBRARIES})
target_link_libraries(${This} game-lib login-lib logic-lib sprite-lib drawables-lib)
