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

## All checks:

- `no-global-variables`
- `unchecked-malloc-result`
- `no-fflush-stdin`
- `no-public-member-variable`

## C (Project 2)

### `no-global-variables`

Check whether you used (non-const) global variables (including static) in C.

**Note.** You don't need to enable the gloabl variable check in `cppcoreguideline`, otherwise some warnings will be repeated

### `unchecked-malloc-result`

Check whether you checked the return value of `malloc`/`calloc` after you used them.

**Note.** You must use `if` after `malloc` statement. You cannot use it in later statements.

### `no-fflush-stdin`

Stop you from using `fflush(stdin)`.

## C++ (Project 3)

### `no-public-member-variable`

Stop you from using public member variables. Protected member variables and public member functions are OK.

## TO-DO

- Check header guards (need to use `PPCallBacks`)
