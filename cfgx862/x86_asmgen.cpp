#include "x86_asmgen.h"


/*void x86_asmgen::outputgen(std::ofstream outfile, std::string data){   
    outfile.open("salidax86.txt");
    outfile << data;
    outfile.close();
}*/

void x86_asmgen::outputgen(std::ofstream outfile, std::vector<FuncDef*> functions){   

    outfile.open("salidax86.txt");
    outfile << "global main" << "\n";
    outfile << "section .data" << "\n";
    outfile <<"section .text\n";

    for(auto x : functions){
        outfile << x->FuncNombre() << ":" << "\n" << "push ebp" << "\n" << "mov ebp, esp" << "\n" <<"add esp, " << std::to_string(x->FuncSize()) << "\n";
        std::string data = iraMain(functions);
        outfile << data;
        std::cout << data << std::endl;
        outfile << "leave" << "\n" <<  "ret" << "\n";
    }
    outfile.close();
}
std::string x86_asmgen::visitSelector(Base * nodobase){
    int x=nodobase->getNodeKind();

        if(x==NodeKind::IntNodeKind) {
            return visitarExpr(reinterpret_cast<IntOperand*>(nodobase));
            }
        else if(x==NodeKind::IdNodeKind) {
            return visitarExpr(reinterpret_cast<IdOperand*>(nodobase));
            }
        else if(x==NodeKind::AddNodeKind) {
            return visitarExpr(reinterpret_cast<AddExpr*>(nodobase));}
        else if(x==NodeKind::SubNodeKind) {
            return visitarExpr(reinterpret_cast<SubExpr*>(nodobase));}
        else if(x==NodeKind::MultNodeKind) {
            return visitarExpr(reinterpret_cast<MulExpr*>(nodobase));}
        else if(x==NodeKind::DivNodeKind) {
            return visitarExpr(reinterpret_cast<DivExpr*>(nodobase));}
        else if(x==NodeKind::GreaterThanNodeKind) {
            return visitarExpr(reinterpret_cast<GTExpr*>(nodobase));}
        else if(x==NodeKind::GreaterThanOrEqualNodeKind) {
            return visitarExpr(reinterpret_cast<GEExpr*>(nodobase)); }
        else if(x==NodeKind::LessThanNodeKind) {
            return visitarExpr(reinterpret_cast<LTExpr*>(nodobase));}
        else if(x==NodeKind::LessThanOrEqualNodeKind) {
            return visitarExpr(reinterpret_cast<LEExpr*>(nodobase));}
        else if(x==NodeKind::EqualNodeKind) {
            return visitarExpr(reinterpret_cast<EQExpr*>(nodobase));}
        else if(x==NodeKind::NotEqualNodeKind) {
            return visitarExpr(reinterpret_cast<NEQExpr*>(nodobase));}
        else if(x==NodeKind::IfNodeKind) {
            return visitarExprCondicional(reinterpret_cast<IfStmt*>(nodobase),reinterpret_cast<IfStmt*>(nodobase)->trueBlock->getTag(),reinterpret_cast<IfStmt*>(nodobase)->falseBlock->getTag());}
        else if(x==NodeKind::AssignNodeKind) {
            return visitarExpr(reinterpret_cast<AssignStmt*>(nodobase));}
        else{}
    
}


std::string x86_asmgen::iraMain(std::vector<FuncDef*> functions){
    std::string out = "";
    for(auto f: functions){
        for(auto n: f->cfgnodes){
            for(int a = 0; a < n->elements.size(); a++){
                std::cout << "cant elements: " <<n->elements.size()<< "node: " <<std::to_string(n->elements.at(a)->getNodeKind()) << std::endl;
                
                Base * currElement = n->elements.at(a);
                 if(n->getTag() != ""){
                    out += n->getTag() + ":" + "\n";
                }
                int x=currElement->getNodeKind();
                    if (x==NodeKind::AddNodeKind){
                        out += visitarExpr(reinterpret_cast<AddExpr*>(currElement));
                        break;
                    }
                    else if (x==NodeKind::SubNodeKind){
                        out += visitarExpr(reinterpret_cast<SubExpr*>(currElement));
                        break;
                    }
                    else if (x==NodeKind::MultNodeKind) {
                        out += visitarExpr(reinterpret_cast<MulExpr*>(currElement));
                        break;
                    }
                    else if (x==NodeKind::DivNodeKind) {
                        out += visitarExpr(reinterpret_cast<DivExpr*>(currElement));
                        break;
                    }
                    else if (x==NodeKind::IntNodeKind) {
                        out += visitarExpr(reinterpret_cast<IntOperand*>(currElement));
                        break;
                    }
                    else if (x==NodeKind::IdNodeKind){
                        out += visitarExpr(reinterpret_cast<IdOperand*>(currElement));
                        break;
                    }
                    else if (x==NodeKind::AssignNodeKind) {
                         std::cout << "asssign" << std::endl;
                        out += visitarExpr(reinterpret_cast<AssignStmt*>(currElement));
                        break;
                    }
                    else if (x==NodeKind::IfNodeKind) {
                        IfStmt * stmt = reinterpret_cast<IfStmt*>(currElement);
                        out += visitarExprCondicional(stmt,stmt->trueBlock->getTag(),stmt->falseBlock->getTag());
                        break;
                    }
                   
             }
         }
     }
    return out;
}

