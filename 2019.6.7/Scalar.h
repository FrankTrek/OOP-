#ifndef SCALAR_H
#define SCALAR_H

#include "Node.h"

//	±‰¡ø

template <typename T>
class Variable: public Node<T>
{
private:
public:
    Variable(const std::string& InitName, const T& InitValue):Node<T>(InitName,InitValue,0){}
    T Solve(std::string& ErrorSignal,std::vector<Node<T>*>*  Order_of_Derive = nullptr){
        return this->GetValue();
    }
    void Backward (T , std::string &);
};

//	’ºŒª∑˚
template <typename T>
class Placeholder : public Node<T>
{
private:
public:
    Placeholder(const std::string& InitName):Node<T>(InitName, 0,0) {}
    T Solve(std::string& ErrorSignal,std::vector<Node<T>*>*  Order_of_Derive = nullptr){
        ErrorSignal = "Placeholder missing";                //    »Ù–Ë“™º∆À„ƒ≥Ω·µ„À˘“¿¿µµƒ’ºŒª∑˚Ω·µ„µƒ÷µ£®∂¯≤ª «∏¯≥ˆªÚ’ﬂø…“‘÷±Ω”ªÒµ√∆‰»°÷µ£©£¨
        return 0;    
    }
    void Backward (float , std::string &);
};

//	≥£¡ø
template <typename T>
class Constant : public Node<T>
{
private:
public:
    Constant(const std::string& InitName, const T& InitValue):Node<T> (InitName, InitValue ,0 ){}
    T Solve(std::string& ErrorSignal,std::vector<Node<T>*>*  Order_of_Derive = nullptr){
        
        return this->GetValue();
    }
    void Backward (float , std::string &);
};
#endif
