#include "parser.h"

void Parser::parse(){
    setCurrentToken();
    program();
    if(currentTokenType != Token::Eof) HANDLE_ERROR("Unexpected Token");
    OUT("Grammatica Correcta");
}

void Parser::program(){
    if(isSameToken(Token::KwProgram)){
        setCurrentToken();
        if(isSameToken(Token::Identifier)){
            setCurrentToken();
            if(isSameToken(Token::SemiColon)){
                setCurrentToken();
                VariableSection();
                while(true){
                    if(isSameToken(Token::KwBeg)){ setCurrentToken(); break;}
                    SubprogramDecl();
                }
                while(true){
                    if(isSameToken(Token::KwEnd)){
                        setCurrentToken();
                        break;
                    }
                    Statement();
                }
                if(isSameToken(Token::Dot)){
                    setCurrentToken();
                }else{
                    HANDLE_ERROR("Expected a . but found -> '"+currentToken +"' in line number: " +lexer.getLineNumber());
                }
            }
            
        }
    }else{
        HANDLE_ERROR("Expected Program Word");
    }
}
void Parser::VariableSection(){
    if(isSameToken(Token::KwVar)){
        setCurrentToken();
        VariableDecl();
    }else{
        /* Epsilon */
    }
}
void Parser::VariableDecl(){
    while(true){
        if(isSameToken(Token::Identifier)){
            setCurrentToken();
            if(isSameToken(Token::Coma)){
                setCurrentToken();
                if(isSameToken(Token::Colon)){
                    HANDLE_ERROR("Expected another Variable declaration ");
                }
                continue;
            }else if(isSameToken(Token::Colon)){
                setCurrentToken();
                break;
            }
        }
    }
    Type();
    if(isSameToken(Token::SemiColon)){
        setCurrentToken();
        if(currentTokenType == Token::Identifier){
            VariableDecl(); // Recursion
        }
    }else{
        HANDLE_ERROR("Expected a ; but found -> '"+currentToken +"' in line number: " +lexer.getLineNumber());
    }
}
void Parser::Type(){
    if(isSameToken(Token::KwInteger)){
        setCurrentToken();
    }else if(isSameToken(Token::KwBool)){
        setCurrentToken();
    }else if(isSameToken(Token::KwChar)){
        setCurrentToken();
    }else if(isSameToken(Token::KwArray)){
        setCurrentToken();
        ArrayBody();
    }else{
        HANDLE_ERROR("Unexpected type -> '" + currentToken);
    }
}
void Parser::ArrayBody(){
    if(isSameToken(Token::OpenBracket)){
        setCurrentToken();
        if(isSameToken(Token::DecimalConst)){
            setCurrentToken();
            if(isSameToken(Token::DoublePoint)){
                setCurrentToken();
                if(isSameToken(Token::DecimalConst)){
                    setCurrentToken();
                    if(isSameToken(Token::CloseBracket)){
                        setCurrentToken();
                        if(isSameToken(Token::KwOf)){
                            setCurrentToken();
                            Type();
                        }else{
                            HANDLE_ERROR("Expected an Of word but found -> '"+currentToken +"' in line number: " +lexer.getLineNumber());
                        }
                    }else{
                        HANDLE_ERROR("Expected ] but found-> '"+currentToken +"' in line number: " +lexer.getLineNumber());
                    }
                }else{
                    HANDLE_ERROR("Expected a DecimalConst but found -> '"+currentToken +"' in line number: " +lexer.getLineNumber());
                }
            }else{
                HANDLE_ERROR("Expected a .. but found -> '"+currentToken +"' in line number: " +lexer.getLineNumber());
            }
        }else{
            HANDLE_ERROR("Expected a DecimalConst but found -> '"+currentToken +"' in line number: " +lexer.getLineNumber());
        }
    }else{
        HANDLE_ERROR("Expected [ but found-> '"+currentToken +"' in line number: " +lexer.getLineNumber());
    }
}

void Parser::SubprogramDecl(){
    SubprogramHeader();
    VariableSection();
    if(isSameToken(Token::KwBeg)){
        setCurrentToken();
        while(true){
            if(isSameToken(Token::KwEnd)){ setCurrentToken(); break;}
            Statement();
        }
        if(isSameToken(Token::SemiColon)){
            setCurrentToken();
        }else{
            HANDLE_ERROR("Expected a ; but found -> '"+currentToken +"' in line number: " +lexer.getLineNumber());
        }
    }else{
        HANDLE_ERROR("Expected a 'Begin' but found -> '"+currentToken +"' in line number: " +lexer.getLineNumber());
    }
}

