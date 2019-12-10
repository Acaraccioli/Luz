#include "x86_asmgen.h"

int main(){

    std::ofstream outfile;
    x86_asmgen * gen = new x86_asmgen(std::move(outfile));
   /* CFGNode * node1 = new CFGNode();
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
    gen->outputgen(std::move(outfile), functions); */

   // std::cout << x << std::endl;
   /*CFGNode * node1 = new CFGNode();
   IntOperand * int1 = new IntOperand(1);
   IntOperand * int2 = new IntOperand(2); 

    AddExpr * addexpr = new AddExpr(int1,int2);
    std::vector<FuncDef*> functions;

    node1->addElement(addexpr);
    std::vector<CFGNode*> stmts;
    std::vector<ParamStmt*> params;
    stmts.push_back(node1);
    FuncDef * func = new FuncDef("add",params,stmts); 


    functions.push_back(func);  
    
    gen->outputgen(std::move(outfile),functions); */

       CFGNode * node1 = new CFGNode();
    CFGNode * node2 = new CFGNode();
    CFGNode * node3 = new CFGNode();

   IntOperand * int1 = new IntOperand(69);
   IntOperand * int2 = new IntOperand(420);
   //int1->setisParam();
   //int2->setisParam();

    ParamStmt * param1 = new ParamStmt(int1);
    ParamStmt * param2 = new ParamStmt(int2); 

   IdOperand * id1 = new IdOperand("m");
   IdOperand * id2 = new IdOperand("n");
    AssignStmt * astmt1 = new AssignStmt(id1, new IntOperand(11));
    AddExpr * addexpr = new AddExpr(new IntOperand(3),new IntOperand(1));
   //AssignStmt * astmt2 = new AssignStmt(id2, addexpr);
    AssignStmt * astmt3 = new AssignStmt(id1, new IntOperand(22));
    node2->setLabel("LC1");
    node3->setLabel("LC2");
    
    LTExpr * gtexpr = new LTExpr(int1, int2);
    IfStmt * ifstmt = new IfStmt(gtexpr,node2, node3);
    node1->addElement(ifstmt); 
    node2->addElement(astmt1);
    //node2->addElement(astmt2);
    node3->addElement(astmt3);
    std::vector<ParamStmt*> params;
    params.push_back(param1);
    params.push_back(param2);
    std::vector<CFGNode*> stmts;
    stmts.push_back(node1);
    stmts.push_back(node2);
    stmts.push_back(node3);

    FuncDef * func = new FuncDef("if_Prueba",params, stmts); 
      std::vector<FuncDef*> functions;
    functions.push_back(func);
    
    gen->outputgen(std::move(outfile),functions); //ESTE FUNCIONA

    
    return 0;
}