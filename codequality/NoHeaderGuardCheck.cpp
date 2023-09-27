//===--- NoHeaderGuardCheck.cpp - clang-tidy ------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "NoHeaderGuardCheck.h"
// #include "clang/AST/ASTContext.h"
// #include "clang/ASTMatchers/ASTMatchFinder.h"
// #include "clang-tidy/utils/HeaderGuard.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace codequality {
std::string NoHeaderGuardCheck::getHeaderGuard(StringRef, StringRef OldGuard) {
    return OldGuard.str();
}

}  // namespace codequality
}  // namespace tidy
}  // namespace clang
