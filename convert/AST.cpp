#include "AST.h"
#include "Number.h"
#include "Operator.h"
#include <iostream>
#include <sstream>
#include <stack>
// Helper functions (recommended):
bool is_operator(const std::string& token){
    return token == "+"||token=="-"||token=="*"||token=="/"||token=="%"||token=="^"||token=="~";
}
bool is_number(const std::string& token){
    double num = 0;
    std::stringstream ts(token);
    ts >> num;
    ts.clear();
    std::string garbage;
    std::getline(ts, garbage);
    if(garbage == ""&&!(is_operator(token))){
        return true;
    }
    return false;
}

AST* AST::parse_prefix(std::istream& tokens) {
    std::string token;
    
    
        if(!(tokens>>token)){
            throw std::runtime_error("Not enough operands.");
        }
        if(!(is_number(token))&&!(is_operator(token))){
            throw std::runtime_error("Invalid token: "+token);
        }
        else if(is_number(token)){
            return new Number(token);
        }
        else{
            if(token == "~"){
                AST* rhs = nullptr;
                try{
                    rhs = AST::parse_prefix(tokens);
                    return new Operator("~",nullptr,rhs);
                }
                catch(...){
                    delete rhs;
                    throw;
                }
            }
            else{
                AST* lhs = nullptr;
                AST* rhs = nullptr;
                try{
                    lhs = AST::parse_prefix(tokens);
                    rhs = AST::parse_prefix(tokens);
                    return new Operator(token, lhs, rhs);
                }
                catch(...){
                    delete lhs;
                    delete rhs;
                    throw;
                }
            }
            
        }
        
      
}

AST* AST::parse_postfix(std::istream& tokens) {
    std::string token;
    std::stack<AST*> st;
    AST* op = nullptr;
    AST* leftNum = nullptr;
    AST* rightNum = nullptr; 
    try{
    while(tokens>>token){
        if(token=="~"){
            //try{
            if(st.empty()){
                throw std::runtime_error("Not enough operands.");
            }else{
                rightNum = st.top();
                st.pop();
            }
           
            op = new Operator(token, nullptr,rightNum);
            st.push(op);
        //}
        /*catch(...){
            delete rightNum;
            throw;
        }*/
        }
        else if(is_number(token)){
            op = new Number(token);
            st.push(op);
        }
        else if(is_operator(token)){
            /*if(token == "~"){
                rightNum = st.top();
                st.pop();
                op = new Operator(token,nullptr,rightNum);
                st.push(op);
            }*/
            //try{
            if(st.empty()){
                throw std::runtime_error("Not enough operands.");
            }else{
                rightNum = st.top();
                st.pop();
            }
            if(st.empty()){
                delete rightNum;
                throw std::runtime_error("Not enough operands.");
                
            }else{
                leftNum = st.top();
                st.pop();
            }
            
            op = new Operator(token,leftNum, rightNum);
            st.push(op);
            //}
            /*catch(...){
                delete rightNum;
                throw;
            }*/
        }else{
            //try{
                throw std::runtime_error("Invalid token: "+ token);
            // std::cerr<<"Invalid token: "<<token<<std::endl;
            // int size = st.size();
            // for(int i = 0; i<size;i++){
            //     st.pop();
                
            // }
            // return nullptr;
            //continue;
            /*try{
                throw token;
            }
            catch(std::string EToken){
                std::cout<<"Invalid token: "<<EToken<<std::endl;
            }*/
            // }
            // catch(...){
            //     delete rightNum;
            //     throw;
            // }
        }     
    }
    int size = st.size();
    //try{
    if(size>1){
        throw std::runtime_error("Too many operands.");
        //std::cerr<<"Too many operands."<<std::endl;
        //return nullptr;
    }
    //}
    // catch(...){
    //     delete rightNum;
    //     throw;
    // }
    if(size==0){
        throw std::runtime_error("Not enough operands.");
    }
   
    /*if(!(st.empty())){
        op = st.top();
        st.pop();
    }*/
    
    return st.top();
    }
    catch(...){
        while(!(st.empty())){
            delete st.top();
            st.pop();
        }
        throw;
    }

}
