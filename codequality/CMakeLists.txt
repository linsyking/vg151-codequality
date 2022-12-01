add_library(codequality
    SHARED
    CodeQualityTidyModule.cpp
    NoFflushStdinCheck.cpp
    NoGlobalVariablesCheck.cpp
    UncheckedMallocResultCheck.cpp
    )
