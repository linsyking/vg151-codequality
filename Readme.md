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

## Run checks

Use the sample code in the `tests` folder as an example,

```bash
clang-tidy --checks="-*,code*" --load=path_to_libcodequality.so -header-filter=".*" simple_static.cpp
```

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

