#include "AST.h"

#include <iostream>
#include <sstream>
#include <string>
using namespace std;
//int argc, char** argv
int main(int argc, char** argv) {
  // Check your command line arguments...
  
  //cout<<argc<<endl;
  //cout<<input<<" "<<output<<endl;
  if(argc!=3){
    cerr<<"USAGE: convert [input-format] [output-format]"<<endl<<"  Valid input formats:   prefix, postfix"<<endl<<"  Valid output formats:  prefix, infix, postfix"<<endl;
    return 0;
  }
  string input = argv[1];
  string output= argv[2];

  if((input !="prefix"&&input!="postfix")||(output!="prefix"&&output != "postfix"&&output!= "infix")){
    cerr<<"USAGE: convert [input-format] [output-format]"<<endl<<"  Valid input formats:   prefix, postfix"<<endl<<"  Valid output formats:  prefix, infix, postfix"<<endl;
    return 0;
  }
 

  std::string line;
  
  while(std::getline(std::cin, line)) {
    std::istringstream tokens(line);
    // Convert the expression...
    //if(input == "postfix"){
      /*try{

      }
      catch(string e){
        e.what();

      }*/
      //AST * ast = AST::parse_postfix(tokens);

      //if(output == "postfix"){
      //if(ast!=nullptr){
        //cout<<"=> "<<ast->prefix()<<endl;
      //}
      try{
      if(input == "postfix"){
        AST* post = AST::parse_postfix(tokens);
        
        if(output=="postfix"){
          if(post!=nullptr){
            cout<<"=> "<<post->postfix()<<endl;
          }
        }
        if(output=="prefix"){
          if(post!=nullptr){
            cout<<"=> "<<post->prefix()<<endl;
          }
        }
        if(output== "infix"){
          if(post!=nullptr){
            cout<<"=> "<<post->infix()<<endl;
          }
        }
        delete post;
      
      }
      if(input=="prefix"){
        AST* pre = AST::parse_prefix(tokens);
        string extraTokens;
        if(tokens>>extraTokens){
          delete pre;
          throw runtime_error("Too many operands.");
        }
        if(output=="postfix"){
          if(pre!=nullptr){
            cout<<"=> "<<pre->postfix()<<endl;
          }
        }
        if(output=="prefix"){
          if(pre!=nullptr){
            cout<<"=> "<<pre->prefix()<<endl;
          }
        }
        if(output== "infix"){
          if(pre!=nullptr){
            cout<<"=> "<<pre->infix()<<endl;
          }
        }
        delete pre;
      }
      
      }
      catch(const std::exception& e){
        std::cout<<e.what()<<endl;
      }
     
        
    //}
    //}
    
   
    

  }
  return 0;
}
