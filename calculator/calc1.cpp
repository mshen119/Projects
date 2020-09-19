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
bool is_operator(const string& input);
int main(){
  //MyStack* newStack = new MyStack();
    string input;
    vector<string> tokens;
    stringstream check(input);
    string intermediate;
    while(getline(check, intermediate, ' ')){
        tokens.push_back(intermediate);
    }

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