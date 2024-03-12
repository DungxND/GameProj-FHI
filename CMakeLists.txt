cmake_minimum_required(VERSION 3.28)
project(SAI___Score_Accumulating_Incremental)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc ")
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
add_executable(${PROJECT_NAME} main.cpp project.o game.h defs.h graphics.h structs.h saver.h input.h components/button.h
)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
set(SDL2_PATH "SDL/x86_64-w64-mingw32")
set(SDL2_IMAGE_PATH "SDL/SDL_Image/x86_64-w64-mingw32")
set(SDL2_TTF_PATH "SDL/SDL_ttf/x86_64-w64-mingw32")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})
