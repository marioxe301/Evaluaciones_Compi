#ifndef __AST__
#define __AST__

#include<memory>
#include <vector>
#include <string>
enum class Kind{
    AssignStmt,
    AddExpr,
    DivExpr,
    MultExpr,
    SubExpr,
    EqExpr,
    DiffExpr,
    IfStmt,
    FuncDecl,
    FuncCall,
    NumberExpr,
    VarExpr,
    SeqStmt
};


class ASTNode{
    public:
        virtual Kind getKind() const = 0;
        ASTNode() = default;
};

using ExprPtr = std::shared_ptr<ASTNode>;
using StmtPtr = std::shared_ptr<ASTNode>;
using ASTNodePtr = std::shared_ptr<ASTNode>;

class BinaryExpr: public ASTNode{
    public:
        BinaryExpr(const ExprPtr &e_1,const ExprPtr &e_2)
        : e_1(e_1) , e_2(e_2)
        {}
    public:
        ExprPtr e_1,e_2;
};

#define MAKE_BINARY_EXPR( name)\
     class name##Expr: public BinaryExpr{\
        public:\
            name##Expr(const ExprPtr &e_1,const ExprPtr &e_2)\
            : BinaryExpr(e_1,e_2)\
            {}\
            Kind getKind() const override{\
                return Kind::name##Expr;\
            }\
    };

MAKE_BINARY_EXPR( Add )
MAKE_BINARY_EXPR( Sub)
MAKE_BINARY_EXPR( Mult)
MAKE_BINARY_EXPR( Div)
MAKE_BINARY_EXPR( Eq )
MAKE_BINARY_EXPR( Diff )

class NumberExpr: public ASTNode{
public:
    NumberExpr(const int &value)
    :value(value)
    {}
    
    Kind getKind() const override{
        return Kind::NumberExpr;
    }
public:
    int value;
};

class VarExpr: public ASTNode{
    public:
        VarExpr(const std::string &id)
        : id(id)
        {}

        Kind getKind() const override{
            return Kind::VarExpr;
        }
    public:
        std::string id;
};

class AssignStmt: public ASTNode{
    public:
        AssignStmt(const std::string &id, const ExprPtr&expr)
        : id(id), expr(expr)
        {}
        Kind getKind() const override{
            return Kind::AssignStmt;
        }
    public:
        std::string id;
        ExprPtr expr;
};

class IfStmt: public ASTNode{
public:
    IfStmt(const ExprPtr& cond, const StmtPtr&t, const StmtPtr&f)
    : cond(cond), t(t), f(f)
    {}
    Kind getKind() const override{
            return Kind::IfStmt;
        }
public:
    ExprPtr cond;
    StmtPtr t,f;
};

class FuncDecl: public ASTNode{
    public:
        FuncDecl(const std::string &id,const std::vector<std::string>&args,const ExprPtr &body)
        : id(id), body(body), args(args)
        {}
        Kind getKind() const override{
            return Kind::FuncDecl;
        }
    public:
        std::string id;
        std::vector<std::string>args;
        ExprPtr body;
};

class FuncCall: public ASTNode{
    public:
        FuncCall(const std::string &id,const std::vector<ExprPtr>&args)
        : id(id), args(args)
        {}
        Kind getKind() const override{
            return Kind::FuncCall;
        }
        std::string id;
        std::vector<ExprPtr>args;
};

class SeqStmt: public ASTNode{
    public:
        SeqStmt(const std::vector<ASTNodePtr>&seq)
        :seq(seq)
        {}
        Kind getKind() const override{
            return Kind::SeqStmt;
        }
        std::vector<ASTNodePtr>seq;
};
#endif