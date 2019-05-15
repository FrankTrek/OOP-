#include "Operator.h"
#include <cmath>
#include <iostream>
const float ep = 1e-8;

//float为0
bool iszero(float a){
    if(a <= ep && a >= -ep)
    return true;
    return false;
}

//float小于0
bool lesserzero(float a){
    if(a < ep && !iszero(a-ep))
    return true;
    return false;
}

//以下为不同类型操作的cal()
void Add::cal(){
    value = children[0]->getvalue() + children[1]->getvalue();
}

void Sub::cal(){
    value = children[0]->getvalue() - children[1]->getvalue();
}

void Mul::cal(){
    value = children[0]->getvalue() * children[1]->getvalue();
}

void Div::cal(){
    if(iszero(children[1]->getvalue())){
        std::string message = "ERROR: Division by zero";
        gra->errorthrow(message);
        return;
    }
    value = children[0]->getvalue() / children[1]->getvalue();
}

void Sin::cal(){
    value = sin(children[0]->getvalue());
}

void Log::cal(){
    if(lesserzero(children[0]->getvalue()) || iszero(children[0]->getvalue())){
        value = NAN;
        std::string message = "ERROR: LOG operator's input must be positive";
        gra->errorthrow(message);
        return;
    }
    value = log(children[0]->getvalue());
}

void Exp::cal(){
    value = exp(children[0]->getvalue());
}

void Tanh::cal(){
    float a = children[0]->getvalue();
    value = (exp(a) - exp(-a)) / (exp(a) + exp(-a));
}

void Sigmoid::cal(){
    float a = children[0]->getvalue();
    value = 1 / (1 + exp(-a));
}

void Print::cal(){
    std::cout << "PRINT operator: " << children[0]->getname() << " = "<<children[0]->getvalue() << std::endl;
    value = children[0]->getvalue();
}

void Greater::cal(){
    if(children[0]->getvalue() > children[1]->getvalue() && !iszero(children[0]->getvalue() - children[1]->getvalue())){
        value = 1.0;
    }
    else value = 0.0;
}

void Greater_e::cal(){
    if(children[0]->getvalue() > children[1]->getvalue() || iszero(children[0]->getvalue() - children[1]->getvalue())){
        value = 1.0;
    }
    else value =0.0;
}

void Lesser::cal(){
    if(children[0]->getvalue() < children[1]->getvalue() && !iszero(children[0]->getvalue() - children[1]->getvalue())){
        value = 1.0;
    }
    else value = 0.0;
}

void Lesser_e::cal(){
    if(children[0]->getvalue() < children[1]->getvalue() || iszero(children[0]->getvalue() - children[1]->getvalue())){
        value = 1.0;
    }
    else value = 0.0;
}

void Equal::cal(){
    if(iszero(children[0]->getvalue() - children[1]->getvalue())){
        value = 1.0;
    }
    else value = 0.0;
}

void Cond::cal(){
    if(children[0]->getvalue() > -ep && !iszero(children[0]->getvalue())) 
        value = children[1]->getvalue();
    else 
        value =children[2]->getvalue();
}

void Constant::cal(){
    return;
}

void Placeholder::cal(){
    if(std::isnan(value)){
        std::string message = "ERROR: Placeholder missing";
        gra->errorthrow(message);
    }
    return;
}

void Variable::cal(){
    return;
}