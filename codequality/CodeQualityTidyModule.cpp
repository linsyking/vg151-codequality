//===--- CodeQualityModule.cpp - clang-tidy--------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "NoGlobalVariablesCheck.h"
#include "UncheckedMallocResultCheck.h"
#include "clang-tidy/ClangTidyModule.h"
#include "clang-tidy/ClangTidyModuleRegistry.h"

namespace clang {
namespace tidy {
namespace codequality {

/// This module is for VG151 Code Quality check
class CodeQualityModule : public ClangTidyModule {
public:
    void addCheckFactories(ClangTidyCheckFactories &CheckFactories) override {
        CheckFactories.registerCheck<NoGlobalVariablesCheck>("codequality-no-global-variables");
        CheckFactories.registerCheck<UncheckedMallocResultCheck>(
            "codequality-unchecked-malloc-result");
    }
};

// Register the CodeQualityModule using this statically initialized variable.
static ClangTidyModuleRegistry::Add<CodeQualityModule> X("codequality-module",
                                                         "Adds VG151-specific checks.");

}  // namespace codequality

// This anchor is used to force the linker to link in the generated object file
// and thus register the CodeQualityModule.
// volatile int CodeQualityModuleAnchorSource = 0;

}  // namespace tidy
}  // namespace clang
