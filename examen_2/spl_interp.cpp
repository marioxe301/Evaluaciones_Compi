#include "spl_interp.h"
#define HANDLE_CASE(n) \
    case Kind::n : return visit(reinterpret_cast<const n*>(expr))

int SplInterp::executeExpr(ASTNode *expr){
    switch (expr->getKind())
    {
    HANDLE_CASE(AssignStmt);
    HANDLE_CASE(AddExpr);
    HANDLE_CASE(DivExpr);
    HANDLE_CASE(MultExpr);
    HANDLE_CASE(SubExpr);
    HANDLE_CASE(EqExpr);
    HANDLE_CASE(DiffExpr);
    HANDLE_CASE(IfStmt);
    HANDLE_CASE(FuncDecl);
    HANDLE_CASE(FuncCall);
    HANDLE_CASE(NumberExpr);
    HANDLE_CASE(VarExpr);
    HANDLE_CASE(SeqStmt);
    }

    return 0;
}

Table SplInterp::exec(ASTNode *root){

    // Recorrer el arbol y al finalizar mostrar la tabla
    executeExpr(root);

    // Retorna la tabla
    return vars;
}

int SplInterp::visit( const AssignStmt *a){
    vars.insert( std::make_pair(a->id, executeExpr(a->expr.get())));
    return 0;
}
int SplInterp::visit( const AddExpr *a){
    int i = executeExpr(a->e_1.get());
    int j = executeExpr(a->e_2.get());
    return i + j;
} 
int SplInterp::visit( const DivExpr *a) {
    int i = executeExpr(a->e_1.get());
    int j = executeExpr(a->e_2.get());
    // validacion de division entre 0
    return !j ?  throw false : i / j;
}
int SplInterp::visit( const MultExpr *a){
    int i = executeExpr(a->e_1.get());
    int j = executeExpr(a->e_2.get());
    return i * j;
}
int SplInterp::visit( const SubExpr *a){
    int i = executeExpr(a->e_1.get());
    int j = executeExpr(a->e_2.get());
    return i * j;
}
int SplInterp::visit( const EqExpr *a){
    int i = executeExpr(a->e_1.get());
    int j = executeExpr(a->e_2.get());
    return i == j;
}
int SplInterp::visit( const DiffExpr *a){
    int i = executeExpr(a->e_1.get());
    int j = executeExpr(a->e_2.get());
    return i != j; 
}
int SplInterp::visit( const IfStmt *a){
    int i = executeExpr(a->cond.get());
    
    i ? executeExpr(a->t.get()) : executeExpr(a->f.get());
    return 0;
}
int SplInterp::visit(const FuncDecl *a){
    
    //Busca si ya se declaro la funcion
    for(auto &funct: functions ){
        if(funct.id == a->id){
            throw false;
        }
    }

    //Reserva la tabla
    for(auto &arg: a->args){
        vars.insert( std::make_pair(arg,0));
    }
    //Declara la funcion
    functions.push_back(*a);
    return 0;
}
int SplInterp::visit(const FuncCall *a){
    for( auto &decl_fun: functions){
        // si no hay funciones y se llama a FuncCall error
        if(functions.empty()){
            throw false;
        }else{
            if(decl_fun.id == a->id){
                 if(decl_fun.args.size() == a->args.size()){
                     //Inicializa las los argumentos
                     for(int i= 0 ; i < decl_fun.args.size();i++){
                         vars[decl_fun.args[i]] = executeExpr(a->args[i].get());
                     }

                     // Luego ejecuta la funcion
                     return executeExpr(decl_fun.body.get());
                 }else{
                     throw false;
                 }
            }
        }
    }
    // si busco y no entro a ningun If error no existe la funcion
    throw false;
}
int SplInterp::visit(const NumberExpr *a){
    return a->value;
}
int SplInterp::visit(const VarExpr *a){
    // Si al final termina el ciclo significa que la variable no existe
    for(auto &i: vars){
        if( i.first == a->id){
            return i.second;
        }
    }
    throw false;
}

int SplInterp::visit(const SeqStmt *a){
    for( auto &s: a->seq){
        executeExpr(s.get());
    }
    return 0;
}