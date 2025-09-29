#!/bin/bash
set -e

PLATFORM=$(uname)
BUILD_DIR="build"

# Parse command-line arguments
BUILD_TYPE="Release"
CLEAN_BUILD=false

while [[ $# -gt 0 ]]; do
    case $1 in
        -c|--clean)
            CLEAN_BUILD=true
            shift
            ;;
        -t|--type)
            BUILD_TYPE="$2"
            shift 2
            ;;
        *)
            echo "Unknown option: $1"
            echo "Usage: $0 [-c|--clean] [-t|--type BUILD_TYPE]"
            exit 1
            ;;
    esac
done

echo "Building for platform: $PLATFORM, Build type: $BUILD_TYPE"

if [ "$CLEAN_BUILD" = true ]; then
    echo "Cleaning previous builds..."
    rm -rf $BUILD_DIR
fi

mkdir -p $BUILD_DIR
cd $BUILD_DIR

# Configure based on platform
if [[ "$PLATFORM" == "Darwin" ]]; then
    # macOS
    echo "Configuring for macOS..."
    
    # Try to find LLVM/Clang paths from different sources
    LLVM_DIRS=(
        "$(brew --prefix llvm 2>/dev/null)/lib/cmake/llvm"
        "/opt/homebrew/lib/cmake/llvm"  # Apple Silicon
        "/usr/local/lib/cmake/llvm"     # Intel
        "$(brew --prefix)/lib/cmake/llvm"
    )
    
    CLANG_DIRS=(
        "$(brew --prefix llvm 2>/dev/null)/lib/cmake/clang"
        "/opt/homebrew/lib/cmake/clang"  # Apple Silicon
        "/usr/local/lib/cmake/clang"     # Intel
        "$(brew --prefix)/lib/cmake/clang"
    )
    
    LLVM_DIR=""
    for dir in "${LLVM_DIRS[@]}"; do
        if [ -n "$dir" ] && [ -d "$dir" ] 2>/dev/null; then
            LLVM_DIR="$dir"
            break
        fi
    done
    
    Clang_DIR=""
    for dir in "${CLANG_DIRS[@]}"; do
        if [ -n "$dir" ] && [ -d "$dir" ] 2>/dev/null; then
            Clang_DIR="$dir"
            break
        fi
    done
    
    if [ -z "$LLVM_DIR" ] || [ -z "$Clang_DIR" ]; then
        echo "Error: Could not find LLVM/Clang CMake configuration directories"
        if ! command -v brew &> /dev/null; then
            echo "Consider installing LLVM via Homebrew: brew install llvm"
        fi
        exit 1
    fi
    
    echo "Using LLVM_DIR: $LLVM_DIR"
    echo "Using Clang_DIR: $Clang_DIR"
    
    cmake -DCMAKE_BUILD_TYPE:STRING=$BUILD_TYPE \
          -DLLVM_DIR="$LLVM_DIR" \
          -DClang_DIR="$Clang_DIR" \
          -S .. -B .
          
elif [[ "$PLATFORM" == "Linux" ]]; then
    # Linux
    echo "Configuring for Linux..."
    
    # Look for common LLVM installation paths on Linux
    LLVM_VERSIONS=(20 18 17 16 15 14 13 12 11 10 9)
    LLVM_DIR=""
    
    for version in "${LLVM_VERSIONS[@]}"; do
        if [ -d "/usr/lib/llvm-$version/lib/cmake/llvm" ]; then
            LLVM_DIR="/usr/lib/llvm-$version/lib/cmake/llvm"
            break
        fi
        if [ -d "/usr/lib64/llvm-$version/lib64/cmake/llvm" ]; then
            LLVM_DIR="/usr/lib64/llvm-$version/lib64/cmake/llvm"
            break
        fi
    done
    
    # Fallback to find LLVM via CMake's default search if not found
    if [ -z "$LLVM_DIR" ]; then
        LLVM_DIR="NO_DEFAULT_PATH"
    fi
    
    cmake_config_args=(
        -DCMAKE_BUILD_TYPE:STRING=$BUILD_TYPE
    )
    
    if [ -n "$LLVM_DIR" ] && [ "$LLVM_DIR" != "NO_DEFAULT_PATH" ]; then
        cmake_config_args+=(-DLLVM_DIR="$LLVM_DIR")
    fi
    
    cmake "${cmake_config_args[@]}" -S .. -B .
else
    echo "Unsupported platform: $PLATFORM"
    exit 1
fi

echo "Building..."
make -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

echo "Build completed successfully!"
echo "Library file: $(find . -name "libcodequality.*" -type f | head -1)"

echo "Build completed successfully!"
echo "Library file: $(find . -name "libcodequality.*" -type f | head -1)"
