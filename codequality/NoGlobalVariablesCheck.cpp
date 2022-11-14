//===--- NoGlobalVariablesCheck.cpp - clang-tidy --------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "NoGlobalVariablesCheck.h"

#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace codequality {

void NoGlobalVariablesCheck::registerMatchers(MatchFinder *Finder) {
    Finder->addMatcher(
        varDecl(hasGlobalStorage(),
                unless(anyOf(isConstexpr(), hasType(isConstQualified()), hasType(referenceType()))),
                unless(hasType(asString("struct option[0]"))))
            .bind("global-variables"),
        this);
}

void NoGlobalVariablesCheck::check(const MatchFinder::MatchResult &Result) {
    const auto *MatchedDecl = Result.Nodes.getNodeAs<VarDecl>("global-variables");
    if (MatchedDecl) {
        diag(MatchedDecl->getLocation(), "global variable %0 is not allowed here") << MatchedDecl <<MatchedDecl->getSourceRange();
        diag("consider adding 'const' to make it unchangeable", DiagnosticIDs::Note);
    }
}

}  // namespace codequality
}  // namespace tidy
}  // namespace clang
