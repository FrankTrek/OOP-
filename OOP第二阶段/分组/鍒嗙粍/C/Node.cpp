#include "Node.h"

Node::Node(string _name)
{
    value = MAX;
    name = _name;
}

Node::Node(string _name, string ty_name)
{
    value = MAX;  
	name = _name;
    ty = ty_name;
}

Variable::Variable(string _name, float v) //Variable�����Ҷ��Ӷ��ǿ�ָ�� 
{
	value = v; 
    name = _name;
    ty = "V";
    left = nullptr;
    right = nullptr;
}

Constant::Constant(string _name, float v) : Node(_name) //Constant�����Ҷ��Ӷ��ǿ�ָ�� 
{
    value = v;
    ty = "C";
    left = nullptr;
	right = nullptr; 
}

Placeholder::Placeholder(string _name) : Node (_name) //Placeholder�����Ҷ��Ӷ��ǿ�ָ�� 
{
	value = MAX;
    ty = "P";
    left = nullptr;
    right = nullptr;
}

Placeholder::Placeholder(string _name, float v) : Node(_name)
{
    value = v;
    ty = "P";
    left = nullptr;
    right = nullptr;
}
