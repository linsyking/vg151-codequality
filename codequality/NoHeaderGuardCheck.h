//===--- NoHeaderGuardCheck.h - clang-tidy ----------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_CODEQUALITY_NOHEADERGUARDCHECK_H
#define LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_CODEQUALITY_NOHEADERGUARDCHECK_H

#include <clang-tidy/utils/HeaderGuard.h>

namespace clang {
namespace tidy {
namespace codequality {

/// FIXME: Write a short description.
///
/// For the user-facing documentation see:
/// http://clang.llvm.org/extra/clang-tidy/checks/codequality/no-header-guard.html
class NoHeaderGuardCheck : public utils::HeaderGuardCheck {
public:
    NoHeaderGuardCheck(StringRef Name, ClangTidyContext *Context)
        : HeaderGuardCheck(Name, Context) {}
    bool        shouldSuggestEndifComment(StringRef) override { return false; }
    std::string getHeaderGuard(StringRef Filename, StringRef OldGuard) override;
};

}  // namespace codequality
}  // namespace tidy
}  // namespace clang

#endif  // LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_CODEQUALITY_NOHEADERGUARDCHECK_H
