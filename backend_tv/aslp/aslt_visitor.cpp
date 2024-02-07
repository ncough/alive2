#include "SemanticsBaseVisitor.h"
#include "aslt_visitor.hpp"

using namespace aslt;

std::ostream& out = std::cerr;

std::any aslt_visitor::visitStmt(SemanticsParser::StmtContext *ctx) {
  // out << "visitStmt: " << ctx->getText() << '\n';
  return super::visitStmt(ctx);
}
std::any aslt_visitor::visitStmts(SemanticsParser::StmtsContext *ctx) {
  out << "visitStmts" << '\n';
  return super::visitStmts(ctx);
}
std::any aslt_visitor::visitAssign(SemanticsParser::AssignContext *ctx) {
  out << "visitAssign: " << ctx->getText() << '\n';
  return super::visitAssign(ctx);
}
std::any aslt_visitor::visitConstDecl(SemanticsParser::ConstDeclContext *ctx) {
  out << "visitConstDecl" << '\n';
  return super::visitConstDecl(ctx);
}
std::any aslt_visitor::visitVarDecl(SemanticsParser::VarDeclContext *ctx) {
  out << "visitVarDecl" << '\n';
  return super::visitVarDecl(ctx);
}
std::any aslt_visitor::visitVarDeclsNoInit(SemanticsParser::VarDeclsNoInitContext *ctx) {
  out << "visitVarDeclsNoInit" << '\n';
  return super::visitVarDeclsNoInit(ctx);
}
std::any aslt_visitor::visitAssert(SemanticsParser::AssertContext *ctx) {
  out << "visitAssert" << '\n';
  return super::visitAssert(ctx);
}
std::any aslt_visitor::visitCall_stmt(SemanticsParser::Call_stmtContext *ctx) {
  out << "visitCall_stmt" << '\n';
  return super::visitCall_stmt(ctx);
}
std::any aslt_visitor::visitConditional_stmt(SemanticsParser::Conditional_stmtContext *ctx) {
  out << "visitConditional_stmt" << '\n';
  return super::visitConditional_stmt(ctx);
}
std::any aslt_visitor::visitTypeBits(SemanticsParser::TypeBitsContext *ctx) {
  out << "visitTypeBits" << '\n';
  return super::visitTypeBits(ctx);
}
std::any aslt_visitor::visitLExprVar(SemanticsParser::LExprVarContext *ctx) {
  out << "visitLExprVar" << '\n';
  return super::visitLExprVar(ctx);
}
std::any aslt_visitor::visitLExprField(SemanticsParser::LExprFieldContext *ctx) {
  out << "visitLExprField" << '\n';
  return super::visitLExprField(ctx);
}
std::any aslt_visitor::visitLExprArray(SemanticsParser::LExprArrayContext *ctx) {
  out << "visitLExprArray" << '\n';
  return super::visitLExprArray(ctx);
}
std::any aslt_visitor::visitExprVar(SemanticsParser::ExprVarContext *ctx) {
  out << "visitExprVar" << '\n';
  return super::visitExprVar(ctx);
}
std::any aslt_visitor::visitExprTApply(SemanticsParser::ExprTApplyContext *ctx) {
  out << "visitExprTApply" << '\n';
  return super::visitExprTApply(ctx);
}
std::any aslt_visitor::visitExprSlices(SemanticsParser::ExprSlicesContext *ctx) {
  out << "visitExprSlices" << '\n';
  return super::visitExprSlices(ctx);
}
std::any aslt_visitor::visitExprField(SemanticsParser::ExprFieldContext *ctx) {
  out << "visitExprField" << '\n';
  return super::visitExprField(ctx);
}
std::any aslt_visitor::visitExprArray(SemanticsParser::ExprArrayContext *ctx) {
  out << "visitExprArray" << '\n';
  return super::visitExprArray(ctx);
}
std::any aslt_visitor::visitExprLitInt(SemanticsParser::ExprLitIntContext *ctx) {
  out << "visitExprLitInt" << '\n';
  return super::visitExprLitInt(ctx);
}
std::any aslt_visitor::visitExprLitHex(SemanticsParser::ExprLitHexContext *ctx) {
  out << "visitExprLitHex" << '\n';
  return super::visitExprLitHex(ctx);
}
std::any aslt_visitor::visitExprLitBits(SemanticsParser::ExprLitBitsContext *ctx) {
  out << "visitExprLitBits" << '\n';
  return super::visitExprLitBits(ctx);
}
std::any aslt_visitor::visitExprLitMask(SemanticsParser::ExprLitMaskContext *ctx) {
  out << "visitExprLitMask" << '\n';
  return super::visitExprLitMask(ctx);
}
std::any aslt_visitor::visitExprLitString(SemanticsParser::ExprLitStringContext *ctx) {
  out << "visitExprLitString" << '\n';
  return super::visitExprLitString(ctx);
}
std::any aslt_visitor::visitTargs(SemanticsParser::TargsContext *ctx) {
  out << "visitTargs" << '\n';
  return super::visitTargs(ctx);
}
std::any aslt_visitor::visitSlice_expr(SemanticsParser::Slice_exprContext *ctx) {
  out << "visitSlice_expr" << '\n';
  return super::visitSlice_expr(ctx);
}
std::any aslt_visitor::visitUuid(SemanticsParser::UuidContext *ctx) {
  out << "visitUuid" << '\n';
  return super::visitUuid(ctx);
}

