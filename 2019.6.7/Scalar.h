#ifndef SCALAR_H
#define SCALAR_H

#include "Node.h"

//	变量

template <typename T>
class Variable: public Node<T>
{
private:
public:
    Variable(const std::string& InitName, const T& InitValue):Node<T>(InitName,InitValue,0){}
    T Solve(std::string& ErrorSignal){
        return this->GetValue();
    }
    void Backward (T , std::string &);
};

//	占位符
template <typename T>
class Placeholder : public Node<T>
{
private:
public:
    Placeholder(const std::string& InitName):Node<T>(InitName, 0,0) {}
    T Solve(std::string& ErrorSignal){
        ErrorSignal = "Placeholder missing";                //    若需要计算某结点所依赖的占位符结点的值（而不是给出或者可以直接获得其取值），
        return 0;    
    }
    void Backward (float , std::string &);
};

//	常量
template <typename T>
class Constant : public Node<T>
{
private:
public:
    Constant(const std::string& InitName, const float& InitValue):Node<T> (InitName, InitValue ,0 ){}
    T Solve(std::string& ErrorSignal){
        
        return this->GetValue();
    }
    void Backward (float , std::string &);
};
#endif
