#include <string>
#include <string.h>
#include <iostream>
#include <unordered_map>


class ASTNode {
public:
    std::unordered_map<std::string, int> idents;
    virtual std::string toString(){};
	virtual int eval() = 0;
};

class BinaryExpr : public ASTNode {
public:
    ASTNode *n1, *n2;
    BinaryExpr(ASTNode *n1, ASTNode *n2){
		this->n1 = n1;
		this->n2 = n2;
	}
};


class NumExpr : public ASTNode {
public:
    int value;
    NumExpr(int val){
        value = val;
    }
    int eval(){ return value; }
    std::string toString(){ 
        return std::to_string(value); 
    }
};

class IdExpr : public ASTNode {
public:
    char * value;
    
    IdExpr(char * val){
        value = val;
    }
    int eval() { return idents[value]; }
    std::string toString() { return value; }
};

class AssignStmt : public ASTNode {
public:
    char * valueId;
    ASTNode * val;
    AssignStmt(char * id, ASTNode * valor){
        valueId = id;
        val = valor;
    }
    int eval(){ 
        idents[valueId] = val->eval();
        return idents[valueId];
     }
    std::string toString(){ 
        std::string x = valueId;
        x+=" = ";
        x+=val->toString();
        return x;
    } 
};

class PrintExpr : public ASTNode {
public:
    ASTNode * value;
    PrintExpr(ASTNode * val){
        value = val;
    }
    std::string toString(){
        return "print"+value->toString();
    };
    int eval(){ std::cout <<value->toString()<<std::endl; };
};


class SumExpr : public BinaryExpr {
public:
    SumExpr(ASTNode * val1, ASTNode * val2): BinaryExpr(val1,val2) {}
    int eval() { 
        int v1 = n1->eval();
        int v2 = n2->eval();
        return v1 + v2;
    }
    std::string toString() { 
        return n1->toString() + "+" +  n2->toString();	
    }
};

class ResExpr : public BinaryExpr {
public:
    ResExpr(ASTNode * val1, ASTNode * val2): BinaryExpr(val1,val2) {}
    int eval() { 
        int v1 = n1->eval();
        int v2 = n2->eval();
        return v1 - v2;
    }
    std::string toString() { 
        return n1->toString() + "-" +  n2->toString();	
    }
};

class MulExpr : public BinaryExpr {
public:
    MulExpr(ASTNode * val1, ASTNode * val2): BinaryExpr(val1,val2) {}
    int eval() { 
        int v1 = n1->eval();
        int v2 = n2->eval();
        return v1 * v2;
    }
    std::string toString() { 
        return n1->toString() + "*" +  n2->toString();	
    }
};

class DivExpr : public BinaryExpr {
public:
    DivExpr(ASTNode * val1, ASTNode * val2): BinaryExpr(val1,val2) {}
    int eval() { 
        int v1 = n1->eval();
        int v2 = n2->eval();
        return v1 / v2;
    }
    std::string toString() { 
        return n1->toString() + "/" +  n2->toString();	
    }
};

class ParExpr : public ASTNode {
public:
    ASTNode * value;
    ParExpr(ASTNode * val){
        value = val;
    }
    int eval(){ return value->eval(); }
    std::string toString(){ 
        return "(" + value->toString() + ")"; 
   }
};

	