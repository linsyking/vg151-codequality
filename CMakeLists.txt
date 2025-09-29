cmake_minimum_required(VERSION 3.5)
project(vg151-codequality)

# Find required packages
find_package(LLVM REQUIRED CONFIG)

# Auto-detect if Clang is available
if(EXISTS "${LLVM_DIR}/../clang")
    find_package(Clang REQUIRED CONFIG)
else()
    # Fallback: try common locations
    find_package(Clang CONFIG 
        PATHS 
            "${LLVM_DIR}/../clang"
            "${LLVM_DIR}/../../clang"
            "/usr/lib/llvm-${LLVM_VERSION_MAJOR}/lib/cmake/clang"
            "/usr/local/lib/cmake/clang"
            "/opt/homebrew/lib/cmake/clang"  # Homebrew on Apple Silicon
        NO_DEFAULT_PATH)
endif()

# Set C++ standard and flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-O3")

# Platform-specific configurations
if(APPLE)
    # macOS specific settings
    set(CMAKE_MACOSX_RPATH ON)
    set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
    message(STATUS "Building for macOS")
elseif(UNIX AND NOT APPLE)
    # Linux specific settings
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
    message(STATUS "Building for Linux")
endif()

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
if(Clang_FOUND)
    message(STATUS "Found Clang ${LLVM_PACKAGE_VERSION}")
endif()

include_directories(${LLVM_INCLUDE_DIRS})
if(Clang_FOUND)
    include_directories(${CLANG_INCLUDE_DIRS})
endif()

add_definitions(${LLVM_DEFINITIONS})

add_subdirectory(codequality)

# Install rules for packaging
install(TARGETS codequality
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
