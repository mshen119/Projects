#include "Stack.h"
#include "MyStack.h"
#include <iostream>
#include <cmath>
#include <climits>
#include <sstream>
#include <cstring>
#include <string>
#include <vector>
#include <string.h>
#include<ctype.h>
using namespace std;
// TODO: Calculator helper fuctions, if necessary.
bool is_operator(const string& input);
//void performOperation(const string& input, MyStack* stack);
//void write_string(string& input);*/

int main() {
  // TODO: Implement a calculator!
  MyStack* newStack = new MyStack();
  string input;
  while(getline(cin,input)){
    double num = 0;
    double result = 0;
    //double single = 0;
    bool valid = true;
    bool notEmpty = false;
    //bool isOnly = false;
    stringstream ss(input);
    string token;
    
    while(ss>>token){
      std::stringstream ts(token);
      ts >> num;
      ts.clear();
      std::string garbage;
      std::getline(ts, garbage);

      if(garbage == ""&&!(is_operator(token))){
        newStack->push(num);
        notEmpty = true;
        result = num;
        //single = num;
        //valid = false;
        //isOnly = true;
      }
      else if(is_operator(token)){
        double leftVal,rightVal;
        notEmpty = true;
        valid = true;
        //isOnly = false;
        if(token == "+"){
          if(newStack->is_empty()){
            cout<<"Not enough operands."<<endl;
            valid = false;
            //isOnly = false;
            break;
          }else{
            rightVal = newStack->top();
            newStack->pop();
          } 
          if(newStack->is_empty()){
            cout<<"Not enough operands."<<endl;
            valid = false;
            //isOnly = false;
          }else{
            leftVal = newStack->top();
            newStack->pop();
          }
          result = leftVal + rightVal;
        }
        else if(token == "-"){
           if(newStack->is_empty()){
            cout<<"Not enough operands."<<endl;
            valid = false;
            //isOnly = false;
            break;
          }else{
            rightVal = newStack->top();
            newStack->pop();
          } 
          if(newStack->is_empty()){
            cout<<"Not enough operands."<<endl;
            valid = false;
            //isOnly = false;
          }else{
            leftVal = newStack->top();
            newStack->pop();
          }
          result = leftVal - rightVal;
        }
        else if(token == "*"){
           if(newStack->is_empty()){
            cout<<"Not enough operands."<<endl;
            valid = false;
            //isOnly = false;
            break;
          }else{
            rightVal = newStack->top();
            newStack->pop();
          } 
          if(newStack->is_empty()){
            cout<<"Not enough operands."<<endl;
            valid = false;
            //isOnly = false;
          }else{
            leftVal = newStack->top();
            newStack->pop();
          }
          result = leftVal * rightVal;
        }
        else if(token == "/"){
           if(newStack->is_empty()){
            cout<<"Not enough operands."<<endl;
            valid = false;
            //isOnly = false;
            break;
          }else{
            rightVal = newStack->top();
            newStack->pop();
          } 
          if(newStack->is_empty()){
            cout<<"Not enough operands."<<endl;
            valid = false;
            //isOnly = false;
          }else{
            leftVal = newStack->top();
            newStack->pop();
          }
          if(rightVal == 0){
            cout<<"Division by zero."<<endl;
            valid= false;
            break;
          }else{
            result = leftVal / rightVal;
          }
        }
        else if(token == "^"){
           if(newStack->is_empty()){
            cout<<"Not enough operands."<<endl;
            valid = false;
            //isOnly = false;
            break;
          }else{
            rightVal = newStack->top();
            newStack->pop();
          } 
          if(newStack->is_empty()){
            cout<<"Not enough operands."<<endl;
            valid = false;
            //isOnly = false;
          }else{
            leftVal = newStack->top();
            newStack->pop();
          }
          result = pow(leftVal,rightVal);
        }
        else if(token == "%"){
           if(newStack->is_empty()){
            cout<<"Not enough operands."<<endl;
            valid = false;
            //isOnly = false;
            break;
          }else{
            rightVal = newStack->top();
            newStack->pop();
          } 
          if(newStack->is_empty()){
            cout<<"Not enough operands."<<endl;
            valid = false;
            //isOnly = false;
          }else{
            leftVal = newStack->top();
            newStack->pop();
          }
          if(rightVal == 0){
            cout<<"Division by zero."<<endl;
            valid = false;
            break;
            //isOnly = false;
          }else{
            result = fmod(leftVal,rightVal);
          }
        }
        else if(token == "~"){
          if(newStack->is_empty()){
            cout<<"Not enough operands."<<endl;
            valid = false;
            //isOnly = false;
            break;
          }else{
            rightVal = newStack->top();
            newStack->pop();
          }
          rightVal = -rightVal;
          result = rightVal;
        }
         newStack->push(result);
      }
      else{
        notEmpty = true;
        cout << "Unknown token."<<endl;
        valid = false;
        break;
        //isOnly = false;
      }
    }
    if(input == ""||notEmpty ==false){
      cout<<"No expression."<<endl;
      valid = false;
    }
    /*if(isOnly == true){
      cout<<"= "<<single<<endl;
      newStack->clear();
    }*/
    //cout <<newStack->count()<<endl;
    if(valid == false){
      newStack->clear();
      continue;
    }
    if(newStack->count()>1){
      cout<<"Too many operands."<<endl;
      valid = false;
    }
     if(valid == true){
      cout<<"= "<<result<<endl;
    }
    newStack->clear();

     
}
delete newStack;
}
bool is_operator(const string& input){
  string Operations[] = {"+","-","*","/","^","%","~"};
  for(int i = 0; i<7;i++){
    if(input == Operations[i]){
      return true;
    }
  }
  return false;
}

