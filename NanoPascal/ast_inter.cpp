#include "ast_inter.h"
#include <iostream>
#include <algorithm>
#include "test_defines.h"


#define HANDLE_CASE(n) \
    case NodeKind::n : return visit(reinterpret_cast<const n*>(root))



int Interpreter::execute(const ASTNode * root){
    switch (root->getKind())
    {
        HANDLE_CASE(NumberExpr);
        HANDLE_CASE(VariableExpr);
        HANDLE_CASE(AddExpr);
        HANDLE_CASE(SubExpr);
        HANDLE_CASE(MultExpr);
        HANDLE_CASE(DivExpr);
        HANDLE_CASE(AndExpr);
        HANDLE_CASE(OrExpr);
        HANDLE_CASE(XorExpr);
        HANDLE_CASE(NotExpr);
        HANDLE_CASE(ModExpr);
        HANDLE_CASE(ShlExpr);
        HANDLE_CASE(ShrExpr);
        HANDLE_CASE(LessThanExpr);
        HANDLE_CASE(LessThanEqExpr);
        HANDLE_CASE(GreaterThanExpr);
        HANDLE_CASE(GreaterThanEqExpr);
        HANDLE_CASE(EqualExpr);
        HANDLE_CASE(DiffExpr);
        //HANDLE_CASE(StringExpr);
        HANDLE_CASE(AssignStmt);
        HANDLE_CASE(PrintStmt);
        HANDLE_CASE(SeqStmt);
        HANDLE_CASE(WhileStmt);
        HANDLE_CASE(IfStmt);
        HANDLE_CASE(ReadStmt);
        HANDLE_CASE(FuncDeclStmt);
        HANDLE_CASE(FuncCallStmt);
        HANDLE_CASE(ReturnExpr);
    default:
        throw std::string("No kind Found");
    }
}

int Interpreter::visit(const NumberExpr * expr){
    return expr->value;
}
int Interpreter::visit(const VariableExpr * expr){
    return expr->isLocal ? variable_stack.top()[expr->ident] : global_vars[expr->ident];
}

int Interpreter::visit(const AddExpr * expr){
    int a = execute(expr->left.get());
    int b = execute(expr->right.get());
    return a+b;
}
int Interpreter::visit(const SubExpr * expr){
    int a = execute(expr->left.get());
    int b = execute(expr->right.get());

    return a-b;
}
int Interpreter::visit(const MultExpr * expr){
    int a = execute(expr->left.get());
    int b = execute(expr->right.get());

    return a*b;
}
int Interpreter::visit(const DivExpr * expr){
    int a = execute(expr->left.get());
    int b = execute(expr->right.get());
    return b == 0 ? throw std::string("Can't divide by 0"): a / b;
}
int Interpreter::visit(const AndExpr * expr){
    int a = execute(expr->left.get());
    int b = execute(expr->right.get());
    return a & b;
}
int Interpreter::visit(const OrExpr * expr){
    int a = execute(expr->left.get());
    int b = execute(expr->right.get());
    return a | b;
}
int Interpreter::visit(const XorExpr * expr){
    int a = execute(expr->left.get());
    int b = execute(expr->right.get());
    return a ^ b;
}
int Interpreter::visit(const NotExpr * expr){
    int a = execute(expr->child.get());
    return ~a;
}
int Interpreter::visit(const ModExpr * expr){
    int a = execute(expr->left.get());
    int b = execute(expr->right.get());
    return b == 0 ? throw std::string("Can't divide by 0") : a % b;
}
int Interpreter::visit(const ShlExpr * expr){
    int a = execute(expr->left.get());
    int b = execute(expr->right.get());
    return a << b;
}
int Interpreter::visit(const ShrExpr * expr){
    int a = execute(expr->left.get());
    int b = execute(expr->right.get());
    return a>>b;
}
int Interpreter::visit(const LessThanExpr * expr){
    int a = execute(expr->left.get());
    int b = execute(expr->right.get());
    return a<b;
}
int Interpreter::visit(const LessThanEqExpr * expr){
    int a = execute(expr->left.get());
    int b = execute(expr->right.get());
    return a<=b;
}
int Interpreter::visit(const GreaterThanExpr * expr){
    int a = execute(expr->left.get());
    int b = execute(expr->right.get());
    return a>b;
}
int Interpreter::visit(const GreaterThanEqExpr * expr){
    int a = execute(expr->left.get());
    int b = execute(expr->right.get());
    return a>=b;
}
int Interpreter::visit(const EqualExpr * expr){
    int a = execute(expr->left.get());
    int b = execute(expr->right.get());
    return a==b;
}
int Interpreter::visit(const DiffExpr * expr){
    int a = execute(expr->left.get());
    int b = execute(expr->right.get());
    return a!=b;
}

