#ifndef NODE
#define NODE

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <cmath>
#include <map>

#define MAX (float)0x7f800000
#define N 1024
#define e (float)2.718282

using namespace std;

class Node
{
public:
    string ty;   //节点类型（记录运算符的种类） 
    string name; //节点名称（字符串类型） 
    float value; //节点所赋值 
    Node * left; //左儿子 
    Node * right;//右儿子 
    Node() {}
    Node(string);
    Node(string, string);
    string output1, output2; //用于COND函数的输出（输出output1或者output2） 
    virtual ~Node() {}
};

class Constant : public Node
{
public:
    Constant(string, float);
};

class Variable : public Node
{
public:
    Variable(string, float);
};

class Placeholder : public Node
{
public:
    Placeholder(string);
    Placeholder(string, float);
};

#endif
