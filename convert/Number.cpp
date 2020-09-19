#include "Number.h"

// Implement Number member functions here.
Number::Number(const std::string& token){
    mValue = std::stod(token);
}
int Number::arity() const{
    return 0;
}
int Number::associativity() const{
    return 0;
}
int Number::precedence() const{
    return 5;
}
std::string Number::infix() const{
    return to_string();

}
std::string Number::postfix() const{
    return to_string();
    
}
std::string Number::prefix() const{
    return to_string();
    
}
std::string Number::to_string() const{
    std::ostringstream s;
    s<<mValue;
    return s.str();
}