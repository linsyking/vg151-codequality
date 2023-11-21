cmake_minimum_required(VERSION 3.5)
project(vg151-codequality CXX)

set(CMAKE_CXX_FLAGS "-O3 -flto=auto")
add_subdirectory(codequality)

# Change the LLVM include directory on your machine
target_include_directories(codequality PRIVATE /usr/lib/llvm-17/include)

install(TARGETS codequality LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
