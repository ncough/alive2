#pragma once

#include <any>
#include <format>
#include <map>

#include <llvm/IR/Value.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <type_traits>

#include "SemanticsBaseVisitor.h"

#include "interface.hpp"

namespace aslp {

using type_t = llvm::Type *;
using expr_t = llvm::Value *;
using lexpr_t = llvm::AllocaInst *;
using stmt_t = std::pair<llvm::BasicBlock *, llvm::BasicBlock *>;
struct slice_t {
  unsigned lo;
  unsigned wd;
};

class aslt_visitor : public aslt::SemanticsBaseVisitor { 
public:
  using super = aslt::SemanticsBaseVisitor;

private:
  lifter_interface &iface;
  llvm::Function &func;  // needed to create basic blocks in here
  llvm::LLVMContext &context;
  std::string block_prefix;

  lexpr_t xreg_sentinel;
  lexpr_t vreg_sentinel;
  lexpr_t pstate_sentinel;
  uint64_t depth = 0;

  std::map<std::string, lexpr_t> locals{};
  std::map<unsigned, unsigned> stmt_counts{};

  // stmt_t statements_init(llvm::Function &func) {
  //   llvm::BasicBlock *bb = llvm::BasicBlock::Create(context, "", &func);
  //   return std::make_pair(bb, bb);
  // }

public:
  aslt_visitor(lifter_interface &iface) : 
    iface{iface},
    func{iface.ll_function()},
    context{func.getContext()},
    block_prefix{"aslp_" + iface.nextName()},
    xreg_sentinel{iface.get_reg(reg_t::X, 0)},
    vreg_sentinel{iface.get_reg(reg_t::V, 0)},
    pstate_sentinel{iface.get_reg(reg_t::PSTATE, (int)pstate_t::N)}
  {
    assert(xreg_sentinel);
  }
protected:
  std::ostream& log() const& {
    return std::cerr << std::string(depth, '|');
  }

  virtual type_t type(aslt::SemanticsParser::TypeContext* ctx) {
    depth++;
    auto x = visitType(ctx);
    depth--;
    return std::any_cast<type_t>(x);
  }

  virtual expr_t expr(aslt::SemanticsParser::ExprContext* ctx) {
    depth++;
    auto x = visitExpr(ctx);
    depth--;
    return std::any_cast<expr_t>(x);
  }

  virtual lexpr_t lexpr(aslt::SemanticsParser::LexprContext* ctx) {
    depth++;
    auto x = visitLexpr(ctx);
    depth--;
    return std::any_cast<lexpr_t>(x);
  }

  virtual slice_t slice(aslt::SemanticsParser::Slice_exprContext* ctx) {
    depth++;
    auto x = visitSlice_expr(ctx);
    depth--;
    return std::any_cast<slice_t>(x);
  }

  virtual int64_t lit_int(aslt::SemanticsParser::ExprContext* ctx) {
    assert(dynamic_cast<aslt::SemanticsParser::Expr_Context*>(ctx->expr_()) && "non-literal found where a ExprLitInt was expected");
    auto x = expr(ctx);
    auto i = llvm::cast<llvm::ConstantInt>(x);
    return i->getSExtValue();
  }


  virtual std::pair<expr_t, expr_t> ptr_expr(llvm::Value* x);
  virtual std::pair<llvm::Value*, llvm::Value*> unify_sizes(llvm::Value* x, llvm::Value* y);

  virtual lexpr_t ref_expr(expr_t expr) {
    // XXX: HACK! since ExprVar are realised as LoadInst, this is incorrect in an array.
    // hence, we undo the load to obtain the actual register.

    auto load = llvm::cast<llvm::LoadInst>(expr);
    auto base = llvm::dyn_cast<llvm::AllocaInst>(load->getPointerOperand());

    assert(base && "expr_var: attempt to reference non-allocainst in a lexpr context");
    assert(load->isSafeToRemove() && "surely not");
    load->eraseFromParent();

    // assert(base == xreg_sentinel || base == pstate_sentinel);

    return llvm::cast<llvm::AllocaInst>(base);
  }

  virtual lexpr_t expr_var(aslt::SemanticsParser::ExprContext* ctx) {
    auto x = expr(ctx);
    return ref_expr(x);
  }

  virtual stmt_t stmt(aslt::SemanticsParser::StmtContext* ctx) {
    depth++;
    auto x = visitStmt(ctx);
    depth--;
    // std::cout << "stmt cast" << '\n';
    return std::any_cast<stmt_t>(x);
  }

