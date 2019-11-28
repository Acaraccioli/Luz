#include <stdio.h>
#include <string>
#include <string.h>
#include <vector>

class CFGNode;
class Arista;
class Base;
class ExprClass;
class Stmt;
class Operand;
class IntOperand;

constexpr char add_op[] = "+";
constexpr char res_op[] = "-";
constexpr char mul_op[] = "*";
constexpr char div_op[] = "/";

constexpr char gt[] = ">";
constexpr char lt[] = "<";
constexpr char gte[] = ">=";
constexpr char lte[] = "<=";

constexpr char eq[] = "==";
constexpr char neq[] = "!=";

std::vector<Arista *> predecessors;

enum NodeKind {
    AddEx,
    SubEx,
    MulEx,
    DivEx,
    GTEx,
    LTEx,
    GTEEx,
    LTEEx,
    EqEx,
    NEqEx,
    IntOp,
    IdOp,
    CharOp,
    StringOp
};

class Arista {
public:
};

class AristaSimple : public Arista {
public:
    AristaSimple(CFGNode * node) : node(node) {}

    CFGNode * node;
};

class AristaCond : public Arista {
public:
    AristaCond(ExprClass * expr, CFGNode * node1, CFGNode * node2) : expr(expr), node1(node1), node2(node2) {}

    CFGNode * node1, *node2;
    ExprClass * expr;
};

class CFGNode {
public:
    CFGNode(){}

    void setLabel(std::string lbl){
        label = lbl;
    }
    
    std::string getLabel(){
        return label;
    }

    void addPredecesor(Arista * n){
        predecessors.push_back(n);
    }

    void removePred(Arista*n){
        auto it = predecessors.begin();
        while(it != predecessors.end()){
            if(*it == n){
                it = predecessors.erase(it);
            } else {
                it++;
            }
        }
    }

    void setNext(CFGNode * nextNode){
        next = nextNode;
        nextNode->addPredecesor(new Arista());
    }
    
    CFGNode * next;

    std::string label;
};


class Base {
public: 
   //Base(){}
};

class ExprClass : public Base {
public:
    ExprClass(){}

    std::string virtual toString() = 0;
};

class Stmt : public Base {
public:
    Stmt(){}
};

class Operand : public ExprClass {
public:
    Operand(){}

    std::string virtual toString() = 0;
};

class IntOperand : public Operand {
public:
    IntOperand(int val): value(val){}
    int value;

    std::string toString(){
        return std::to_string(value);
    }

    NodeKind getKind(){
        return NodeKind::IntOp;
    }
};

class IdOperand : public Operand {
public:
    IdOperand(std::string val): value(val){}
    std::string value;

    std::string toString(){
        return value;
    }

    NodeKind getKind(){
        return NodeKind::IdOp;
    }
};

template <const char * oper, NodeKind kind>
class BinaryExpr : public ExprClass {
public:
    BinaryExpr(Operand * e1, Operand * e2) : expr1(e1), expr2(e2){}

   std::string toString(){
        return expr1->toString() + oper + expr2->toString();
    }

    NodeKind getKind(){
        return kind;
    } 
    Operand *expr1, *expr2;

};


using AddExpr = BinaryExpr<add_op, NodeKind::AddEx>;
using SubExpr = BinaryExpr<res_op, NodeKind::SubEx>;
using MulExpr = BinaryExpr<mul_op, NodeKind::MulEx>;
using DivExpr = BinaryExpr<div_op, NodeKind::DivEx>;
using GTExpr = BinaryExpr<gt, NodeKind::GTEx>;
using LTExpr = BinaryExpr<lt, NodeKind::LTEx>;
using GEExpr = BinaryExpr<gte, NodeKind::GTEEx>;
using LEExpr = BinaryExpr<lte, NodeKind::LTEEx>;
using EQExpr = BinaryExpr<eq, NodeKind::EqEx>;
using NEExpr = BinaryExpr<neq, NodeKind::NEqEx>;

class UnaryExpr : public ExprClass {
    public:
    UnaryExpr(Operand* ea): value(ea){}

    Operand* value;

    std::string toString(){
        return value->toString();
    }
};



class IfStmt : public Stmt {
public:
    IfStmt(ExprClass * cond, CFGNode * tb, CFGNode * fb ): condicion(cond), trueBlock(tb), falseBlock(fb){}

    ExprClass * condicion;
    CFGNode *trueBlock, *falseBlock;

    std::string toString(){
        return "if(" + condicion->toString() + ") goto "  + trueBlock->getLabel() + "else goto " + falseBlock->getLabel();
    }
};

class AssignStmt : public Stmt {
public: 
    AssignStmt(IdOperand * id, ExprClass * expr) : id(id), expr(expr) {}

    IdOperand * id;
    ExprClass * expr;

    std::string toString(){
        return id->toString() + "="  + expr->toString();
    }

};

class ParamStmt : public Stmt {
public: 
    ParamStmt(Operand * op) : op(op){}

    Operand * op;

    std::string toString(){
        return "param "  + op->toString();
    }

};

class RetStmt : public Stmt {
public:
    RetStmt(){}

    std::string toString(){
        return "ret";
    }
};

class CallStmt : public Stmt {
public:
    CallStmt(std::string n, int c): name(n), cant(c){}

    std::string name;
    int cant;

    std::string toString(){
        return "call " + name + "," + std::to_string(cant);
    }
};

class NopStmt : public Stmt {
public:
    NopStmt(){}

    std::string toString(){
        return "nop";
    }
};

class BlockStmt : public Stmt {
public: 
    BlockStmt() { }
};



