add_library(codequality
    SHARED
    CodeQualityTidyModule.cpp
    NoFflushStdinCheck.cpp
    NoGlobalVariablesCheck.cpp
    NoHeaderGuardCheck.cpp
    NoPublicMemberVariablesCheck.cpp
    UncheckedMallocResultCheck.cpp
    )

# Set the include directories
target_include_directories(codequality PRIVATE 
    ${LLVM_INCLUDE_DIRS}
)

if(Clang_FOUND)
    target_include_directories(codequality PRIVATE 
        ${CLANG_INCLUDE_DIRS}
    )
endif()

# Auto-detect and link required libraries
set(REQUIRED_LIBS "")

# Try to detect available clang libraries
set(CLANG_LIBS_TO_TRY
    clangTidy
    clangTidyUtils
    clangAST
    clangASTMatchers
    clangBasic
    clangFrontend
    clangTooling
    clangLex
    clangParse
    clangSema
    clangSerialization
    clangAnalysis
    clangDriver
    clangEdit
)

foreach(CLANG_LIB ${CLANG_LIBS_TO_TRY})
    if(TARGET ${CLANG_LIB})
        list(APPEND REQUIRED_LIBS ${CLANG_LIB})
    else()
        # Try to find the library as a file
        find_library(${CLANG_LIB}_FILE 
            NAMES ${CLANG_LIB} lib${CLANG_LIB}
            PATHS ${LLVM_LIBRARY_DIR} 
                  ${LLVM_LIBRARY_DIRS}
                  /usr/lib/llvm-${LLVM_VERSION_MAJOR}/lib
                  /usr/local/lib
                  /opt/homebrew/lib
            NO_DEFAULT_PATH)
        if(${CLANG_LIB}_FILE)
            list(APPEND REQUIRED_LIBS ${${CLANG_LIB}_FILE})
        endif()
    endif()
endforeach()

# Link against the detected libraries
if(REQUIRED_LIBS)
    target_link_libraries(codequality ${REQUIRED_LIBS})
endif()

# Always link against required LLVM components
set(LLVM_COMPONENTS
    Support
    Core
)

# Map LLVM components to libraries and link them
llvm_map_components_to_libnames(LLVM_LIBRARIES ${LLVM_COMPONENTS})
if(LLVM_LIBRARIES)
    target_link_libraries(codequality ${LLVM_LIBRARIES})
endif()

if(LLVM_LDFLAGS)
    target_link_libraries(codequality ${LLVM_LDFLAGS})
endif()
