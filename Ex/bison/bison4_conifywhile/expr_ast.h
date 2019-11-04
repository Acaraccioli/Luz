#ifndef _AST_H
#define _AST_H
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

enum class NodeKind {
    AddExpr,
    SubExpr,
    MulExpr,
    DivExpr,
    NumExpr,
    IdentExpr,
    ParExpr,
    VarDeclaration,
    AssignStatement,
    PrintStatement,
    PrintStatement2,
    IfStatement
};
class ASTNode {
public:
    virtual string toString() = 0;
    virtual int eval(unordered_map<string, int> vars) = 0;
    NodeKind getKind(){
        return kind;
    };

    NodeKind kind;
};

using ASTNodePtr = ASTNode*;
#define BINARY_EXPR(nomOperacion, operador) \
    class nomOperacion##Expr : public ASTNode { \
        public : \
        nomOperacion##Expr(ASTNodePtr expr1, ASTNodePtr expr2) : expr1(std::move(expr1)), expr2(std::move(expr2)) { kind = NodeKind::nomOperacion##Expr;} \
        int eval(std::unordered_map<std::string, int> vars) { \
            return expr1->eval(vars) operador expr2->eval(vars); \
        }\
        std::string toString() { \
            return  expr1->toString() + #operador + expr2->toString();\
        } \
    ASTNodePtr expr1,expr2;\
    };

BINARY_EXPR(Add,+);
BINARY_EXPR(Sub,-);
BINARY_EXPR(Div,/);
BINARY_EXPR(Mul,*);

class VarDeclaration : public ASTNode {
public:
    VarDeclaration(int  valor,string variable) : valor(valor),variable(variable){}
    
   string toString(){
        return "int "+variable;
    }
    int eval(unordered_map<string, int>& vars){ 
        return vars[variable]; 
        }
    string variable;
    int valor;
};

class PrintStatement2 : public ASTNode {

  public:
    PrintStatement2(ASTNode * expr) : expr(move(expr)){ kind = NodeKind::PrintStatement; }
        int eval(unordered_map<string, int> vars) { }
      virtual NodeKind getKind(){}
    string toString() { 
                return "print("+expr->toString()+")";
        }
    ASTNode *expr;
};    

class IfStatement : public ASTNode{
public:
    IfStatement(ASTNode * c, ASTNode * t, ASTNode * f):c(move(c)), t(move(t)), f(move(f)){ kind = NodeKind::IfStatement;}
    int eval(unordered_map<string, int> vars) {}
          virtual NodeKind getKind(){}

    string toString() override{
        
        return "Si "+c->toString()+" Entonces \n"+t->toString()+"\n} Sino \n"+f->toString()+"\n";

    }
    ASTNode * c;
    ASTNode * t;
    ASTNode * f;
    
};

class IdentExpr : public ASTNode {
    public: 
    IdentExpr(string var) {
        name = var;
        kind = NodeKind::IdentExpr;
    }
    int eval(unordered_map<string, int> vars){ return vars[name]; }
    string toString() { return name; }
    string name;
};


class AssignStatement : public ASTNode{
public:
    AssignStatement(string id, ASTNodePtr expr) :
        id(id), expr(move(expr)) {}
    int eval(unordered_map<string, int> vars) { 
        vars[id] = expr->eval(vars);
        return 0;
    }
    string toString() { 
        return id+ "=" + expr->toString();
        }
    std::string id;
    ASTNodePtr expr;
};

class NumExpr : public ASTNode{
    public:
    NumExpr(int valor ) : valor(valor) {}
    int eval(unordered_map<string, int> vars) { return valor;}
      virtual NodeKind getKind(){}
    string toString() { 
        return to_string(valor); 
        }
    int valor;
};

class ParExpr : public ASTNode{
    public:
    ParExpr(ASTNode* nodo ) : nodo(nodo) { }
    int eval(unordered_map<string, int> vars) { return nodo->eval(vars);}
      virtual NodeKind getKind(){}
    string toString() { 
        string x ="("+nodo->toString()+")";
        return x;
        }
    ASTNode *nodo;
};
#endif