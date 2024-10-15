//===--- NoFflushStdinCheck.h - clang-tidy ----------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_CODEQUALITY_NOFFLUSHSTDINCHECK_H
#define LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_CODEQUALITY_NOFFLUSHSTDINCHECK_H

#include "clang-tidy/ClangTidyCheck.h"

namespace clang {
namespace tidy {
namespace codequality {

/// FIXME: Write a short description.
///
/// For the user-facing documentation see:
/// http://clang.llvm.org/extra/clang-tidy/checks/codequality/no-fflush-stdin.html
class NoFflushStdinCheck : public ClangTidyCheck {
public:
    NoFflushStdinCheck(StringRef Name, ClangTidyContext *Context) : ClangTidyCheck(Name, Context) {}
    void registerMatchers(ast_matchers::MatchFinder *Finder) override;
    void check(const ast_matchers::MatchFinder::MatchResult &Result) override;

private:
    const clang::Stmt *getStmt(clang::Stmt::const_child_range it, uint index);
};

}  // namespace codequality
}  // namespace tidy
}  // namespace clang

#endif  // LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_CODEQUALITY_NOFFLUSHSTDINCHECK_H
