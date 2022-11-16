# VG151 Code Check

A clang-tidy plugin that performs code quality checks for vg151.

---

## Build

To build a Release version, run

```sh
cmake -DCMAKE_BUILD_TYPE:STRING=Release -S . -B build

cmake --build build --config Release
```

Change the compiler path by yourself (like adding `-DCMAKE_C_COMPILER:FILEPATH=/usr/local/bin/clang -DCMAKE_CXX_COMPILER:FILEPATH=/usr/local/bin/clang++ `). If possible, better to use `clang` and `clang++` instead of `gcc` and `g++`.

## C (Project 2)

All checks:

- `no-global-variables`
- `unchecked-malloc-result`

### `no-global-variables`

**Function:** Check whether you used (non-const) global variables (including static) in C.

**Note.** You don't need to enable the gloabl variable check in `cppcoreguideline`, otherwise some warnings will be repeated

### `unchecked-malloc-result`

**Function:** Check whether you checked the return value of `malloc`/`calloc` after you used them.

**Note.** You must use `if` after `malloc` statement. You cannot use it in later statements.

## C++ (Project 3)