std::string x86_asmgen::visitarExpr(AddExpr * nodoAdd){
    std::string archivo;
    archivo = "mov eax, " + nodoAdd->expr1->toString() + "\nadd eax, " + nodoAdd->expr2->toString() + "\n";
    return archivo;
}

std::string x86_asmgen::visitarExpr(SubExpr * nodoSub){
    std::string archivo;
    archivo = "mov eax, " + nodoSub->expr1->toString() + "\nsub eax, " + nodoSub->expr2->toString() + "\n";
    return archivo;
}

std::string x86_asmgen::visitarExpr(MulExpr * nodoMult){
    std::string archivo;
    archivo = "mov eax, " + nodoMult->expr1->toString() + "\nimul eax, " + nodoMult->expr2->toString() + "\n";
    return archivo;
}

std::string x86_asmgen::visitarExpr(DivExpr * nodoDiv){ //* FALTA *//
    std::string archivo;

    archivo = "mov eax, " + nodoDiv->expr1->toString() + "\ncdq\nidiv eax, " + nodoDiv->expr2->toString() + "\n";
    return archivo;
}

std::string x86_asmgen::visitarExpr(GTExpr * nodoGT){ //* FALTA *//
    std::string archivo;
    archivo = "mov eax, " + nodoGT->expr1->toString() + "\n"  + "cmp eax, " + nodoGT->expr2->toString() + "\nsetg bl\n";
    return archivo;
}

std::string x86_asmgen::visitarExpr(GEExpr * nodoGTE){ 
    std::string archivo;
    archivo = "mov eax, " + nodoGTE->expr1->toString() + "\ncmp eax, " + nodoGTE->expr2->toString() + "\nsetge bl\n";
    return archivo;
}

std::string x86_asmgen::visitarExpr(LTExpr * expr){
    std::string archivo;
    archivo = "mov eax, " + expr->expr1->toString() + "\ncmp eax, " + expr->expr2->toString() + "\nsetl bl\n";
    return archivo;
}

std::string x86_asmgen::visitarExpr(LEExpr * expr){
    std::string archivo;
    archivo = "mov eax, " + expr->expr1->toString() + "\ncmp eax, " + expr->expr2->toString() + "\nsetle bl\n";
    return archivo;
}

std::string x86_asmgen::visitarExpr(EQExpr * expr){
    std::string archivo;
    archivo = "mov eax, " + expr->expr1->toString() + "\ncmp eax, " + expr->expr2->toString() + "\nsete bl\n";
    return archivo;
}

std::string x86_asmgen::visitarExpr(NEQExpr * expr){
    std::string archivo;
    archivo = "mov eax, " + expr->expr1->toString() + "\ncmp eax, " + expr->expr2->toString() + "\nsetne bl\n";
    return archivo;
}

std::string x86_asmgen::visitarExpr(AssignStmt * nodoAssign){
    std::string archivo;

    std::string visitRet = visitSelector(nodoAssign->expr);
    archivo = "mov eax, " + visitRet + "\n"; 

    return archivo;  
}

std::string x86_asmgen::visitarExprCondicional(IfStmt * stmt,std::string tr,std::string fl){
    
    std::string archivo;
    std::string visitRet = visitSelector(stmt->condicion);
    std::string jump = getJumpType(stmt->condicion);

    archivo = visitRet + jump + tr + "\n";
    archivo += "jmp " + fl + "\n";

    
    //archivo = visitRet + "mov ebx, eax\n";
    return archivo;
}

std::string x86_asmgen::visitarExpr(IntOperand * nodoInt){
    std::string archivo;

    archivo = nodoInt->toString();
    return archivo;

}

std::string x86_asmgen::visitarExpr(IdOperand * nodoId){
    std::string archivo;

    archivo = nodoId->toString();
    return archivo;
}

std::string x86_asmgen::getJumpType(Base * expr){
    NodeKind kind = expr->getNodeKind();
    
    if(kind == NodeKind::GreaterThanNodeKind)
        return "jg ";
    else if(kind == NodeKind::GreaterThanOrEqualNodeKind)
        return "jge ";
    else if(kind == NodeKind::LessThanNodeKind){
        
        return "jl ";
    }
        
    else if(kind == NodeKind::LessThanOrEqualNodeKind)
        return "jle ";
    else if(kind == NodeKind::EqualNodeKind)
        return "je ";
    else if(kind == NodeKind::NotEqualNodeKind)
        return "jne ";
    else
        return "";
    
}