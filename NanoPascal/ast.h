#ifndef __AST__
#define __AST__

#include <memory>
#include <string>
#include "kinds.h"
#include <vector>

/* AST backbone begin */
class ASTNode{
public:
    virtual NodeKind getKind() const = 0;
protected:
    ASTNode() = default;
};

class Expr: public ASTNode{
public:
    Expr() = default;
};

class Stmt: public ASTNode{
public:
    Stmt() = default;
};
/* AST backbone end */

using ExprPtr = std::shared_ptr<Expr>;
using StmtPtr = std::shared_ptr<Stmt>;

class BinaryExpr: public Expr{
protected:
    BinaryExpr(const ExprPtr &expr_1,const ExprPtr &expr_2)
    : left(expr_1), right(expr_2)
    {}
public:
    ExprPtr left;
    ExprPtr right;
};

class UniExpr: public Expr{
protected:
    UniExpr(const ExprPtr &expr)
    : child(expr)
    {}
public:
    ExprPtr child;
};


/* Expresion seccion begin */
class AddExpr : public BinaryExpr{
public:
    AddExpr(const ExprPtr &expr_1, const ExprPtr &expr_2)
    : BinaryExpr(expr_1,expr_2)
    {}

    NodeKind getKind() const override{ return NodeKind::AddExpr;}
};

class SubExpr : public BinaryExpr{
public:
    SubExpr(const ExprPtr &expr_1, const ExprPtr &expr_2)
    : BinaryExpr(expr_1,expr_2)
    {}

    NodeKind getKind() const override{ return NodeKind::SubExpr;}
};

class MultExpr : public BinaryExpr{
public:
    MultExpr(const ExprPtr &expr_1, const ExprPtr &expr_2)
    : BinaryExpr(expr_1,expr_2)
    {}

    NodeKind getKind() const override{ return NodeKind::MultExpr;}
};

class DivExpr : public BinaryExpr{
public:
    DivExpr(const ExprPtr &expr_1, const ExprPtr &expr_2)
    : BinaryExpr(expr_1,expr_2)
    {}

    NodeKind getKind() const override{ return NodeKind::DivExpr;}
};

class AndExpr : public BinaryExpr{
public:
    AndExpr(const ExprPtr &expr_1, const ExprPtr &expr_2)
    : BinaryExpr(expr_1,expr_2)
    {}

    NodeKind getKind() const override{ return NodeKind::AndExpr;}
};

class OrExpr : public BinaryExpr{
public:
    OrExpr(const ExprPtr &expr_1, const ExprPtr &expr_2)
    : BinaryExpr(expr_1,expr_2)
    {}

    NodeKind getKind() const override{ return NodeKind::OrExpr;}
};

class XorExpr: public BinaryExpr{
public:
    XorExpr(const ExprPtr &expr_1, const ExprPtr &expr_2)
    : BinaryExpr(expr_1,expr_2)
    {}

    NodeKind getKind() const override{ return NodeKind::XorExpr;}
};

class NotExpr: public UniExpr{
public:
    NotExpr(const ExprPtr &expr)
    : UniExpr(expr)
    {}

    NodeKind getKind() const override{ return NodeKind::NotExpr;}
};

class ModExpr: public BinaryExpr{
public:
    ModExpr(const ExprPtr &expr_1, const ExprPtr &expr_2)
    : BinaryExpr(expr_1,expr_2)
    {}

    NodeKind getKind() const override{ return NodeKind::ModExpr;}
};

class ShlExpr : public BinaryExpr{
public:
    ShlExpr(const ExprPtr &expr_1, const ExprPtr &expr_2)
    : BinaryExpr(expr_1,expr_2)
    {}

    NodeKind getKind() const override{ return NodeKind::ShlExpr;}
};

class ShrExpr : public BinaryExpr{
public:
    ShrExpr(const ExprPtr &expr_1, const ExprPtr &expr_2)
    : BinaryExpr(expr_1,expr_2)
    {}

    NodeKind getKind() const override{ return NodeKind::ShrExpr;}
};

class LessThanExpr: public BinaryExpr{
public:
    LessThanExpr(const ExprPtr &expr_1, const ExprPtr &expr_2)
    : BinaryExpr(expr_1,expr_2)
    {}

    NodeKind getKind() const override{ return NodeKind::LessThanExpr;}
};

class LessThanEqExpr: public BinaryExpr{
public:
    LessThanEqExpr(const ExprPtr &expr_1, const ExprPtr &expr_2)
    : BinaryExpr(expr_1,expr_2)
    {}

    NodeKind getKind() const override{ return NodeKind::LessThanEqExpr;}
};

class GreaterThanExpr: public BinaryExpr{
public:
    GreaterThanExpr(const ExprPtr &expr_1, const ExprPtr &expr_2)
    : BinaryExpr(expr_1,expr_2)
    {}

