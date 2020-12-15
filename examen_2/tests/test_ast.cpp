#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "spl_ast.h"
#include "spl_interp.h"

#define SEQ(a) std::make_shared<SeqStmt>(a)
#define FUNC(a,b,c) std::make_shared<FuncDecl>(a,b,c)
#define ASSIGN(a,b) std::make_shared<AssignStmt>(a,b)
#define CALL(a,b) std::make_shared<FuncCall>(a,b)
#define COND(a,b,c) std::make_shared<IfStmt>(a,b,c)
#define ADD(a,b) std::make_shared<AddExpr>(a,b)
#define SUB(a,b) std::make_shared<SubExpr>(a,b)
#define MUL(a,b) std::make_shared<MultExpr>(a,b)
#define DIV(a,b) std::make_shared<DivExpr>(a,b)
#define EQ(a,b) std::make_shared<EqExpr>(a,b)
#define NUM(a) std::make_shared<NumberExpr>(a)
#define VAR(a) std::make_shared<VarExpr>(a)

ASTNodePtr makeFuncDecl(const std::string& name, const std::vector<std::string>& params,
                        ASTNodePtr expr)
{
    return FUNC(name, params, expr);
}

ASTNodePtr makeFuncCall(const std::string& name, const std::vector<ASTNodePtr>& args)
{
    return CALL(name, args);
}

ASTNodePtr makeSeq(const std::vector<ASTNodePtr>& stmts)
{
    return SEQ(stmts);
}

TEST_CASE("Error: Function not defined")
{
    ASTNodePtr root = ASSIGN("x", makeFuncCall("func", {}) );

    SplInterp interp;

    REQUIRE_THROWS( interp.exec(root.get()) );
}

TEST_CASE("Error: Duplicated definition of function")
{
    ASTNodePtr root = makeSeq({
        makeFuncDecl("add", {}, {}),
        makeFuncDecl("add", {}, {})
    });

    SplInterp interp;

    REQUIRE_THROWS( interp.exec(root.get()) );
}

TEST_CASE("Error: Mismatch argument count")
{   
    ASTNodePtr root = makeSeq({
        makeFuncDecl("add", {"a", "b", "c"}, {}),
        ASSIGN("x", makeFuncCall("add", { NUM(10) }))
    });

    SplInterp interp;

    REQUIRE_THROWS( interp.exec(root.get()) );
}

TEST_CASE("Error: Variable not defined")
{
    ASTNodePtr root = makeSeq({
        ASSIGN("x", VAR("y"))
    });

    SplInterp interp;
    REQUIRE_THROWS( interp.exec(root.get()) );
}

TEST_CASE("Single Assign")
{
    std::vector<ASTNodePtr> stmts = {
        ASSIGN("x", MUL(ADD(NUM(10), NUM(7)), NUM(5)))
    };

    ASTNodePtr root = SEQ(stmts);
    SplInterp interp;

    Table vars = interp.exec(root.get());

    auto it = vars.find("x");

    REQUIRE( it != vars.end() );
    CHECK( it->second == 85 );
}

TEST_CASE("Multiple Assign")
{
    std::vector<ASTNodePtr> stmts = {
        ASSIGN("x", ADD(NUM(10), NUM(7))),
        ASSIGN("y", SUB(NUM(170), NUM(7))),
        ASSIGN("z", MUL(NUM(13), NUM(17)))
    };

    ASTNodePtr root = SEQ(stmts);
    SplInterp interp;

    Table vars = interp.exec(root.get());

    auto itx = vars.find("x");
    auto ity = vars.find("y");
    auto itz = vars.find("z");

    REQUIRE( itx != vars.end() );
    CHECK( itx->second == 17 );
    REQUIRE( ity != vars.end() );
    CHECK( ity->second == 163 );
    REQUIRE( itz != vars.end() );
    CHECK( itz->second ==  221);
}

TEST_CASE("Two argument function")
{
    std::vector<ASTNodePtr> stmts = {
        makeFuncDecl( "add", {"a", "b"}, ADD(VAR("a"), VAR("b")) ),
        ASSIGN( "x", makeFuncCall("add", {NUM(10), NUM(20)}) )
     };

    ASTNodePtr root = SEQ(stmts);
    SplInterp interp;

    Table vars = interp.exec(root.get());

    auto it = vars.find("x");

    REQUIRE( it != vars.end() );
    CHECK( it->second == 30 );
}

TEST_CASE("Three argument function")
{
    ASTNodePtr add_fn = makeFuncDecl("add",  { "a", "b", "c" },
                                     { MUL(ADD(VAR("c"), VAR("a")), SUB(VAR("b"), VAR("c"))) });

    ASTNodePtr root = makeSeq({
        add_fn,
        ASSIGN("x", makeFuncCall("add", { NUM(10), NUM(20), NUM(3) })),
    });

    SplInterp interp;

    Table vars = interp.exec(root.get());

    auto it = vars.find("x");

    REQUIRE( it != vars.end() );
    CHECK( it->second == 221 );
}

TEST_CASE("Function order")
{
    ASTNodePtr add_fn = makeFuncDecl(
                                        "add",  { "a", "b", "c" }, 
                                        ADD(makeFuncCall("mul", {VAR("a"), VAR("b")}), VAR("c"))
                                     );

    ASTNodePtr mul_fn = makeFuncDecl("mul",  { "a", "b" }, MUL(VAR("a"), VAR("b")) );

    ASTNodePtr root = makeSeq({
        add_fn,
        mul_fn,
        ASSIGN("x", makeFuncCall("add", { NUM(10), NUM(17), NUM(3) })),
    });

    SplInterp interp;

    Table vars = interp.exec(root.get());

    auto it = vars.find("x");

    REQUIRE( it != vars.end() );
    CHECK( it->second == 173 );
}

TEST_CASE("Recursive function")
{
    ASTNodePtr fact_fn = makeFuncDecl(
                                        "fact",  { "n" },
                                        COND( EQ(VAR("n"), NUM(0)),
                                              NUM(1),
                                              MUL( VAR("n"), makeFuncCall("fact", { SUB(VAR("n"), NUM(1)) }) )
                                            )
                                      );

    ASTNodePtr root = makeSeq({
        fact_fn,
        ASSIGN("x", makeFuncCall("fact", { NUM(7) })),
    });

    SplInterp interp;

    Table vars = interp.exec(root.get());

    auto it = vars.find("x");

    REQUIRE( it != vars.end() );
    CHECK( it->second == 5040 );
}