#ifndef OPERATOR_H
#define OPERATOR_H

#include "Node.h"
#include<iostream>
#include<cmath>
#include"Tensor.h"
#include <iostream>
#include <iomanip>

// 加法
template <typename T>
class PlusOperator : public Node<T>
{
private:
public:
    PlusOperator(const std::string& InitName, const std::vector<Node<T>*>& InitPre):Node<T>(InitName,0,0){this->Pre = InitPre;}
    T Solve(std::string&ErrorSignal,std::vector<Node<T>*>*  Order_of_Derive = nullptr){
        if (ErrorSignal.size() != 0)    return 0;                        //    有报错信息则终止运算并返回
        T Tempa = this->Pre[0]->Calc(this->GetTime(), ErrorSignal,Order_of_Derive);
        if (ErrorSignal.size() != 0)    return 0;
        T Tempb = this->Pre[1]->Calc(this->GetTime(), ErrorSignal,Order_of_Derive);
        if (ErrorSignal.size() != 0)    return 0;
        return Tempa + Tempb;
    }
    void Backward(T ,std::string&ErrorSignal);
};

//  减法
template <typename T>
class MinusOperator : public Node<T>
{
private:
public:
    MinusOperator(const std::string& InitName, const std::vector<Node<T>*>& InitPre):Node<T>(InitName,0,0){this->Pre = InitPre;}
    T Solve(std::string&ErrorSignal,std::vector<Node<T>*>*  Order_of_Derive = nullptr){
        if (ErrorSignal.size() != 0)    return 0;                        //    有报错信息则终止运算并返回
        T Tempa = this->Pre[0]->Calc(this->GetTime(), ErrorSignal,Order_of_Derive);
        if (ErrorSignal.size() != 0)    return 0;
        T Tempb = this->Pre[1]->Calc(this->GetTime(), ErrorSignal,Order_of_Derive);
        if (ErrorSignal.size() != 0)    return 0;
        return Tempa - Tempb;
    }
    void Backward(T ,std::string&ErrorSignal);
};

// 乘法
template <typename T>
class MultipleOperator : public Node<T>
{
private:
public:
    MultipleOperator(const std::string& InitName, const std::vector<Node<T>*>& InitPre):Node<T>(InitName,0,0){this->Pre = InitPre;}
    T Solve(std::string&ErrorSignal,std::vector<Node<T>*>*  Order_of_Derive = nullptr){
        if (ErrorSignal.size() != 0)    return 0;                        //    有报错信息则终止运算并返回
        T Tempa = this->Pre[0]->Calc(this->GetTime(), ErrorSignal,Order_of_Derive);
        if (ErrorSignal.size() != 0)    return 0;
        T Tempb = this->Pre[1]->Calc(this->GetTime(), ErrorSignal,Order_of_Derive);
        if (ErrorSignal.size() != 0)    return 0;
        return Tempa * Tempb;
    }
    void Backward(T ,std::string&ErrorSignal);
};



// 除法(没有模版化)

class DivisionOperator : public Node<float>
{
private:
public:
    DivisionOperator(const std::string& InitName, const std::vector<Node*>& InitPre);
    float Solve(std::string&ErrorSignal,std::vector<Node<float>*>*  Order_of_Derive = nullptr);
    void Backward(float ,std::string&ErrorSignal);
};

// PRINT(半模版化)（solve 采用特化，Backward 采用模版化）
template <typename T>
class PrintOperator :public Node<T>
{
private:
    std::ostream* OutStream;
public:
    PrintOperator(const std::string& InitName, const std::vector<Node<T>*>& InitPre, std::ostream& InitOut):Node<T>(InitName, 0, 0)
    {
        this->Pre = InitPre;
        OutStream = &InitOut;
    }
    T Solve(std::string&ErrorSignal,std::vector<Node<T>*>*  Order_of_Derive = nullptr)
    {
        return 0;
    }
    
    void Backward(T, std::string &ErrorSignal)
    {
        ErrorSignal= "Not defined Grad for PrintOperator yet!";
    }
    
};




//  SIN
template <typename T>
class SinOperator :public Node<T>
{
private:
public:
    SinOperator(const std::string& InitName, const std::vector<Node<T>*>& InitPre):Node<T>(InitName,0,0) {this->Pre= InitPre;}
    T Solve(std::string& ErrorSignal,std::vector<Node<T>*>*  Order_of_Derive = nullptr){
        if (ErrorSignal.size() != 0)  return 0;
        T Temp = this->Pre[0]->Calc(this->GetTime(), ErrorSignal);
        if (ErrorSignal.size() != 0)  return 0;
        return  std::sin(Temp);
    }
    void Backward(T ,std::string&ErrorSignal);
};

//  EXP
template <typename T>
class ExpOperator :public Node<T>
{
private:
public:
    ExpOperator(const std::string& InitName, const std::vector<Node<T>*>& InitPre):Node<T>(InitName,0,0) {this->Pre= InitPre;}
    T Solve(std::string& ErrorSignal,std::vector<Node<T>*>*  Order_of_Derive = nullptr){
        if (ErrorSignal.size() != 0)  return 0;
        T Temp = this->Pre[0]->Calc(this->GetTime(), ErrorSignal);
        if (ErrorSignal.size() != 0)  return 0;
        return  std::exp(Temp);
    }
    void Backward(T ,std::string&ErrorSignal);
};


