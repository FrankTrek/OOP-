#ifndef SCALAR_H
#define SCALAR_H

#include "Node.h"

//	����

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

//	ռλ��
template <typename T>
class Placeholder : public Node<T>
{
private:
public:
    Placeholder(const std::string& InitName):Node<T>(InitName, 0,0) {}
    T Solve(std::string& ErrorSignal){
        ErrorSignal = "Placeholder missing";                //    ����Ҫ����ĳ�����������ռλ������ֵ�������Ǹ������߿���ֱ�ӻ����ȡֵ����
        return 0;    
    }
    void Backward (float , std::string &);
};

//	����
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
