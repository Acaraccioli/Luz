#include <stdio.h>
#include <string>
#include <string.h>
#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_map>

class CFGNode;
class Arista;
class Base;
class Expression;
class Stmt;
class Operando;
class IntOperand;
Stmt * CFGRemoveNops(Stmt *root);
void CFGSetLabels(Stmt * root);
std::string CFGToString(Stmt * root);
constexpr char add_op[] = "+";
constexpr char mul_op[] = "*";
constexpr char res_op[] = "-";
constexpr char div_op[] = "/";
constexpr char gt[] = ">";
constexpr char gte[] = ">=";
constexpr char lt[] = "<";
constexpr char lte[] = "<=";
constexpr char and_op[] = "&&";
constexpr char or_op[] = "||";
constexpr char mod_op[] = "%";
constexpr char eq[] = "==";
constexpr char neq[] = "!=";

static std::vector<Arista *> predecessors;
static std::vector<Stmt*> blockStmts;
enum NodeKind {
    AddNodeKind,
    MultNodeKind,
    SubNodeKind,
    DivNodeKind,
    OrNodeKind,
    AndNodeKind,
    ModNodeKind,
    GreaterThanNodeKind,
    GreaterThanOrEqualNodeKind,
    LessThanNodeKind,
    LessThanOrEqualNodeKind,
    EqualNodeKind,
    NotEqualNodeKind,
    IntNodeKind,
    IdNodeKind,
    IfNodeKind,
    AssignNodeKind,
    CharNodeKind,
    StringNodeKind,
    StatementNodeKind,
    NopeStatementNodeKind
};

class Base {
public: 
   NodeKind virtual getNodeKind() = 0;
};

class Expression : public Base {
public:
    Expression(){}
    std::string virtual toString() = 0;
    NodeKind getNodeKind(){
    }
};

class Stmt : public Base {
public:
    Stmt(){}
    void virtual setNext(Stmt * siguiente) = 0;
    std::string virtual toString() = 0;
    int predCount = 0;
    void agregarSiguiente(Stmt * x){
        predCount++;
    }

    Stmt * getSiguiente(){ return nullptr;}

    void setLabel(std::string m){tag = m;}

    std::string getTag(){return tag; }
    NodeKind getNodeKind(){return NodeKind::StatementNodeKind;}

    std::vector<Stmt*> getAristas(){ 
        std::vector<Stmt*> aristas;
        if (siguiente != nullptr) 
        {
            aristas.push_back(siguiente);
        }
        return aristas;
    }

    Stmt * siguiente;
    std::string tag;
};

class Arista {
public:
};

class AristaSimple : public Arista {
public:
    AristaSimple(CFGNode * node) : node(node) {}
    
    CFGNode * node;
};

class AristaCondicional : public Arista {
public:
    AristaCondicional(CFGNode * node1, CFGNode * node2) : node1(node1), node2(node2) {}

    CFGNode * node1, *node2;
};

class CFGNode {
public:
    CFGNode(){}

    void setLabel(std::string label){
        tag = label;
    }
    
    std::string getTag(){
        return tag;
    }

    void addPredecesor(Arista * x){
        predecessors.push_back(x);
    }

    void removePred(Arista*x){
        auto it = predecessors.begin();
        while(it != predecessors.end()){
            if(*it == x){
                it = predecessors.erase(it);
            } else {
                it++;
            }
        }
    }

    void setNext(CFGNode * nextNode){
        siguiente = nextNode;
        nextNode->addPredecesor(new Arista());
    }

    CFGNode * getSiguiente(){
        return siguiente;
    }

    void setNextStmt(Stmt * x){
        nextStmt = x;
        x->agregarSiguiente(nextStmt);
        std::cout << x->toString() << std::endl;
    }

    void addElement(Base * x){
        elements.push_back(x);
    }

    void setEdge(Arista* x){
        edge = x;
    }

    void addStmt(Stmt *x){
        this->stmt = x;
        this->statements.push_back(stmt);
    }

    void printStatements(){
        std::cout << getTag() << std::endl;
        for(int a = 0; a < statements.size(); a++){
            std::cout << "   " << statements.at(a)->toString() << std::endl;
        }
    }
    
    Arista * edge;
    CFGNode * siguiente;
    Stmt * stmt, *nextStmt;
    std::vector<Stmt*> statements;
    std::vector<Base*> elements;
    std::string tag;
};


class Operando : public Expression {
public:
    Operando(){}

    std::string virtual toString() = 0;
};

class IntOperand : public Operando {
public:
    IntOperand(int val): value(val){}
    int value;

    std::string toString(){
        return std::to_string(value);
    }

    NodeKind getNodeKind(){
        return NodeKind::IntNodeKind;
    }
};

class IdOperand : public Operando {
public:
    IdOperand(std::string val): value(val){}
    std::string value;

    std::string toString(){
        return value;
    }

    NodeKind getNodeKind(){
        return NodeKind::IdNodeKind;
    }
};

class StringOperand : public Operando {
public:
    StringOperand(std::string val): value(val){}
    std::string value;

    std::string toString(){
        return "\"" + value + "\"";
    }

    NodeKind getNodeKind(){
        return NodeKind::StringNodeKind;
    }

    
};

template <const char * oper, NodeKind kind>
class BinaryExpr : public Expression {
public:
    BinaryExpr(Operando * e1, Operando * e2) : expr1(e1), expr2(e2){}

