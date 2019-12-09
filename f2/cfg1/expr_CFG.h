#include <stdio.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <string.h>

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

static std::vector<Arista *> predecessors;
static std::vector<Stmt*> blockStmts;
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

    void virtual setNext(Stmt * next) = 0;
    std::string virtual toString() = 0;
    int predCount = 0;

    void addPred(Stmt * n){
        predCount++;
    }

    Stmt * getNext(){
        return nullptr;
    }

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
    AristaCond(CFGNode * node1, CFGNode * node2) : node1(node1), node2(node2) {}

    CFGNode * node1, *node2;
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

    CFGNode * getNext(){
        return next;
    }

    void setNextStmt(Stmt * n){
        nextStmt = n;
        n->addPred(nextStmt);
        std::cout << n->toString() << std::endl;
    }

    void setEdge(Arista* n){
        edge = n;
    }

    void addStmt(Stmt *n){
        this->stmt = n;
        this->statements.push_back(stmt);
    }

    void printStatements(){
        std::cout << getLabel() << std::endl;
        for(int a = 0; a < statements.size(); a++){
            std::cout << "   " << statements.at(a)->toString() << std::endl;
        }
    }
    
    Arista * edge;
    CFGNode * next;
    Stmt * stmt, *nextStmt;
    std::vector<Stmt*> statements;

    std::string label;
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

class StringOperand : public Operand {
public:
    StringOperand(std::string val): value(val){}
    std::string value;

    std::string toString(){
        return "\"" + value + "\"";
    }

    NodeKind getKind(){
        return NodeKind::StringOp;
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

class NegateExpr : public UnaryExpr {
public:
    NegateExpr(Operand * op) : UnaryExpr(op) {}

    std::string toString(){
        return "!" + op->toString();
    }

    Operand * op;
};


class IfStmt : public Stmt {
public:
    IfStmt(ExprClass * cond, CFGNode * tb, CFGNode * fb ): condicion(cond), trueBlock(tb), falseBlock(fb){}

    ExprClass * condicion;
    CFGNode *trueBlock, *falseBlock;

    std::string toString(){
        return "if(" + condicion->toString() + ") goto "  + trueBlock->getLabel() + " else goto " + falseBlock->getLabel();
    }
    void setNext(Stmt * next){

    }

    Stmt * getNext(){
        nullptr;
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

    void setNext(Stmt * n){
        next = n; 
        n->addPred(this);
    }

    Stmt * getNext(){
        return next;
    }

    Stmt * next;


};

class ParamStmt : public Stmt {
public: 
    ParamStmt(Operand * op) : op(op){}

    Operand * op;

    std::string toString(){
        return "param "  + op->toString();
    }
    void setNext(Stmt * n){
        next = n; 
        n->addPred(this);
    }

    Stmt * getNext(){
        return next;
    }

    Stmt * next;




};

class RetStmt : public Stmt {
public:
    RetStmt(){}

    std::string toString(){
        return "ret";
    }
    void setNext(Stmt * n){
        next = n; 
        n->addPred(this);
    }

    Stmt * getNext(){
        return next;
    }

    Stmt * next;

};

class CallStmt : public Stmt {
public:
    CallStmt(std::string n, int c): name(n), cant(c){}

    std::string name;
    int cant;

    std::string toString(){
        return "call " + name + "," + std::to_string(cant);
    }

    void setNext(Stmt * n){
        next = n; 
        n->addPred(this);
    }

    Stmt * getNext(){
        return next;
    }

    Stmt * next;
};

class NopStmt : public Stmt {
public:
    NopStmt(){}

    std::string toString(){
        return "nop";
    }

    void setNext(Stmt * n){
        next = n; 
        n->addPred(this);
    }

    Stmt * getNext(){
        return next;
    }

    Stmt * next;
    
};

class BlockStmt : public Stmt {
public: 
    BlockStmt(Stmt * first, Stmt * second): first(first), second(second){}

    std::string toString(){
        std::ostringstream out;

        Stmt * s = first;
        while (s != second ) {
            out << s->toString() << '\n';
            s = s->getNext();
        }
        out << second->toString() << '\n';

        return out.str();
    }

    Stmt * first, *second;

    void setNext(Stmt * next){

    }

    Stmt * getNext(){
        return second->getNext();
    }
    
};
