cmake_minimum_required(VERSION 3.5)
project(vg151-codequality CXX)

set(CMAKE_CXX_FLAGS "-Os -flto")
add_subdirectory(codequality)

target_include_directories(codequality_deb PRIVATE /usr/lib/llvm-14/include)

install(TARGETS codequality LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(TARGETS codequality_deb LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