//  LOG

template <typename T>
class LogOperator :public Node<T>
{
private:
public:
    LogOperator(const std::string& InitName, const std::vector<Node<T>*>& InitPre):Node<T>(InitName,0,0) {this->Pre= InitPre;}
    T Solve(std::string& ErrorSignal,std::vector<Node<T>*>*  Order_of_Derive = nullptr){
        return 0;
    }
    void Backward(T ,std::string&ErrorSignal);
};

//  TANH
template <typename T>
class TanhOperator :public Node <T>{
private:
public:
    TanhOperator(const std::string& InitName, const std::vector<Node<T>*>& InitPre):Node<T>(InitName, 0,0) {this-> Pre = InitPre;}
    T Solve(std::string& ErrorSignal,std::vector<Node<T>*>*  Order_of_Derive = nullptr){
        if (ErrorSignal.size() != 0)  return 0;
        T Temp = this->Pre[0]->Calc(this->GetTime(), ErrorSignal);
        if (ErrorSignal.size() != 0)  return 0;
        return  std::tanh(Temp);
    }
    void Backward(float ,std::string&ErrorSignal);
};

//  SIGMOID

template <typename T>
class SigmoidOperator :public Node<T> {
private:
public:
    SigmoidOperator(const std::string& InitName, const std::vector<Node<T>*>& InitPre):Node<T>(InitName,0,0){this->Pre = InitPre;}
    T Solve(std::string& ErrorSignal,std::vector<Node<T>*>*  Order_of_Derive = nullptr){
        if (ErrorSignal.size() != 0)  return 0;
        T Temp = this->Pre[0]->Calc(this->GetTime(), ErrorSignal);
        if (ErrorSignal.size() != 0)  return 0;
        return sigmoid<T>(Temp);
    }
    void Backward(float ,std::string&ErrorSignal);
};

//  COND
class CondOperator :public Node<float> {
private:
public:
    CondOperator(const std::string& InitName, const std::vector<Node*>& InitPre);
    float Solve(std::string& ErrorSignal,std::vector<Node<float>*>*  Order_of_Derive = nullptr);
    void Backward(float ,std::string&ErrorSignal);
};

//  >
class GreaterOperator :public Node <float>{
private:
public:
    GreaterOperator(const std::string& InitName, const std::vector<Node*>& InitPre);
    float Solve(std::string& ErrorSignal,std::vector<Node<float>*>*  Order_of_Derive = nullptr);
    void Backward(float ,std::string&ErrorSignal);
};

//  >=
class GreaterEqualOperator :public Node<float> {
private:
public:
    GreaterEqualOperator(const std::string& InitName, const std::vector<Node*>& InitPre);
    float Solve(std::string& ErrorSignal,std::vector<Node<float>*>*  Order_of_Derive = nullptr);
    void Backward(float ,std::string&ErrorSignal);
};

//  <
class LessOperator :public Node <float>{
private:
public:
    LessOperator(const std::string& InitName, const std::vector<Node*>& InitPre);
    float Solve(std::string& ErrorSignal,std::vector<Node<float>*>*  Order_of_Derive = nullptr);
    void Backward(float ,std::string&ErrorSignal);
};

//  <=
class LessEqualOperator :public Node <float>{
private:
public:
    LessEqualOperator(const std::string& InitName, const std::vector<Node*>& InitPre);
    float Solve(std::string& ErrorSignal,std::vector<Node<float>*>*  Order_of_Derive = nullptr);
    void Backward(float ,std::string&ErrorSignal);
};

//  ==
class EqualOperator :public Node <float>{
private:
public:
    EqualOperator(const std::string& InitName, const std::vector<Node*>& InitPre);
    float Solve(std::string& ErrorSignal,std::vector<Node<float>*>*  Order_of_Derive = nullptr);
    void Backward(float ,std::string&ErrorSignal);
};
//——————以下是第二阶段修改中添加的部分

class AssertOperator :public Node<float> {
private:
public:
    AssertOperator(const std::string& InitName, const std::vector<Node*>& InitPre);
    float Solve(std::string& ErrorSignal,std::vector<Node<float>*>*  Order_of_Derive = nullptr);
    void Backward(float ,std::string&ErrorSignal);
};

class BindOperator :public Node <float>{
private:
public:
    BindOperator(const std::string& InitName, const std::vector<Node*>& InitPre);
    float Solve(std::string& ErrorSignal,std::vector<Node<float>*>*  Order_of_Derive = nullptr);
    void Backward(float ,std::string&ErrorSignal);
};

// Add by Cai on 6.6
class GradOperator :public Node <float>{
private:
    std::vector<Node<float>*> * waitinglist;
public:
    GradOperator(const std::string& InitName, const std::vector<Node*>& InitPre, std::vector<Node<float>*>* Order_of_Derive=nullptr);
    float Solve(std::string& ErrorSignal,std::vector<Node<float>*>*  Order_of_Derive = nullptr);
    void Backward(float ,std::string&ErrorSignal);
};
//Grad

class AtOperator: public Node<float>{
private:
public:
    AtOperator(const std::string& InitName, const std::vector<Node*>& InitPre);
    float Solve(std::string& ErrorSignal,std::vector<Node<float>*>*  Order_of_Derive = nullptr);
    void Backward(float ,std::string&ErrorSignal);
};

#endif
