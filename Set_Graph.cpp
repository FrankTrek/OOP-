//
//  Set_Graph.cpp
//  OOP Computation Graph
//
//  Created by 王一诺 on 2019/4/13.
//  Copyright © 2019 王一诺. All rights reserved.
//

#include <stdio.h>
#include "Set_Graph.h"
namespace Computational_Graph{
    
    void Set_Graph::Initalize_Ph(const string& name)               //对于Ph(n名字为name)进行初始化；
    {
        auto x = graph.find(name);
        if(x!=graph.end())
        {
            std::cerr<<"False Redefination\n";
        }
        else
        {
            graph[name].Mode = Placehold;
            graph[name].Nodename = name;
            graph[name].node = std::make_shared<Placeholder>(new Placeholder(name));
        }
    }
    void Set_Graph::Initalize_V(const string& name, float num)               //对于V(n名字为name)进行初始化；
    {
        auto x = graph.find(name);
        if(x!=graph.end())
        {
            std::cerr<<"False Redefination\n";
        }
        else
        {
            graph[name].Nodename = name;
            graph[name].Mode = Varible;
            graph[name].node = std::make_shared<Variable>(new Variable(num,name));
        }
    }
    void Set_Graph::Initalize_C(const string& name, float num)               //对于C(n名字为name)进行初始化；
    {
        auto x = graph.find(name);
        if(x!=graph.end())
        {
            std::cerr<<"False Redefination\n";
        }
        else
        {
            graph[name].Mode = Const;
            graph[name].Nodename = name;
            graph[name].node = std::make_shared<Constant>(new Constant(num,name));
        }
    }
    
    
    void Set_Graph::ADD(const string& obj, const string& p1, const string& p2)
    {
        auto x = graph.find(obj);  auto pt1 = graph.find(p1); auto pt2 = graph.find(p2);
        if(x!=graph.end())           //被重定义错误
        {
            std::cerr<<"False Redefination\n";
        }
        else if (pt2==graph.end()||pt1 == graph.end())
        {
            std::cerr<<"False Parameter defination\n";
        }
        else
        {
            graph[obj].Mode = Operator;
            graph[obj].Nodename = obj;
            BaseNode<float>* para1 = graph[p1].node.get();
            BaseNode<float>* para2 = graph[p1].node.get();
            graph[obj].node = std::make_shared<Addition>(new Addition(obj,para1, para2));
        }
        
    }
    
}