    NodeKind getKind() const override{ return NodeKind::GreaterThanExpr;}
};

class GreaterThanEqExpr: public BinaryExpr{
public:
    GreaterThanEqExpr(const ExprPtr &expr_1, const ExprPtr &expr_2)
    : BinaryExpr(expr_1,expr_2)
    {}

    NodeKind getKind() const override{ return NodeKind::GreaterThanEqExpr;}
};

class EqualExpr : public BinaryExpr{
public:
    EqualExpr(const ExprPtr &expr_1, const ExprPtr &expr_2)
    : BinaryExpr(expr_1,expr_2)
    {}

    NodeKind getKind() const override{ return NodeKind::EqualExpr;}
};

class DiffExpr: public BinaryExpr{
public:
    DiffExpr(const ExprPtr &expr_1, const ExprPtr &expr_2)
    : BinaryExpr(expr_1,expr_2)
    {}

    NodeKind getKind() const override{ return NodeKind::DiffExpr;}
};

class NumberExpr: public Expr{
public:
    NumberExpr(const int &value)
    : value(value)
    {}

    NodeKind getKind() const override{ return NodeKind::NumberExpr;}
public:
    int value;
};

class VariableExpr: public Expr{
public:
    VariableExpr(const std::string &ident,bool &isLocal)
    : ident(ident), isLocal(isLocal)
    {}

    NodeKind getKind() const override{ return NodeKind::VariableExpr;}
public:
    std::string ident;
    bool isLocal;
};

/* class StringExpr: public Expr{
public:
    StringExpr(const std::string &str)
    : str(str)
    {}

    NodeKind getKind() const override{ return NodeKind::StringExpr;}
public:
    std::string str;
}; */

class ReturnExpr: public Expr{
public:
    ReturnExpr(const ExprPtr &expr)
    :ret(expr)
    {}
public:
    ExprPtr ret;
};

/* Expresion seccion end */


/* Statements seccion begin */

class AssignStmt: public Stmt{
public:
    AssignStmt(const std::string &ident, const ExprPtr &expr,const bool&isLocal)
    : ident(ident), expr(expr),isLocal(isLocal)
    {}
    NodeKind getKind() const override{ return NodeKind::AssignStmt;}
public:
    std::string ident;
    ExprPtr expr;
    bool isLocal;
};

class PrintStmt: public Stmt{
public:
    PrintStmt(const std::string &msj,const ExprPtr &out,const bool &b)
    : out(out), breakLine(b), msj(msj)
    {}
    NodeKind getKind() const override { return NodeKind::PrintStmt;}
public:
    std::string msj;
    bool breakLine;
    ExprPtr out;
};

class ReadStmt: public Stmt{
public:
    ReadStmt(const std::string &in,const bool&inLocal)
    : in(in),inLocal(inLocal)
    {}

public:
    std::string in;
    bool inLocal;
};

class IfStmt: public Stmt{
public:
    IfStmt(const ExprPtr &cond,const StmtPtr & stmt_1, const StmtPtr & stmt_2)
    : cond(cond), stmt_1(stmt_1), stmt_2(stmt_2)
    {}
    NodeKind getKind() const override { return NodeKind::IfStmt;}
public:
    ExprPtr cond;
    StmtPtr stmt_1; // If dentro de un if
    StmtPtr stmt_2; // Else
};

class WhileStmt: public Stmt{
public:
    WhileStmt(const ExprPtr & cond, const StmtPtr & block)
    : cond(cond), block(block)
    {}
    NodeKind getKind() const override { return NodeKind::WhileStmt;}
public:
    ExprPtr cond;
    StmtPtr block;
};

class SeqStmt: public Stmt{
public:
    SeqStmt(const std::vector<StmtPtr>&sequence)
    : sequence(sequence)
    {}
    NodeKind getKind() const override { return NodeKind::SeqStmt;}
public:
    std::vector<StmtPtr> sequence;
};

class FuncDeclStmt: public Stmt{
public:
    FuncDeclStmt(const std::string &id, const std::vector<std::string>&args, const ExprPtr &block,const bool &isProc)
    : id(id),args(args),block(block), isProcedure(isProc)
    {}
    NodeKind getKind() const override { return NodeKind::FuncDeclStmt;}
public:
    bool isProcedure;
    std::string id;
    std::vector<std::string>args;
    ExprPtr block;
};


class FuncCallStmt: public Stmt{
public:
    FuncCallStmt(const std::string &id, const std::vector<ExprPtr> &args)
    : id(id), args(args)
    {}
public:
    std::string id;
    std::vector<ExprPtr>args;
};

/* Statement seccion end */

#endif