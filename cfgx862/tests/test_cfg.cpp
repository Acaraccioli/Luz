#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "CFG.h"

TEST_CASE("Add expression") {

    ExprClass *e1 = new AddExpr(new IntOperand(10), new IntOperand(20));
    ExprClass *e2 = new AddExpr(new IntOperand(10), new IdOperand("z"));
    ExprClass *e3 = new AddExpr(new IdOperand("x"), new IdOperand("y"));
    
    CHECK(e1->toString() == "10+20");
    CHECK(e2->toString() == "10+z");
    CHECK(e3->toString() == "x+y");
}

TEST_CASE("Sub ExprClassession") {
    ExprClass *e1 = new SubExpr(new IntOperand(10), new IntOperand(20));
    ExprClass *e2 = new SubExpr(new IntOperand(10), new IdOperand("z"));
    ExprClass *e3 = new SubExpr(new IdOperand("x"), new IdOperand("y"));
    
    CHECK(e1->toString() == "10-20");
    CHECK(e2->toString() == "10-z");
    CHECK(e3->toString() == "x-y");
}

TEST_CASE("Mult ExprClassession") {
    ExprClass *e1 = new MulExpr(new IntOperand(10), new IntOperand(20));
    ExprClass *e2 = new MulExpr(new IntOperand(10), new IdOperand("z"));
    ExprClass *e3 = new MulExpr(new IdOperand("x"), new IdOperand("y"));
    
    CHECK(e1->toString() == "10*20");
    CHECK(e2->toString() == "10*z");
    CHECK(e3->toString() == "x*y");
}

TEST_CASE("Div expression") {
    ExprClass *e1 = new DivExpr(new IntOperand(10), new IntOperand(20));
    ExprClass *e2 = new DivExpr(new IntOperand(10), new IdOperand("z"));
    ExprClass *e3 = new DivExpr(new IdOperand("x"), new IdOperand("y"));
    
    CHECK(e1->toString() == "10/20");
    CHECK(e2->toString() == "10/z");
    CHECK(e3->toString() == "x/y");
}

TEST_CASE("Greater than") {
    ExprClass *e1 = new GTExpr(new IntOperand(10), new IntOperand(20));
    ExprClass *e2 = new GTExpr(new IntOperand(10), new IdOperand("z"));
    ExprClass *e3 = new GTExpr(new IdOperand("x"), new IdOperand("y"));
    
    CHECK(e1->toString() == "10>20");
    CHECK(e2->toString() == "10>z");
    CHECK(e3->toString() == "x>y");
}

TEST_CASE("Less than") {
    ExprClass *e1 = new LTExpr(new IntOperand(10), new IntOperand(20));
    ExprClass *e2 = new LTExpr(new IntOperand(10), new IdOperand("z"));
    ExprClass *e3 = new LTExpr(new IdOperand("x"), new IdOperand("y"));
    
    CHECK(e1->toString() == "10<20");
    CHECK(e2->toString() == "10<z");
    CHECK(e3->toString() == "x<y");
}

TEST_CASE("Greater Or Equal") {
    ExprClass *e1 = new GEExpr(new IntOperand(10), new IntOperand(20));
    ExprClass *e2 = new GEExpr(new IntOperand(10), new IdOperand("z"));
    ExprClass *e3 = new GEExpr(new IdOperand("x"), new IdOperand("y"));
    
    CHECK(e1->toString() == "10>=20");
    CHECK(e2->toString() == "10>=z");
    CHECK(e3->toString() == "x>=y");
}

TEST_CASE("Less Or Equal") {
    ExprClass *e1 = new LEExpr(new IntOperand(10), new IntOperand(20));
    ExprClass *e2 = new LEExpr(new IntOperand(10), new IdOperand("z"));
    ExprClass *e3 = new LEExpr(new IdOperand("x"), new IdOperand("y"));
    
    CHECK(e1->toString() == "10<=20");
    CHECK(e2->toString() == "10<=z");
    CHECK(e3->toString() == "x<=y");
}

TEST_CASE("Equal") {
    ExprClass *e1 = new EQExpr(new IntOperand(10), new IntOperand(20));
    ExprClass *e2 = new EQExpr(new IntOperand(10), new IdOperand("z"));
    ExprClass *e3 = new EQExpr(new IdOperand("x"), new IdOperand("y"));
    
    CHECK(e1->toString() == "10==20");
    CHECK(e2->toString() == "10==z");
    CHECK(e3->toString() == "x==y");
}

TEST_CASE("Not Equal") {
    ExprClass *e1 = new NEExpr(new IntOperand(10), new IntOperand(20));
    ExprClass *e2 = new NEExpr(new IntOperand(10), new IdOperand("z"));
    ExprClass *e3 = new NEExpr(new IdOperand("x"), new IdOperand("y"));
    
    CHECK(e1->toString() == "10!=20");
    CHECK(e2->toString() == "10!=z");
    CHECK(e3->toString() == "x!=y");
}

TEST_CASE("Assign Stmt") {
    AssignStmt *s1 = new AssignStmt(new IdOperand("x"), new UnaryExpr(new IntOperand(10)));
    AssignStmt *s2 = new AssignStmt(new IdOperand("x"), new AddExpr(new IdOperand("x"), new IdOperand("y")));
    
    CHECK(s1->toString() == "x=10");
    CHECK(s2->toString() == "x=x+y");
}

TEST_CASE("Param Stmt") {
    ParamStmt *s1 = new ParamStmt(new IdOperand("x"));
    ParamStmt *s2 = new ParamStmt(new IntOperand(10));
    
    CHECK(s1->toString() == "param x");
    CHECK(s2->toString() == "param 10");
}

TEST_CASE("Call Stmt") {
    CallStmt *s1 = new CallStmt("print", 4);
    
    CHECK(s1->toString() == "call print,4");
}

TEST_CASE("Ret Stmt") {
    RetStmt *s1 = new RetStmt();
    
    CHECK(s1->toString() == "ret");
}

TEST_CASE("CBR Stmt") {
    AssignStmt *s1 = new AssignStmt(new IdOperand("x"), new UnaryExpr(new IntOperand(10)));
    AssignStmt *s2 = new AssignStmt(new IdOperand("x"), new UnaryExpr(new IntOperand(20)));
    IfStmt *s3 = new IfStmt(new UnaryExpr(new IdOperand("c")), s1, s2);

    s1->setLabel("l1");
    s2->setLabel("l2");
    
    CHECK(s3->toString() == "if (c) goto l1 else goto l2");
} 
