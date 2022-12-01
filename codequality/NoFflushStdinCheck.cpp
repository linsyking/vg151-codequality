//===--- NoFflushStdinCheck.cpp - clang-tidy ------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "NoFflushStdinCheck.h"

#include <iostream>

#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace codequality {

void NoFflushStdinCheck::registerMatchers(MatchFinder *Finder) {
    // FIXME: Add matchers.
    Finder->addMatcher(callExpr(callee(functionDecl(hasName("fflush")))).bind("call"), this);
}

const clang::Stmt *NoFflushStdinCheck::getStmt(clang::Stmt::const_child_range it, uint index) {
    uint counter = 0;
    for (const auto *c : it) {
        if (counter == index) {
            return c;
        }
        counter++;
    }
    return nullptr;
}

void NoFflushStdinCheck::check(const MatchFinder::MatchResult &Result) {
    // FIXME: Add callback implementation.
    const auto *caller = Result.Nodes.getNodeAs<CallExpr>("call");

    const auto *var_decl_stmt = getStmt(caller->children(), 1);
    if (var_decl_stmt) {
        const auto *var_decl = getStmt(var_decl_stmt->children(), 0);
        if (var_decl) {
            const auto *var_decl_ref = dyn_cast<DeclRefExpr>(var_decl);
            if (var_decl_ref) {
                const auto *var_decl_r = dyn_cast<VarDecl>(var_decl_ref->getDecl());
                if (var_decl_r) {
                    if (var_decl_r->getQualifiedNameAsString() == "stdin") {
                        diag(caller->getBeginLoc(), "fflush(stdin) is undefined behavior");
                    }
                }
            }
        }
    }
}

}  // namespace codequality
}  // namespace tidy
}  // namespace clang
