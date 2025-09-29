# VG151 Code Check

A clang-tidy plugin that performs code quality checks for vg151.

---

## Dependencies

Make sure you have `llvm`, `clang-tidy` installed. You also need `libllvm-dev` (or some similar packages) to get the headers.

You can install `llvm` on [apt.llvm.org](https://apt.llvm.org/) if you are using debian or ubuntu.

If you are using other linux distribution that cannot install clang-tidy headers, you may download those headers manually from [github](https://github.com/llvm/llvm-project/releases/), download `clang-tools-extra-*.src.tar.xz` and move that to some header folder on your system.

## Build

To build a Release version, run

```sh
cmake -DCMAKE_BUILD_TYPE:STRING=Release -S . -B build

cmake --build build --config Release
```

You may change the compiler path (like adding `-DCMAKE_C_COMPILER:FILEPATH=/usr/bin/clang -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/clang++`). If possible, it is better to use `clang` and `clang++` instead of `gcc` and `g++`.

## macOS Build Instructions

For macOS, you need to ensure LLVM and Clang are properly installed and specify the correct CMake paths:

1. Install LLVM/Clang via Homebrew:

```bash
brew install llvm
```

2. Build with the correct CMake configuration:

```bash
cmake -DCMAKE_BUILD_TYPE:STRING=Release \
      -DLLVM_DIR="$(brew --prefix llvm)/lib/cmake/llvm" \
      -DClang_DIR="$(brew --prefix llvm)/lib/cmake/clang" \
      -S . -B build

cmake --build build --config Release
```

The build process will generate `libcodequality.dylib` instead of `libcodequality.so` on macOS.

## Run checks

Use the sample code in the `tests` folder as an example,

```bash
# Linux
clang-tidy --checks="-*,code*" --load=path_to_libcodequality.so -header-filter=".*" simple_static.cpp
```

```bash
# Macos
clang-tidy \
  --load=../vg151-codequality/build/codequality/path_to_libcodequality.dylib \
  --checks="-*,code*" \
  -header-filter=".*" \
  -extra-arg=-isystem \
  -extra-arg=$(xcrun --show-sdk-path)/usr/include \
  *.[ch]
;
```

For macOS, the library path would be `path_to_libcodequality.dylib`.

`"-*,code*"` means add all `codequality` checks and ignore all other checks.

## All checks:

### `no-global-variables`

Check whether you used (non-const) global variables (including static) in C.

**Note.** You don't need to enable the gloabl variable check in `cppcoreguideline`, otherwise some warnings will be repeated

### `unchecked-malloc-result`

Check whether you checked the return value of `malloc`/`calloc` after you used them.

**Note.** You must use `if` after `malloc` statement. You cannot use it in later statements.

### `no-fflush-stdin`

Stop you from using `fflush(stdin)`.

### `no-public-member-variable`

Stop you from using public member variables. Protected member variables and public member functions are OK.

### `no-header-guard`

Check if you defined header guard in header files.
