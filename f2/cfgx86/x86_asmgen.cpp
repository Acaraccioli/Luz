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
    switch (nodobase->getNodeKind()) 
    { 
        case NodeKind::AddNodeKind : return visitarExpr(reinterpret_cast<AddExpr*>(nodobase));
        case NodeKind::SubNodeKind: return visitarExpr(reinterpret_cast<SubExpr*>(nodobase));
        case NodeKind::MultNodeKind: return visitarExpr(reinterpret_cast<MulExpr*>(nodobase));
        case NodeKind::DivNodeKind: return visitarExpr(reinterpret_cast<DivExpr*>(nodobase));
        case NodeKind::GreaterThanNodeKind: return visitarExpr(reinterpret_cast<GTExpr*>(nodobase));
        case NodeKind::GreaterThanOrEqualNodeKind: return visitarExpr(reinterpret_cast<GEExpr*>(nodobase));
        case NodeKind::LessThanNodeKind : return visitarExpr(reinterpret_cast<LTExpr*>(nodobase));
        case NodeKind::LessThanOrEqualNodeKind: return visitarExpr(reinterpret_cast<LEExpr*>(nodobase));
        case NodeKind::EqualNodeKind: return visitarExpr(reinterpret_cast<EQExpr*>(nodobase));
        case NodeKind::NotEqualNodeKind : return visitarExpr(reinterpret_cast<NEQExpr*>(nodobase));
        case NodeKind::IfNodeKind: return visitarExpr(reinterpret_cast<IfStmt*>(nodobase));
        case NodeKind::AssignNodeKind : return visitarExpr(reinterpret_cast<AssignStmt*>(nodobase));
        default: break;
    }
}




std::string x86_asmgen::iraMain(std::vector<FuncDef*> functions){
    std::string out = "";
    for(auto f: functions){
        for(auto n: f->cfgnodes){
            for(int a = 0; a < n->elements.size(); a++){
                Base * currElement = n->elements.at(a);
                switch(currElement->getNodeKind()){
                    case (NodeKind::AddNodeKind): {
                        out += visitarExpr(reinterpret_cast<AddExpr*>(currElement));
                        break;
                    }
                    case (NodeKind::SubNodeKind): {
                        out += visitarExpr(reinterpret_cast<SubExpr*>(currElement));
                        break;
                    }
                    case (NodeKind::MultNodeKind): {
                        out += visitarExpr(reinterpret_cast<MulExpr*>(currElement));
                        break;
                    }
                    case (NodeKind::DivNodeKind): {
                        out += visitarExpr(reinterpret_cast<DivExpr*>(currElement));
                        break;
                    }
                    case (NodeKind::IntNodeKind): {
                        out += visitarExpr(reinterpret_cast<IntOperand*>(currElement));
                        break;
                    }
                    case (NodeKind::IdNodeKind): {
                        out += visitarExpr(reinterpret_cast<IdOperand*>(currElement));
                        break;
                    }
                    case (NodeKind::AssignNodeKind): {
                        out += visitarExpr(reinterpret_cast<AssignStmt*>(currElement));
                        break;
                    }
                    case (NodeKind::IfNodeKind): {
                        out += visitarExpr(reinterpret_cast<IfStmt*>(currElement));
                        break;
                    }
                    default:
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
    archivo = visitRet + "mov ebx, eax\n"; 
    return archivo;  
}

std::string x86_asmgen::visitarExpr(IfStmt * nodoIf){
    std::string archivo;
    std::string visitRet = visitSelector(nodoIf->condicion);
    archivo = visitRet + "mov ebx, eax\n";
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