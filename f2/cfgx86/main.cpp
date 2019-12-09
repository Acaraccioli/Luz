#include "x86_asmgen.h"

int main(){

    std::ofstream outfile;
    x86_asmgen * gen = new x86_asmgen(std::move(outfile));
    CFGNode * node1 = new CFGNode();
    IntOperand* param1=new IntOperand(5);
    IntOperand *param2= new IntOperand(8);


    AddExpr * expr = new AddExpr(param1,param2 );
    node1->addElement(expr);

    ParamStmt *parametro1= new ParamStmt(param1);
    ParamStmt *parametro2= new ParamStmt(param2);
    std::vector<ParamStmt*> parametros;
    parametros.push_back(parametro1);
    parametros.push_back(parametro2);
    std::vector<CFGNode *> nodos;
    nodos.push_back(node1);
    FuncDef * firstfunction= new FuncDef("SumaFunc",parametros, nodos );
    std::vector<FuncDef*> functions;
    functions.push_back(firstfunction);
   // std::string x = gen->iraMain(functions);
    gen->outputgen(std::move(outfile), functions);
   // std::cout << x << std::endl;
    
    return 0;
}