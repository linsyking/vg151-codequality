//===--- UncheckedMallocResultCheck.cpp - clang-tidy ----------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "UncheckedMallocResultCheck.h"

#include <iostream>
#include <vector>

#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace codequality {

const std::vector<StringRef> AllocNames = {"malloc", "calloc"};

void UncheckedMallocResultCheck::registerMatchers(MatchFinder *Finder) {
    // Still need to improve for different checks
    Finder->addMatcher(
        traverse(
            TK_IgnoreUnlessSpelledInSource,
            declStmt(hasDescendant(
                         callExpr(callee(functionDecl(hasAnyName(AllocNames)))).bind("caller")),
                     anyOf(has(varDecl().bind("vardecl")),
                           hasDescendant(declRefExpr(to(varDecl().bind("vardecl"))))))
                .bind("decl")),
        this);

    Finder->addMatcher(
        traverse(TK_IgnoreUnlessSpelledInSource,
                 binaryOperator(
                     hasDescendant(
                         callExpr(callee(functionDecl(hasAnyName(AllocNames)))).bind("caller")),
                     hasDescendant(declRefExpr(to(varDecl().bind("vardecl")))))
                     .bind("bin")),
        this);
}
void UncheckedMallocResultCheck::reportBug() {
    diag("The plugin has error, please report this event to 151 Teaching Team.");
}

bool UncheckedMallocResultCheck::hasUsedVar(const Stmt *statement, const VarDecl *var) {
    // Check if it used variable
    if (statement->children().empty()) {
        return false;
    }
    bool has_success = false;
    for (auto const *child : statement->children()) {
        if (child->getStmtClass() == Stmt::DeclRefExprClass) {
            const DeclRefExpr *var_decl = (DeclRefExpr *)child;
            if (var_decl->getDecl() == var) {
                has_success = true;
                continue;
            } else {
                throw 0;
            }
        } else {
            if (hasUsedVar(child, var)) {
                has_success = true;
            }
        }
    }
    return has_success;
}

void UncheckedMallocResultCheck::check(const MatchFinder::MatchResult &Result) {
    const auto *DeclStatement = Result.Nodes.getNodeAs<DeclStmt>("decl");
    const auto *BinOperator   = Result.Nodes.getNodeAs<BinaryOperator>("bin");
    const auto *my_var        = Result.Nodes.getNodeAs<VarDecl>("vardecl");
    const auto *call_expr     = Result.Nodes.getNodeAs<CallExpr>("caller");
    const Stmt *GenNode       = nullptr;
    const Stmt *PaNodes       = nullptr;

    if (!my_var || !call_expr) {
        reportBug();
        return;
    }

    if (DeclStatement) {
        // Decl Mode
        const auto &Parents = (Result.Context->getParents(*DeclStatement));
        GenNode             = DeclStatement;
        if (Parents.empty()) {
            reportBug();
            return;
        }
        const auto *Statement = Parents[0].get<Stmt>();
        if (!Statement) {
            reportBug();
            return;
        }
        PaNodes = Statement;

    } else if (BinOperator) {
        // Bin mode
        const auto &Parents = (Result.Context->getParents(*BinOperator));
        GenNode             = BinOperator;
        if (Parents.empty()) {
            reportBug();
            return;
        }
        const auto *Statement = Parents[0].get<Stmt>();
        if (!Statement) {
            reportBug();
            return;
        }
        PaNodes = Statement;
    } else {
        reportBug();
        return;
    }

    // Got parent!

    bool        ShouldCheck = false;
    const Stmt *BackupChild = nullptr;

    for (auto *Child : PaNodes->children()) {
        if (Child == NULL) {
            break;
        }
        if (ShouldCheck) {
            if (Child->getStmtClass() != Stmt::IfStmtClass) {
                // Wrong!
                diag(call_expr->getBeginLoc(),
                     "variable %0 is dynamically allocated here, but you don't check if its value "
                     "is NULL")
                    << my_var;
                diag(Child->getBeginLoc(), "add 'if' to check whether it's NULL",
                     DiagnosticIDs::Note);
            } else {
                bool check_res = 0;
                const auto *cond_stmt = *Child->child_begin();
                try {
                    check_res = hasUsedVar(cond_stmt, my_var);
                } catch (...) {
                    check_res = 0;
                }
                if (!check_res) {
                    // Not checking properly
                    diag(call_expr->getBeginLoc(),
                         "variable %0 is dynamically allocated here, but you don't check if its "
                         "value "
                         "is NULL")
                        << my_var;
                    diag(cond_stmt->getBeginLoc(), "this 'if' statement is not checking %0 properly",
                         DiagnosticIDs::Note)
                        << my_var;
                }
            }
            ShouldCheck = false;
        }
        if (Child == GenNode) {
            ShouldCheck = true;
            BackupChild = Child;
        }
    }
    if (ShouldCheck) {
        diag(call_expr->getBeginLoc(),
             "variable %0 is dynamically allocated here, but you don't check if its value is NULL")
            << my_var;
        diag(BackupChild->getEndLoc(), "add 'if' to check whether it's NULL", DiagnosticIDs::Note);
    }
}

}  // namespace codequality
}  // namespace tidy
}  // namespace clang
