//===--- CodeQualityModule.cpp - clang-tidy--------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "NoFflushStdinCheck.h"
#include "NoGlobalVariablesCheck.h"
#include "NoHeaderGuardCheck.h"
#include "NoPublicMemberVariablesCheck.h"
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
        CheckFactories.registerCheck<NoFflushStdinCheck>("codequality-no-fflush-stdin");
        CheckFactories.registerCheck<NoGlobalVariablesCheck>("codequality-no-global-variables");
        CheckFactories.registerCheck<NoHeaderGuardCheck>("codequality-no-header-guard");
        CheckFactories.registerCheck<NoPublicMemberVariablesCheck>(
            "codequality-no-public-member-variables");
        CheckFactories.registerCheck<UncheckedMallocResultCheck>(
            "codequality-unchecked-malloc-result");
    }
};

// Register the CodeQualityModule using this statically initialized variable.
static const ClangTidyModuleRegistry::Add<CodeQualityModule> X("codequality-module",
                                                               "Adds VG151-specific checks.");

}  // namespace codequality

}  // namespace tidy
}  // namespace clang
