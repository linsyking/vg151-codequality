//===--- NoPublicMemberVariablesCheck.cpp - clang-tidy --------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "NoPublicMemberVariablesCheck.h"

#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace codequality {

void NoPublicMemberVariablesCheck::registerMatchers(MatchFinder *Finder) {
    Finder->addMatcher(cxxRecordDecl(findAll(fieldDecl(isPublic()).bind("var"))), this);
}

void NoPublicMemberVariablesCheck::check(const MatchFinder::MatchResult &Result) {
    const auto *var_decl = Result.Nodes.getNodeAs<FieldDecl>("var");
    diag(var_decl->getLocation(), "public member variable");
    
}

}  // namespace codequality
}  // namespace tidy
}  // namespace clang
