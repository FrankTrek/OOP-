#include "Node.h"
#include <cmath>
#include <iostream>

//递归计算
float Node::eval(){
    //如果该节点已算过，则返回对应value
    if(caled){
        return value;
    }
    //如果没有算过，则对子节点递归
    for(auto child : children){
        child->eval();
    }
    cal();
    caled = true;
    gra->caleds.push_back(this);
    return value;
};

//修改value
void Node::setvalue(float a){
    value = a;
}

//返回value
float Node::getvalue(){
    return value;
}

//返回名称
std::string Node::getname(){
    return name;
}
