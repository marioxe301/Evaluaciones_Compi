#ifndef __AST_DEF__
#define __AST_DEF__

// Defines to test the AST
#define LOCAL true
#define GLOBAL false
#define ENDL true
#define NOENDL false

#define VAR(a,b) std::make_shared<VariableExpr>(a,b)
#define NUMBER(a) std::make_shared<NumberExpr>(a)

#define ADD(a,b) std::make_shared<AddExpr>(a,b)
#define SUB(a,b) std::make_shared<SubExpr>(a,b)
#define MULT(a,b) std::make_shared<MultExpr>(a,b)
#define DIV(a,b) std::make_shared<DivExpr>(a,b)
#define AND(a,b) std::make_shared<AndExpr>(a,b)
#define OR(a,b) std::make_shared<OrExpr>(a,b)
#define XOR(a,b) std::make_shared<XorExpr>(a,b)
#define NOT(a) std::make_shared<NotExpr>(a)
#define MOD(a,b) std::make_shared<ModExpr>(a,b)
#define SHL(a,b) std::make_shared<ShlExpr>(a,b)
#define SHR(a,b) std::make_shared<ShrExpr>(a,b)
#define LESSTHAN(a,b) std::make_shared<LessThanExpr>(a,b)
#define LESSTHANEQ(a,b) std::make_shared<LessThanEqExpr>(a,b)
#define GREATERTHAN(a,b) std::make_shared<GreaterThanExpr>(a,b)
#define GREATERTHANEQ(a,b) std::make_shared<GreaterThanEqExpr>(a,b)
#define EQUAL(a,b) std::make_shared<EqualExpr>(a,b)
#define DIFF(a,b) std::make_shared<DiffExpr>(a,b)

#define ASSIGN(a,b,c) std::make_shared<AssignStmt>(a,b,c)
#define PRINT(a,b,c) std::make_shared<PrintStmt>(a,b,c)
//#define STR(a) std::make_shared<StringExpr>(a)

#define IF(a,b,c) std::make_shared<IfStmt>(a,b,c)
#define WHILE(a,b) std::make_shared<WhileStmt>(a,b)
#define SEQ(a) std::make_shared<SeqStmt>(a)

#define READ(a,b) std::make_shared<ReadStmt>(a,b)

#define FUNC_DECL(a,b,c) std::make_shared<FuncDeclStmt>(a,b,c)
#define FUNC_CALL(a,b) std::make_shared<FuncCallStmt>(a,b)

#define RETURN(n) std::make_shared<ReturnExpr>(n)

#endif