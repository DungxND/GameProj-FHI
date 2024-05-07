cmake_minimum_required(VERSION 3.29.2)
project(SAI___Score_Accumulating_Incremental)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc -std=c++23")
file(COPY assets SDL/x86_64-w64-mingw32/bin/SDL2.dll SDL/x86_64-w64-mingw32/bin/SDL2_image.dll SDL/x86_64-w64-mingw32/bin/SDL2_ttf.dll SDL/x86_64-w64-mingw32/bin/SDL2_mixer.dll DESTINATION ${CMAKE_BINARY_DIR})
add_compile_options(-fPIC)
add_executable(${PROJECT_NAME}
        icon.o
        main.cpp
        game.hpp
        game.cpp
        defs.hpp
        graphics_n_audio.hpp
        graphics_n_audio.cpp
        structs.hpp
        saver.hpp
        input.hpp
        components/button.hpp
        components/upgrader.cpp
        components/upgrader.hpp
)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
set(CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/SDL/x86_64-w64-mingw32")
set(SDL2_DIR "${CMAKE_SOURCE_DIR}/SDL/x86_64-w64-mingw32")
set(SDL2_PATH "${CMAKE_SOURCE_DIR}/SDL/x86_64-w64-mingw32")
set(SDL2_IMAGE_PATH "${CMAKE_SOURCE_DIR}/SDL/x86_64-w64-mingw32")
set(SDL2_IMAGE_DIR "${CMAKE_SOURCE_DIR}/SDL/x86_64-w64-mingw32")
set(SDL2_TTF_PATH "${CMAKE_SOURCE_DIR}/SDL/x86_64-w64-mingw32")
set(SDL2_TTF_DIR "${CMAKE_SOURCE_DIR}/SDL/x86_64-w64-mingw32")
set(SDL2_MIXER_PATH "${CMAKE_SOURCE_DIR}/SDL/x86_64-w64-mingw32")
set(SDL2_MIXER_DIR "${CMAKE_SOURCE_DIR}/SDL/x86_64-w64-mingw32")

find_package(SDL2 REQUIRED CONFIG)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

find_library(SDL2_LIBRARY SDL2)
find_library(SDL2_IMAGE_LIBRARIES SDL2_image)
find_library(SDL2_TTF_LIBRARIES SDL2_ttf)
find_library(SDL2_MIXER_LIBRARIES SDL2_mixer)

include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR} ${SDL2_MIXER_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${SDL2_MIXER_LIBRARIES})