void Parser::SubprogramHeader(){
    if(isSameToken(Token::KwFunc)){
        setCurrentToken();
        FunctionBody();
    }else if(isSameToken(Token::KwProc)){
        setCurrentToken();
        ProcedureBody();
    }else{
        HANDLE_ERROR("Expected a 'Function' or 'Procedure' but found -> '"+currentToken +"' in line number: " +lexer.getLineNumber());
    }
}
void Parser::FunctionBody(){
    if(isSameToken(Token::Identifier)){
        setCurrentToken();
        FunctOrProcArgs();
        if(isSameToken(Token::Colon)){
            setCurrentToken();
            Type();
            if(isSameToken(Token::SemiColon)){
                setCurrentToken();
            }else{
                HANDLE_ERROR("Expected a ; but found -> '"+currentToken +"' in line number: " +lexer.getLineNumber());
            }
        }else{
            HANDLE_ERROR("Expected : but found -> '"+currentToken +"' in line number: " +lexer.getLineNumber());
        }
    }else{
        HANDLE_ERROR("Expecteda ID but found -> '"+currentToken +"' in line number: " +lexer.getLineNumber());
    }
}
void Parser::ProcedureBody(){
    if(isSameToken(Token::Identifier)){
        setCurrentToken();
        FunctOrProcArgs();
        if(isSameToken(Token::SemiColon)){
            setCurrentToken();
        }else{
            HANDLE_ERROR("Expected a ; but found -> '"+currentToken +"' in line number: " +lexer.getLineNumber());
        }
    }else{
        HANDLE_ERROR("Expected a ID but found -> '"+currentToken +"' in line number: " +lexer.getLineNumber());
    }
}

void Parser::FunctOrProcArgs(){
    if(isSameToken(Token::OpenParen)){
        setCurrentToken();
        while(true){
            if(isSameToken(Token::CloseParen)){
                setCurrentToken();
                break;
            }else if(isSameToken(Token::Identifier)){
                setCurrentToken();
                ArgumentBodyId();
            }else if(isSameToken(Token::KwVar)){
                setCurrentToken();
                ArgumentBodyVar();
            }else if(isSameToken(Token::Coma)){
                setCurrentToken();
                if(isSameToken(Token::CloseParen)){
                    HANDLE_ERROR("Expected another Arg ");
                }
                continue;
            }else{
                HANDLE_ERROR("Expected a ID or Var word but found -> '"+currentToken +"' in line number: " +lexer.getLineNumber());
            }
        }
    }else{
        HANDLE_ERROR("Expected a ( but found -> '"+currentToken +"' in line number: " +lexer.getLineNumber());
    }
}

