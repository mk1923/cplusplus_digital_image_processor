cmake_minimum_required(VERSION 3.22)
project(advanced_programming_group_fibonacci)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE "Release")
include_directories(src)

add_executable(advanced_programming_group_fibonacci
                src/Filter.cpp
                src/Filter.h
                src/Image.cpp
                src/Image.h
                src/main.cpp
                src/Projection.cpp
                src/Projection.h
                src/stb_image.h
                src/stb_image_write.h
                src/Volume.cpp
                src/Volume.h
                src/utils.h
                src/utils.cpp
                src/Slice.cpp
                src/Slice.h)

#Set up tests executable
add_executable(tests
                src/Filter.cpp
                src/Filter.h
                src/Image.cpp
                src/Image.h
                src/Projection.cpp
                src/Projection.h
                src/stb_image.h
                src/stb_image_write.h
                src/Volume.cpp
                src/Volume.h
                src/utils.h
                src/utils.cpp
                src/Slice.cpp
                src/Slice.h
                tests/Tests.cpp
                tests/Tests.h
                tests/main.cpp)

#Set up performance executable
add_executable(performance
                src/Filter.cpp
                src/Filter.h
                src/Image.cpp
                src/Image.h
                src/Projection.cpp
                src/Projection.h
                src/stb_image.h
                src/stb_image_write.h
                src/Volume.cpp
                src/Volume.h
                src/utils.h
                src/utils.cpp
                src/Slice.cpp
                src/Slice.h
                performance.cpp)