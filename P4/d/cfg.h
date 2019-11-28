#ifndef __CFG_H__
#define __CFG_H__

#include <string>
#include <unordered_map>
#include <memory>

using namespace std;

class CFGNode{
    public:
    CFGNode(){}
    ~CFGNode(){}

    string virtual toString() = 0;

    string label;

    void setLabel(string ne){
        label = ne;
    }

    string getLabel(){
        return label;
    }
};

class Expr : public CFGNode{
    public:
    Expr(){}
    ~Expr(){}
};

class Operand : public Expr{
    public:
    Operand(){}
    ~Operand(){}
};

class IntOperand : public Operand{
    public:
    IntOperand(int val): value(val){}
    ~IntOperand(){}
    int value;

    string toString(){
        return std::to_string(value);
    }
};

class UnaryExpr : public Expr{
    public:
    UnaryExpr(Operand* ea): value(ea){}
    ~UnaryExpr(){}
    Operand* value;

    string toString(){
        return value->toString();
    }
};

class LValueOperand : public Operand{
    public:
    LValueOperand(string val): value(val){}
    ~LValueOperand(){}
    string value;

    string toString(){
        return value;
    }
};

class BinExpr : public Expr{
    public:
    BinExpr(Operand* z1, Operand* z2): a1(z1), a2(z2){}
    ~BinExpr(){}
    Operand* a1;
    Operand* a2;
};

class AddExpr : public BinExpr{
    public:
    AddExpr(Operand* z1, Operand* z2): BinExpr(z1,z2){}
    string toString(){
        return a1->toString()+"+"+a2->toString();
    }
};

class SubExpr : public BinExpr{
    public:
    SubExpr(Operand* z1, Operand* z2): BinExpr(z1,z2){}
    string toString(){
        return a1->toString()+"-"+a2->toString();
    }
};

class MulExpr : public BinExpr{
    public:
    MulExpr(Operand* z1, Operand* z2): BinExpr(z1,z2){}
    string toString(){
        return a1->toString()+"*"+a2->toString();
    }
};

class DivExpr : public BinExpr{
    public:
    DivExpr(Operand* z1, Operand* z2): BinExpr(z1,z2){}
    string toString(){
        return a1->toString()+"/"+a2->toString();
    }
};

class GTExpr : public BinExpr{
    public:
    GTExpr(Operand* z1, Operand* z2): BinExpr(z1,z2){}
    string toString(){
        return a1->toString()+">"+a2->toString();
    }
};

class LTExpr : public BinExpr{
    public:
    LTExpr(Operand* z1, Operand* z2): BinExpr(z1,z2){}
    string toString(){
        return a1->toString()+"<"+a2->toString();
    }
};

class GEExpr : public BinExpr{
    public:
    GEExpr(Operand* z1, Operand* z2): BinExpr(z1,z2){}
    string toString(){
        return a1->toString()+">="+a2->toString();
    }
};

class LEExpr : public BinExpr{
    public:
    LEExpr(Operand* z1, Operand* z2): BinExpr(z1,z2){}
    string toString(){
        return a1->toString()+"<="+a2->toString();
    }
};

class EQExpr : public BinExpr{
    public:
    EQExpr(Operand* z1, Operand* z2): BinExpr(z1,z2){}
    string toString(){
        return a1->toString()+"=="+a2->toString();
    }
};


class NEExpr : public BinExpr{
    public:
    NEExpr(Operand* z1, Operand* z2): BinExpr(z1,z2){}
    string toString(){
        return a1->toString()+"!="+a2->toString();
    }
};


class Stmt : public CFGNode{
    public:
    Stmt(){}
    ~Stmt(){}
};

class AssignStmt : public Stmt{
    public:
    AssignStmt(LValueOperand* l, Expr* r): lhs(l),rhs(r){}
    ~AssignStmt(){}
    LValueOperand* lhs;
    Expr* rhs;

    string toString(){
        return lhs->toString()+"="+rhs->toString();
    }
};

class ParamStmt : public Stmt{
    public:
    ParamStmt(Operand* l): lhs(l){}
    ~ParamStmt(){}
    Operand* lhs;

    string toString(){
        return "param "+lhs->toString();
    }
};

class CallStmt : public Stmt{
    public:
    CallStmt(string l, int r): lhs(l),rhs(r){}
    ~CallStmt(){}
    string lhs;
    int rhs;

    string toString(){
        return "call "+lhs+","+std::to_string(rhs);
    }
};

class RetStmt : public Stmt{
    public:
    RetStmt(){}
    ~RetStmt(){}

    string toString(){
        return "ret";
    }
};

class CBRStmt : public Stmt{
    public:
    CBRStmt(Expr* c, CFGNode* t, CFGNode* f): cond(c),tru(t),fal(f){}
    ~CBRStmt(){}
    Expr* cond;
    CFGNode* tru;
    CFGNode* fal;

    string toString(){
        return "if ("+cond->toString()+") goto "+tru->getLabel()+" else goto "+fal->getLabel();
    }
};

#endif
