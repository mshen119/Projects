#include "Operator.h"
#include <iostream>
// Implement Operator member functions here.
Operator::Operator(const std::string& token, AST* lhs, AST* rhs){
    mlhs = lhs;
    mrhs = rhs;
    op = token;
}
int Operator::arity() const{
    if(op == "~"){
        return 1;
    }
    else if(op=="+"||op=="-"||op=="/"||op=="*"||op=="^"||op=="%"){
        return 2;
    }
    return 0;
}
int Operator::associativity() const{
    if(op == "+"||op=="-"||op=="/"||op=="*"||op=="%"){
        return -1;
    }
    else if(op=="~"||op=="^"){
        return 1;
    }
    return 0;
}
int Operator::precedence() const{
    //std::cout<<"operator: "<<op<<std::endl;
    if(op=="+"||op=="-"){
        return 1;
    }
    else if(op=="*"||op=="/"||op=="%"){
        return 2;
    }
    else if(op=="~"){
        return 3;
    }
    else if(op=="^"){
        return 4;
    }
    return 5;
}
/*bool Operator::needsParenthesis(){
    int currentPrecedence = this->precedence();
    int rightPrecedence = mrhs->precedence();
    int leftPrecedence = mlhs->precedence();
    if(rightPrecedence<currentPrecedence||leftPrecedence<currentPrecedence){
        return true;
    }
    if(rightPrecedence==currentPrecedence||leftPrecedence==currentPrecedence){
        return false;
    }
    return false;
}*/
std::string Operator::infix() const{
    std::string right = mrhs->infix();
    if(mrhs->precedence()<this->precedence()){
        if(mrhs->precedence()!= 3){
            right = "("+right + ")";
        }
        
    }
    //std::cout<<mrhs->precedence()<<" "<<this->precedence()<<std::endl;
    else if(mrhs->precedence()==this->precedence()){
        if(mrhs->associativity() == -1){
            right = "("+right + ")";
        }
    }
    if(op == "~"){
        return op + " "+ right;
    }
    std::string left = mlhs->infix();
    if(mlhs->precedence()<this->precedence()){
        left = "("+left+")";
    }
    else if(mlhs->precedence()==this->precedence()){
        if(mlhs->associativity() == 1){
            left = "("+left + ")";
        }
    }
    return left + " "+ op + " "+ right;
}
std::string Operator::prefix() const{
    if(op == "~"){
        return "~ "+ mrhs->prefix();
    }
    return 
        op + " "+ mlhs->prefix() + " "+ mrhs->prefix();

}
std::string Operator::postfix() const{
    if(op == "~"){
        return mrhs->postfix()+" ~";
    }
    return 
        mlhs->postfix()+" "+mrhs->postfix()+" "+ op;

}
Operator::~Operator(){
    delete mlhs;
    delete mrhs;
}
