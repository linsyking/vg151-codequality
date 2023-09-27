# VG151 Code Check

A clang-tidy plugin that performs code quality checks for vg151.

---

## Build

Based on your system environment, you may need to change the include directory in `CMakeLists.txt`:

```cmake
target_include_directories(codequality PRIVATE /usr/lib/llvm-14/include)
```

To build a Release version, run

```sh
cmake -DCMAKE_BUILD_TYPE:STRING=Release -S . -B build

cmake --build build --config Release
```

You may change the compiler path (like adding `-DCMAKE_C_COMPILER:FILEPATH=/usr/local/bin/clang -DCMAKE_CXX_COMPILER:FILEPATH=/usr/local/bin/clang++ `). If possible, better to use `clang` and `clang++` instead of `gcc` and `g++`.

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

