cmake_minimum_required(VERSION 3.5)
project(vg151-codequality)
find_package(LLVM REQUIRED CONFIG)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

set(CMAKE_CXX_FLAGS "-O3 -flto=auto")
add_subdirectory(codequality)

# Change the LLVM include directory on your machine
# target_include_directories(codequality PRIVATE /usr/lib/llvm-17/include) # OR
# include_directories(${LLVM_INCLUDE_DIRS})
target_include_directories(codequality PRIVATE ${LLVM_INCLUDE_DIRS})

install(TARGETS codequality LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