/* int Interpreter::visit(const StringExpr * expr){
    int a;
    a.str = expr->str;
    return a;
} */

int Interpreter::visit(const AssignStmt * expr){
    int a = execute(expr->expr.get());
    expr->isLocal ? variable_stack.top()[expr->ident] = a : global_vars[expr->ident] = a;
    return 0;
}
int Interpreter::visit(const PrintStmt * expr){
    int a = execute(expr->out.get());
    expr->breakLine ? std::cout<<expr->msj<<a<<std::endl : std::cout<<expr->msj<<a;
    return 0;
}

int Interpreter::visit(const IfStmt * expr){
    int a = execute(expr->stmt_1.get());
    if(a)
        return execute(expr->stmt_1.get());
    else
        return execute(expr->stmt_2.get());
}
int Interpreter::visit(const WhileStmt * expr){
    int a = execute(expr->cond.get());
    while(a){
        execute(expr->block.get());
        a = execute(expr->cond.get());
    }
    return 0;
}
int Interpreter::visit(const SeqStmt * expr){
    for(const auto& s : expr->sequence){
        execute(s.get());
    }
    return 0;
}

int Interpreter::visit(const ReadStmt *expr){
    int r;
    std::cin>>r;
    expr->inLocal ? variable_stack.top()[expr->in] = r : global_vars[expr->in] = r;
    return 0;
}

int Interpreter::visit(const FuncDeclStmt *expr){
    for(auto funct : functions){
        if( funct.id == expr->id){
            std::cerr<< " Funcion ya declarada "<< std::endl;
            throw false;
        }
    }
    functions.push_back(*expr);
}
int Interpreter::visit(const FuncCallStmt *expr){
    if( expr->id == "IntToHex"){
        
    }else{
       if(isFuctionDefined(expr->id)){
           int ret=0;
           FuncDeclStmt foundFunc = getFunction(expr->id);
           if(compareArgsSize(foundFunc,expr->args)){
                addArgsToStack(foundFunc,expr->args);
                if(foundFunc.isProcedure){
                    execute(foundFunc.block.get());
                }else{
                    ret = execute(foundFunc.block.get());
                }
                variable_stack.pop();
                return ret;
           }else{
               throw std::string("Verify arguments");
           }
       }else{
           throw std::string("Function Not Defined");
       }
    }
}

int Interpreter::visit(const ReturnExpr * expr){
    return execute(expr->ret.get());
}

bool Interpreter::isFuctionDefined(const std::string&name){
    for(auto &f: functions){
        if(f.id == name) return true;
    }
    return false;
}
void Interpreter::addArgsToStack(const FuncDeclStmt&funct,const std::vector<ExprPtr>&args){
    VARS local;
    int i = 0;
    for(auto &arg: funct.args){
        local.insert( std::make_pair(arg, execute(args[i].get())));
        i++;
    }

    variable_stack.push(local);
}

bool Interpreter::compareArgsSize(const FuncDeclStmt&func,const std::vector<ExprPtr>&args){
    return func.args.size() == args.size();
}

FuncDeclStmt Interpreter::getFunction(const std::string &name) const {
    for(auto &f : functions){
        if(f.id == name) return f;
    }
}