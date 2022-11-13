cmake_minimum_required(VERSION 3.5)
project(vg151-codequality CXX)

set(CMAKE_CXX_FLAGS "-Os -flto")
add_subdirectory(codequality)
install(TARGETS codequality LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
