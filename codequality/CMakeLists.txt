add_library(codequality
    SHARED
    CodeQualityTidyModule.cpp
    NoFflushStdinCheck.cpp
    NoGlobalVariablesCheck.cpp
    NoPublicMemberVariablesCheck.cpp
    UncheckedMallocResultCheck.cpp
    )
