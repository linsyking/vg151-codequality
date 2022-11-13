include_directories(../include)
add_library(codequality
    SHARED
    CodeQualityTidyModule.cpp
    NoGlobalVariablesCheck.cpp
    UncheckedMallocResultCheck.cpp
    )
