#pragma once
#include "Graph.h"
#include <string>
#include <vector>
#include <cmath>
#include <iostream>

class Graph;

class Node{
private:
    std::string name;               //变量名称
    bool caled = false;             //是否被计算过
protected:
    float value = NAN;              //值    
    std::vector<Node*> children;    //子节点vector 
    Graph* gra;                     //对应的图
public:
    Node(){}
    Node(std::string a, Graph*c) : name(a),gra(c) {}
    Node(std::string a, std::vector<Node*> b, Graph* c) : name(a), children(b), gra(c) {}
    Node(std::string a, float b, Graph* c) : name(a), value(b), gra(c) {}
    virtual void cal() = 0;
    float eval();
    void setvalue(float a);
    float getvalue();
    std::string getname();
    virtual bool notconst() = 0;
    ~Node(){}
    friend Graph;
};
