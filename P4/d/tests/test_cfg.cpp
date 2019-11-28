#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "cfg.h"

TEST_CASE("Add expression") {
    Expr *e1 = new AddExpr(new IntOperand(10), new IntOperand(20));
    Expr *e2 = new AddExpr(new IntOperand(10), new LValueOperand("z"));
    Expr *e3 = new AddExpr(new LValueOperand("x"), new LValueOperand("y"));
    
    CHECK(e1->toString() == "10+20");
    CHECK(e2->toString() == "10+z");
    CHECK(e3->toString() == "x+y");
}

TEST_CASE("Sub expression") {
    Expr *e1 = new SubExpr(new IntOperand(10), new IntOperand(20));
    Expr *e2 = new SubExpr(new IntOperand(10), new LValueOperand("z"));
    Expr *e3 = new SubExpr(new LValueOperand("x"), new LValueOperand("y"));
    
    CHECK(e1->toString() == "10-20");
    CHECK(e2->toString() == "10-z");
    CHECK(e3->toString() == "x-y");
}

TEST_CASE("Mult expression") {
    Expr *e1 = new MulExpr(new IntOperand(10), new IntOperand(20));
    Expr *e2 = new MulExpr(new IntOperand(10), new LValueOperand("z"));
    Expr *e3 = new MulExpr(new LValueOperand("x"), new LValueOperand("y"));
    
    CHECK(e1->toString() == "10*20");
    CHECK(e2->toString() == "10*z");
    CHECK(e3->toString() == "x*y");
}

TEST_CASE("Div expression") {
    Expr *e1 = new DivExpr(new IntOperand(10), new IntOperand(20));
    Expr *e2 = new DivExpr(new IntOperand(10), new LValueOperand("z"));
    Expr *e3 = new DivExpr(new LValueOperand("x"), new LValueOperand("y"));
    
    CHECK(e1->toString() == "10/20");
    CHECK(e2->toString() == "10/z");
    CHECK(e3->toString() == "x/y");
}

TEST_CASE("Greater than") {
    Expr *e1 = new GTExpr(new IntOperand(10), new IntOperand(20));
    Expr *e2 = new GTExpr(new IntOperand(10), new LValueOperand("z"));
    Expr *e3 = new GTExpr(new LValueOperand("x"), new LValueOperand("y"));
    
    CHECK(e1->toString() == "10>20");
    CHECK(e2->toString() == "10>z");
    CHECK(e3->toString() == "x>y");
}

TEST_CASE("Less than") {
    Expr *e1 = new LTExpr(new IntOperand(10), new IntOperand(20));
    Expr *e2 = new LTExpr(new IntOperand(10), new LValueOperand("z"));
    Expr *e3 = new LTExpr(new LValueOperand("x"), new LValueOperand("y"));
    
    CHECK(e1->toString() == "10<20");
    CHECK(e2->toString() == "10<z");
    CHECK(e3->toString() == "x<y");
}

TEST_CASE("Greater Or Equal") {
    Expr *e1 = new GEExpr(new IntOperand(10), new IntOperand(20));
    Expr *e2 = new GEExpr(new IntOperand(10), new LValueOperand("z"));
    Expr *e3 = new GEExpr(new LValueOperand("x"), new LValueOperand("y"));
    
    CHECK(e1->toString() == "10>=20");
    CHECK(e2->toString() == "10>=z");
    CHECK(e3->toString() == "x>=y");
}

TEST_CASE("Less Or Equal") {
    Expr *e1 = new LEExpr(new IntOperand(10), new IntOperand(20));
    Expr *e2 = new LEExpr(new IntOperand(10), new LValueOperand("z"));
    Expr *e3 = new LEExpr(new LValueOperand("x"), new LValueOperand("y"));
    
    CHECK(e1->toString() == "10<=20");
    CHECK(e2->toString() == "10<=z");
    CHECK(e3->toString() == "x<=y");
}

TEST_CASE("Equal") {
    Expr *e1 = new EQExpr(new IntOperand(10), new IntOperand(20));
    Expr *e2 = new EQExpr(new IntOperand(10), new LValueOperand("z"));
    Expr *e3 = new EQExpr(new LValueOperand("x"), new LValueOperand("y"));
    
    CHECK(e1->toString() == "10==20");
    CHECK(e2->toString() == "10==z");
    CHECK(e3->toString() == "x==y");
}

TEST_CASE("Not Equal") {
    Expr *e1 = new NEExpr(new IntOperand(10), new IntOperand(20));
    Expr *e2 = new NEExpr(new IntOperand(10), new LValueOperand("z"));
    Expr *e3 = new NEExpr(new LValueOperand("x"), new LValueOperand("y"));
    
    CHECK(e1->toString() == "10!=20");
    CHECK(e2->toString() == "10!=z");
    CHECK(e3->toString() == "x!=y");
}

TEST_CASE("Assign Stmt") {
    CFGNode *s1 = new AssignStmt(new LValueOperand("x"), new UnaryExpr(new IntOperand(10)));
    CFGNode *s2 = new AssignStmt(new LValueOperand("x"), new AddExpr(new LValueOperand("x"), new LValueOperand("y")));
    
    CHECK(s1->toString() == "x=10");
    CHECK(s2->toString() == "x=x+y");
}

TEST_CASE("Param Stmt") {
    CFGNode *s1 = new ParamStmt(new LValueOperand("x"));
    CFGNode *s2 = new ParamStmt(new IntOperand(10));
    
    CHECK(s1->toString() == "param x");
    CHECK(s2->toString() == "param 10");
}

TEST_CASE("Call Stmt") {
    CFGNode *s1 = new CallStmt("print", 4);
    
    CHECK(s1->toString() == "call print,4");
}

TEST_CASE("Ret Stmt") {
    CFGNode *s1 = new RetStmt();
    
    CHECK(s1->toString() == "ret");
}

TEST_CASE("CBR Stmt") {
    CFGNode *s1 = new AssignStmt(new LValueOperand("x"), new UnaryExpr(new IntOperand(10)));
    CFGNode *s2 = new AssignStmt(new LValueOperand("x"), new UnaryExpr(new IntOperand(20)));
    CFGNode *s3 = new CBRStmt(new UnaryExpr(new LValueOperand("c")), s1, s2);

    s1->setLabel("l1");
    s2->setLabel("l2");
    
    CHECK(s3->toString() == "if (c) goto l1 else goto l2");
}