void Parser::ArgumentBodyVar(){
    if(isSameToken(Token::Identifier)){
        setCurrentToken();
        if(isSameToken(Token::Colon)){
            setCurrentToken();
            Type();
        }else{
            HANDLE_ERROR("Expected a : but found -> '"+currentToken +"' in line number: " +lexer.getLineNumber());
        }
    }else{
        HANDLE_ERROR("Expected a ID but found -> '"+currentToken +"' in line number: " +lexer.getLineNumber());
    }
}
void Parser::ArgumentBodyId(){
    if(isSameToken(Token::Colon)){
        setCurrentToken();
        Type();
    }else{
        HANDLE_ERROR("Expected a : but found -> '"+currentToken +"' in line number: " +lexer.getLineNumber());
    }
}
void Parser::Statement(){
    if(isSameToken(Token::KwIf)){
        setCurrentToken();
        Expr();
        if(isSameToken(Token::KwThen)){
            setCurrentToken();
            Block();
            ElseStmt();
        }else{
            HANDLE_ERROR("Expected Then word but found ->"+currentToken +"' in line number: " +lexer.getLineNumber());
        }
    }else if(isSameToken(Token::KwWhile)){
        setCurrentToken();
        Expr();
        if(isSameToken(Token::KwDo)){
            setCurrentToken();
            Block();
        }else{
            HANDLE_ERROR("Expected a do word but found -> '"+currentToken +"' in line number: " +lexer.getLineNumber());
        }
    }else if(isSameToken(Token::KwRepeat)){
        setCurrentToken();
        Block();
        if(isSameToken(Token::KwUntil)){
            setCurrentToken();
            Expr();
            if(isSameToken(Token::SemiColon)){
                setCurrentToken();
            }else{
                HANDLE_ERROR("Expected a ; but found -> '"+currentToken +"' in line number: " +lexer.getLineNumber());
            }
        }else{
            HANDLE_ERROR("Expected an Until word but found -> '"+currentToken +"' in line number: " +lexer.getLineNumber());
        }
    }else if(isSameToken(Token::KwFor)){
        setCurrentToken();
        AssignFor();
        Expr();
        if(isSameToken(Token::KwTo)){
            setCurrentToken();
            Expr();
            if(isSameToken(Token::KwDo)){
                setCurrentToken();
                Block();
            }else{
                HANDLE_ERROR("Expected a do Word -> '"+currentToken +"' in line number: " +lexer.getLineNumber());
            }
        }else{
            HANDLE_ERROR("Expected a To word but found -> '"+currentToken +"' in line number: " +lexer.getLineNumber());
        }

    }else if(isSameToken(Token::KwBreak)){
        setCurrentToken();
        if(isSameToken(Token::SemiColon)){
            setCurrentToken();
        }else{
            HANDLE_ERROR("Expected a ; -> '"+currentToken +"' in line number: " +lexer.getLineNumber());
        }
    }else if(isSameToken(Token::KwContinue)){
        setCurrentToken();
        if(isSameToken(Token::SemiColon)){
            setCurrentToken();
        }else{
            HANDLE_ERROR("Expected a ; -> '"+currentToken +"' in line number: " +lexer.getLineNumber());
        }
    }else if(isSameToken(Token::SemiColon)){
        setCurrentToken();
    }else{
        AssignOrSubProg();
    }
}
void Parser::ElseStmt(){
    if(isSameToken(Token::KwElse)){
        setCurrentToken();
        Block();
    }else{
        /* Epsilon */
    }
}
void Parser::Block(){
    if(isSameToken(Token::KwBeg)){
        setCurrentToken();
        while(true){
            if(isSameToken(Token::KwEnd)){
                setCurrentToken();
                break;
            }
            Statement();
        }
    }else{
        Statement();
    }
}
void Parser::AssignOrSubProg(){
    if(isSameToken(Token::KwPrint)){
        setCurrentToken();
        IoBody();
        if(isSameToken(Token::SemiColon)){
            setCurrentToken();
        }else{
            HANDLE_ERROR("Expected a ; but found a -> '"+currentToken +"' in line number: " +lexer.getLineNumber());
        }
    }else if(isSameToken(Token::KwPrintLn)){
        setCurrentToken();
        IoBody();
        if(isSameToken(Token::SemiColon)){
            setCurrentToken();
        }else{
            HANDLE_ERROR("Expected a ; but found a -> '"+currentToken +"' in line number: " +lexer.getLineNumber());
        }
    }else if(isSameToken(Token::KwRead)){
        setCurrentToken();
        IoBody();
        if(isSameToken(Token::SemiColon)){
            setCurrentToken();
        }else{
            HANDLE_ERROR("Expected a ; but found a -> '"+currentToken +"' in line number: " +lexer.getLineNumber());
        }
    }else if(isSameToken(Token::Identifier)){
        setCurrentToken();
        AssignOrSubProgP();
        if(isSameToken(Token::SemiColon)){
            setCurrentToken();
        }else{
            HANDLE_ERROR("Expected a ; but found a -> '"+currentToken +"' in line number: " +lexer.getLineNumber());
        }
    }else{
        HANDLE_ERROR("Expected an ID or Print or Read but found -> '"+currentToken +"' in line number: " +lexer.getLineNumber());
    }
}
void Parser::AssignOrSubProgP(){
    if(isSameToken(Token::OpenBracket)){
        setCurrentToken();
        Expr();
        if(isSameToken(Token::CloseBracket)){
            setCurrentToken();
            if(isSameToken(Token::Assign)){
                setCurrentToken();
                Expr();
            }else{
                HANDLE_ERROR("Expected a := but found -> '"+currentToken +"' in line number: " +lexer.getLineNumber());
            }
        }else{
            HANDLE_ERROR("Expected a ] but found -> '"+currentToken +"' in line number: " +lexer.getLineNumber());
        }
    }else if(isSameToken(Token::OpenParen)){
        setCurrentToken();
        while(true){
            if(isSameToken(Token::CloseParen)){ setCurrentToken(); break;}
            Expr();
            if(isSameToken(Token::Coma)){
                 setCurrentToken();
                 continue;
            }else if(isSameToken(Token::CloseParen)){ setCurrentToken(); break;}
        }
    }else if(isSameToken(Token::Assign)){
        setCurrentToken();
        Expr();
    }else{
        /* Epsilon */
    }
}
void Parser::IoBody(){
    int arg = 0;
    if(isSameToken(Token::OpenParen)){
        setCurrentToken();
        while(true){
            if(isSameToken(Token::CloseParen) && !arg){ HANDLE_ERROR("Expected more args "); }
            Argument();
            arg++;
            if(isSameToken(Token::Coma)){ 
                setCurrentToken();
                continue;
            }else if(isSameToken(Token::CloseParen)){
                setCurrentToken();
                break;
            }
        }
    }else{
        HANDLE_ERROR("Expected a ( but found -> '"+currentToken +"' in line number: " +lexer.getLineNumber());
    }
}
void Parser::Argument(){
    if(isSameToken(Token::StringConst)){
        setCurrentToken();
    }else{
        Expr();
    }
}
void Parser::AssignFor(){
    if(isSameToken(Token::Identifier)){
        setCurrentToken();
        ArrayVar();
        if(isSameToken(Token::Assign)){
            setCurrentToken();
            Expr();
            if(isSameToken(Token::SemiColon)){
                setCurrentToken();
            }else{
                HANDLE_ERROR("Expected a ; but found a -> '"+currentToken +"' in line number: " +lexer.getLineNumber());
            }
        }else{
            HANDLE_ERROR("Expected a := but found a -> '"+currentToken +"' in line number: " +lexer.getLineNumber());
        }
    }else{
        HANDLE_ERROR("Expected an ID but found a -> '"+currentToken +"' in line number: " +lexer.getLineNumber());
    }
}
void Parser::ArrayVar(){
    if(isSameToken(Token::OpenBracket)){
        setCurrentToken();
        Expr();
    }else{
        /* Epsilon */
    }
}