    std::string toString(){
        return expr1->toString() + oper + expr2->toString();
    }

    NodeKind getNodeKind(){
        return kind;
    } 
    Operando *expr1, *expr2;



};


using AddExpr = BinaryExpr<add_op, NodeKind::AddNodeKind>;
using SubExpr = BinaryExpr<res_op, NodeKind::SubNodeKind>;
using MulExpr = BinaryExpr<mul_op, NodeKind::MultNodeKind>;
using DivExpr = BinaryExpr<div_op, NodeKind::DivNodeKind>;
using GTExpr = BinaryExpr<gt, NodeKind::GreaterThanNodeKind>;
using LTExpr = BinaryExpr<lt, NodeKind::LessThanNodeKind>;
using GEExpr = BinaryExpr<gte, NodeKind::GreaterThanOrEqualNodeKind>;
using LEExpr = BinaryExpr<lte, NodeKind::LessThanOrEqualNodeKind>;
using EQExpr = BinaryExpr<eq, NodeKind::EqualNodeKind>;
using NEQExpr = BinaryExpr<neq, NodeKind::NotEqualNodeKind>;
using ModExpr = BinaryExpr<mod_op, NodeKind::ModNodeKind>;
using AndExpr = BinaryExpr<and_op, NodeKind::AndNodeKind>;
using OrExpr = BinaryExpr<or_op, NodeKind::OrNodeKind>;

class UnaryExpr : public Expression {
    public:
    UnaryExpr(Operando* ea): value(ea){}
    Operando* value;
    std::string toString(){
        return value->toString();
    }
};

class NotExpr : public UnaryExpr {
public:
    NotExpr(Operando * op) : UnaryExpr(op) {}

    std::string toString(){
        return "!" + op->toString();
    }
    Operando * op;
};


class IfStmt : public Stmt {
public:
    IfStmt(Expression * cond, CFGNode * tb, CFGNode * fb ): condicion(cond), trueBlock(tb), falseBlock(fb){}

    Expression * condicion;
    CFGNode *trueBlock, *falseBlock;

    std::string toString(){
        return "if(" + condicion->toString() + ") goto "  + trueBlock->getTag() + " else goto " + falseBlock->getTag();
    }
    void setNext(Stmt * siguiente){}

    std::vector<CFGNode*> getAristas(){
        std::vector<CFGNode*> aristas(2);
        aristas.at(0) = trueBlock;
        aristas.at(1) = falseBlock;
        return aristas;
    }

    NodeKind getNodeKind(){
        return NodeKind::IfNodeKind;
    }

    Stmt * getSiguiente(){
        nullptr;
    }
};

class AssignStmt : public Stmt {
public: 
    AssignStmt(IdOperand * id, Expression * expr) : id(id), expr(expr) {}
    IdOperand * id;
    Expression * expr;
    std::string toString(){
        return id->toString() + " = "  + expr->toString();
    }

    void setNext(Stmt * x){
        siguiente = x; 
        x->agregarSiguiente(this);
    }

    Stmt * getSiguiente(){
        return siguiente;
    }

    Stmt * siguiente;

    NodeKind getNodeKind(){
        return NodeKind::AssignNodeKind;
    }
};

class ParamStmt : public Stmt {
public: 
    ParamStmt(Operando * op) : op(op){}

    Operando * op;

    std::string toString(){
        return "param "  + op->toString();
    }
    void setNext(Stmt * x){
        siguiente = x; 
        x->agregarSiguiente(this);
    }

    Stmt * getSiguiente(){
        return siguiente;
    }
    Stmt * siguiente;
};

class RetStmt : public Stmt {
public:
    RetStmt(){}

    std::string toString(){
        return "ret";
    }
    void setNext(Stmt * x){
        siguiente = x; 
        x->agregarSiguiente(this);
    }

    Stmt * getSiguiente(){
        return siguiente;
    }

    Stmt * siguiente;

};

class CallStmt : public Stmt {
public:
    CallStmt(std::string x, int c): name(x), cant(c){}

    std::string name;
    int cant;

    std::string toString(){
        return "call " + name + "," + std::to_string(cant);
    }

    void setNext(Stmt * x){
        siguiente = x; 
        x->agregarSiguiente(this);
    }
    Stmt * getSiguiente(){
        return siguiente;
    }
    Stmt * siguiente;
};

class NopStmt : public Stmt {
public:
    NopStmt(){}

    std::string toString(){
        return "nop";
    }

    void setNext(Stmt * x){
        siguiente = x; 
        x->agregarSiguiente(this);
    }

    Stmt * getSiguiente(){
        return siguiente;
    }

    NodeKind getNodeKind(){
        return NodeKind::NopeStatementNodeKind;
    }
    Stmt * siguiente;
    
};

class BlockStmt : public Stmt {
public: 
    BlockStmt(Stmt * primero, Stmt * siguiente): primero(primero), siguiente(siguiente){}

    std::string toString(){
        std::ostringstream out;

        Stmt * s = primero;
        while (s != siguiente ) {
            out << s->toString() << '\n';
            s = s->getSiguiente();
        }
        out << siguiente->toString() << '\n';

        return out.str();
    }

    Stmt * primero, *siguiente;

    void setNext(Stmt * siguiente){

    }

    std::vector<Stmt*> getAristas(){
        return siguiente->getAristas();
    }


    Stmt * getSiguiente(){
        return siguiente->getSiguiente();
    }
    
};