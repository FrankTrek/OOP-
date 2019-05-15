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
    string ty;   //�ڵ����ͣ���¼����������ࣩ 
    string name; //�ڵ����ƣ��ַ������ͣ� 
    float value; //�ڵ�����ֵ 
    Node * left; //����� 
    Node * right;//�Ҷ��� 
    Node() {}
    Node(string);
    Node(string, string);
    string output1, output2; //����COND��������������output1����output2�� 
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
