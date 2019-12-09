#include "expr_CFG.h"
class FuncDef {
public:

    FuncDef(std::string s, std::vector<ParamStmt*> ps, std::vector<CFGNode*> cn)
    {
            nombre=s;
            paramstatements=ps;
            cfgnodes=cn;
    }

    int FuncSize(){
            return paramstatements.size()*4;
    }

    std::string FuncNombre(){
         return nombre;
    }

    std::string nombre;
    std::vector<ParamStmt*> paramstatements;
    std::vector<CFGNode*> cfgnodes;
};




class x86_asmgen {
public:
    x86_asmgen(std::ofstream outfile){
        outfile = std::move(outfile);
    }
    void outputgen(std::ofstream outfile, std::vector<FuncDef*> funcs);
    std::string iraMain(std::vector<FuncDef*> functions);
    std::ofstream outfile;

    
private:
    class StrLitTable {
    public:
        std::unordered_map<std::string, std::string> stringLiterals;

        void addStringLit(std::string na){
            std::unordered_map<std::string,std::string>::const_iterator it = stringLiterals.find(na);
            if (it == stringLiterals.end()){
                stringLiterals.emplace(na,na); 
            } 
        }
    };


    std::string visitarExpr(AddExpr * expr); 
    std::string visitarExpr(SubExpr * expr); 
    std::string visitarExpr(MulExpr * expr); 
    std::string visitarExpr(DivExpr * expr); 
    std::string visitarExpr(GTExpr * expr); 
    std::string visitarExpr(GEExpr * expr); 
    std::string visitarExpr(LTExpr * expr); 
    std::string visitarExpr(LEExpr * expr); 
    std::string visitarExpr(EQExpr * expr); 
    std::string visitarExpr(NEQExpr * expr); 
    std::string visitarExpr(IfStmt * stmt); 
    std::string visitarExpr(AssignStmt * stmt); 
    std::string visitSelector(Base * node);
    std::string visitarExpr(IntOperand * nodoInt);
    std::string visitarExpr(IdOperand * nodoId);
};