void Parser::FuncArgs(){
    if(isSameToken(Token::OpenParen)){
        setCurrentToken();
        while(true){
            if(isSameToken(Token::CloseParen)){ setCurrentToken(); break;}
            Expr();
            if(isSameToken(Token::Coma)){ 
                setCurrentToken();
                continue;
            }else if(isSameToken(Token::CloseParen)){
                setCurrentToken();
                break;
            }
        }
    }else if(isSameToken(Token::OpenBracket)){
        setCurrentToken();
        Expr();
        if(isSameToken(Token::CloseBracket)){
            setCurrentToken();
        }else{
             HANDLE_ERROR("Expected an ] but found a -> '"+currentToken +"' in line number: " +lexer.getLineNumber());
        }
    }else{
        /*Epsilon*/
    }
}

void Parser::Expr(){
    Rel();
    while (true)
    {
        if(isSameToken(Token::Equal)){
            setCurrentToken();
            Rel();
        }else if(isSameToken(Token::Different)){
            setCurrentToken();
            Rel();
        }else if(isSameToken(Token::LessThan)){
            setCurrentToken();
            Rel();
        }else if(isSameToken(Token::LessThanEq)){
            setCurrentToken();
            Rel();
        }else if(isSameToken(Token::GreaterThan)){
            setCurrentToken();
            Rel();
        }else if(isSameToken(Token::GreaterThanEq)){
            setCurrentToken();
            Rel();
        }else{
            break;
        }
    }
    
}
void Parser::Rel(){
    Term();
    while (true)
    {
        if(isSameToken(Token::Plus)){
            setCurrentToken();
            Term();
        }else if(isSameToken(Token::Minus)){
            setCurrentToken();
            Term();
        }else if(isSameToken(Token::KwOr)){
            setCurrentToken();
            Term();
        }else if(isSameToken(Token::KwXor)){
            setCurrentToken();
            Term();
        }else{
            break;
        }
    }
    
}
void Parser::Term(){
    Neg();
    while(true){
        if(isSameToken(Token::Mult)){
            setCurrentToken();
            Neg();
        }else if(isSameToken(Token::KwDiv)){
            setCurrentToken();
            Neg();
        }else if(isSameToken(Token::KwMod)){
            setCurrentToken();
            Neg();
        }else if(isSameToken(Token::KwAnd)){
            setCurrentToken();
            Neg();
        }else if(isSameToken(Token::KwShl)){
            setCurrentToken();
            Neg();
        }else if(isSameToken(Token::KwShr)){
            setCurrentToken();
            Neg();
        }else{
            break;
        }
    }
}
void Parser::Neg(){
    if(isSameToken(Token::KwNot)){
        setCurrentToken();
        Factor();
    }else{
        Factor();
    }
}
void Parser::Factor(){
    if(isSameToken(Token::DecimalConst)){
        setCurrentToken();
    }else if(isSameToken(Token::BinaryConst)){
        setCurrentToken();
    }else if(isSameToken(Token::BoolConst)){
        setCurrentToken();
    }else if(isSameToken(Token::HexConst)){
        setCurrentToken();
    }else if(isSameToken(Token::CharConst)){
        setCurrentToken();
    }else if(isSameToken(Token::Identifier)){
        setCurrentToken();
        FuncArgs();
    }else if(isSameToken(Token::OpenParen)){
        setCurrentToken();
        Expr();
        if(isSameToken(Token::CloseParen)){
            setCurrentToken();
        }else{
            HANDLE_ERROR("Expected ) but found -> '"+currentToken +"' in line number: " +lexer.getLineNumber());
        }
    }else{
        HANDLE_ERROR("Expected Numeric const or ID or ( but found -> '"+currentToken +"' in line number: " +lexer.getLineNumber());
    }
}