  virtual stmt_t new_stmt(const std::string_view& name) {
    auto count = stmt_counts[depth]++;
    std::string s = std::format("{}__{}_{}_", block_prefix, depth, count);
    s += name;
    s += '_';
    auto newbb = llvm::BasicBlock::Create(context, s, &func);
    iface.set_bb(newbb);
    return std::make_pair(newbb, newbb);
  }

  stmt_t link(stmt_t head, stmt_t tail) {
    llvm::BranchInst::Create(tail.first, head.second);
    auto bb = tail.second;
    assert(bb);
    iface.set_bb(bb);
    return std::make_pair(head.first, tail.second);
  }

  virtual lexpr_t get_local(std::string s) const& {
    return locals.at(s);
  }

  virtual void add_local(std::string s, lexpr_t v) {
    // assert(!locals.contains(s) && "local variable already exists in aslt!");
    // XXX aslp will emit duplicated local variable names when a variable is declared within
    // a for loop.  https://github.com/UQ-PAC/aslp/issues/43
    locals.insert_or_assign(s, v);
  }

  template<std::ranges::range It, typename Ctx, typename U>
  std::vector<U> map(const It &xs, U(aslt_visitor::*f)(Ctx)) {
    std::vector<U> out{};
    for (const auto& x : xs)
      out.push_back((this->*f)(x));
    return out;
  }

  template<std::ranges::range It, typename F, typename U = std::invoke_result_t<F, std::iter_value_t<It>>>
  std::vector<U> map(const It &xs, F f) {
    std::vector<U> out{};
    for (const auto& x : xs)
      out.push_back(f(x));
    return out;
  }
public:
  virtual std::any visitStmt(aslt::SemanticsParser::StmtContext *ctx) override;
  virtual std::any visitStmts(aslt::SemanticsParser::StmtsContext *ctx) override;
  virtual std::any visitAssign(aslt::SemanticsParser::AssignContext *ctx) override;
  virtual std::any visitConstDecl(aslt::SemanticsParser::ConstDeclContext *ctx) override;
  virtual std::any visitVarDecl(aslt::SemanticsParser::VarDeclContext *ctx) override;
  virtual std::any visitVarDeclsNoInit(aslt::SemanticsParser::VarDeclsNoInitContext *ctx) override;
  virtual std::any visitAssert(aslt::SemanticsParser::AssertContext *ctx) override;
  virtual std::any visitCall_stmt(aslt::SemanticsParser::Call_stmtContext *ctx) override;
  virtual std::any visitConditionalStmt(aslt::SemanticsParser::ConditionalStmtContext *ctx) override;
  virtual std::any visitTypeBits(aslt::SemanticsParser::TypeBitsContext *context) override;
  virtual std::any visitTypeBoolean(aslt::SemanticsParser::TypeBooleanContext *context) override;
  virtual std::any visitLExprVar(aslt::SemanticsParser::LExprVarContext *ctx) override;
  virtual std::any visitLExprField(aslt::SemanticsParser::LExprFieldContext *ctx) override;
  virtual std::any visitLExprArray(aslt::SemanticsParser::LExprArrayContext *ctx) override;
  virtual std::any visitExprVar(aslt::SemanticsParser::ExprVarContext *ctx) override;
  virtual std::any visitExprTApply(aslt::SemanticsParser::ExprTApplyContext *ctx) override;
  virtual std::any visitExprSlices(aslt::SemanticsParser::ExprSlicesContext *ctx) override;
  virtual std::any visitExprField(aslt::SemanticsParser::ExprFieldContext *ctx) override;
  virtual std::any visitExprArray(aslt::SemanticsParser::ExprArrayContext *ctx) override;
  virtual std::any visitExprLitInt(aslt::SemanticsParser::ExprLitIntContext *ctx) override;
  virtual std::any visitExprLitHex(aslt::SemanticsParser::ExprLitHexContext *ctx) override;
  virtual std::any visitExprLitBits(aslt::SemanticsParser::ExprLitBitsContext *ctx) override;
  virtual std::any visitExprLitMask(aslt::SemanticsParser::ExprLitMaskContext *ctx) override;
  virtual std::any visitExprLitString(aslt::SemanticsParser::ExprLitStringContext *ctx) override;
  virtual std::any visitTargs(aslt::SemanticsParser::TargsContext *ctx) override;
  virtual std::any visitSlice_expr(aslt::SemanticsParser::Slice_exprContext *ctx) override;
  virtual std::any visitUuid(aslt::SemanticsParser::UuidContext *ctx) override;

  virtual std::any defaultResult() override {
    return std::any{};
  }
  virtual std::any aggregateResult(std::any vec, std::any nextResult) override {
    return nextResult;
  }

  virtual ~aslt_visitor() override = default;
};

} // namespace aslp
