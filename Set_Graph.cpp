//
//  Set_Graph.cpp
//  OOP Computation Graph
//
//  Created by 王一诺 on 2019/4/13.
//  Copyright © 2019 王一诺. All rights reserved.
//

/*4.21 Cai. 补全了Set_Graph:: Operation类所有构造节点函数
 *4.21 Cai. 用模版重写了Set_Graph:: 里所有的构造节点函数
 
 */
#include <stdio.h>
#include "Set_Graph.h"
#include "Const.h"
#include "Node.h"
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
            graph[name].node = std::make_shared<Placeholder>(name);
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
            graph[name].node = std::make_shared<Variable>(num,name);
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
            graph[name].node = std::make_shared<Constant>(num,name);
        }
    }
    //修改思路，把下面所有的重复代码全部
    /*
    void Set_Graph::ADD(const string& obj, const string& p1, const string& p2)       //加法操作
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
            BaseNode<float>* para2 = graph[p2].node.get();
            graph[obj].node = std::make_shared<Addition>(obj,para1, para2);
        }
        
    }
    void Set_Graph::Multi(const string& obj, const string& p1, const string& p2)   //乘法z操作
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
            BaseNode<float>* para2 = graph[p2].node.get();
            graph[obj].node = std::make_shared<Multiply >(obj,para1, para2);
        }
    }
    
    void Set_Graph::MINUS(const string& obj, const string& p1, const string& p2)     //减法z操作
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
            BaseNode<float>* para2 = graph[p2].node.get();
            graph[obj].node = std::make_shared<Minus >(obj,para1, para2);
        }
    }
    void Set_Graph::Div(const string& obj, const string& p1, const string& p2)     //除法z操作
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
            BaseNode<float>* para2 = graph[p2].node.get();
            graph[obj].node = std::make_shared<Division>(obj,para1, para2);
        }
    }
    
    //add by Cai on 4.21
    void Set_Graph::Cond(const std::string &obj, const std::string &p1, const std::string &p2, const std::string &p3) //cond操作
    {
        auto x = graph.find(obj);
        auto pt1 = graph.find(p1);
        auto pt2 = graph.find(p2);
        auto pt3 = graph.find(p3);
        if(x!=graph.end())           //被重定义错误
        {
            std::cerr<<"False Redefination\n";
        }
        else if (pt3==graph.end()||pt2==graph.end()||pt1 == graph.end())
        {
            std::cerr<<"False Parameter defination\n";
        }
        else {
            graph[obj].Mode = Operator;
            graph[obj].Nodename = obj;
            BaseNode<float>* para1 = graph[p1].node.get();
            BaseNode<float>* para2 = graph[p2].node.get();
            BaseNode<float>* para3 = graph[p3].node.get();
            graph[obj].node = std::make_shared<COND>(obj,para1, para2, para3);
        }
    }
    void Set_Graph::XIAOYU(const string& obj, const string& p1, const string& p2)
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
            BaseNode<float>* para2 = graph[p2].node.get();
            graph[obj].node = std::make_shared<Xiaoyu>(obj,para1, para2);
        }
    }
    */
    //-----------------------------------------------------------------------------------------
    void Set_Graph::Initalize_Op()          //第二阶段的操作
    {//add by Cai on 4.21
        if(info[2]=="+")                 //为加法;
        {
            //ADD(info[0], info[1], info[3]);
            Jianli_2<Addition>(info[0], info[1], info[3]);
        }
        else if(info[2]=="*")                 //为乘法
        {
            //Multi(info[0], info[1], info[3]);
            Jianli_2<Multiply>(info[0], info[1], info[3]);
        }
        else if(info[2]=="-")            //为减法
        {
             //MINUS(info[0], info[1], info[3]);
            Jianli_2<Minus>(info[0], info[1], info[3]);
        }
        else if(info[2]=="/")
        {
            //Div(info[0], info[1], info[3]);
            Jianli_2<Division>(info[0], info[1], info[3]);
        }
        else if(info[2]=="<")
        {
            Jianli_2<Xiaoyu>(info[0], info[1], info[3]);
        }
        else if(info[2]=="<=")
        {
            Jianli_2<Xiaodeng>(info[0], info[1], info[3]);
        }
        else if(info[2]==">")
        {
            Jianli_2<Dayu>(info[0], info[1], info[3]);
        }
        else if(info[2]==">=")
        {
            Jianli_2<Dadeng>(info[0], info[1], info[3]);
        }
        else if(info[2]=="==")
        {
            Jianli_2<Dengyu>(info[0], info[1], info[3]);
        }
        else if(info[2]=="==")
        {
            Jianli_2<Budeng>(info[0], info[1], info[3]);
        }
        else if(info[1]=="SIN")
        {
            Jianli_1<SIN>(info[0], info[2]);
        }
        else if(info[1]=="LOG")
        {
            Jianli_1<LOG>(info[0], info[2]);
        }
        else if(info[1]=="TANH")
        {
            Jianli_1<TANH>(info[0], info[2]);
        }
        else if(info[1]=="EXP")
        {
            Jianli_1<EXP>(info[0], info[2]);
        }
        else if(info[1]=="SINGMOID")
        {
            Jianli_1<SINGMOID>(info[0], info[2]);
        }
        else if(info[1]=="Print")
        {
            Jianli_1<Print>(info[0], info[2]);
        }
        else if(info[1]=="COND")
        {
            Jianli_3<COND>(info[0], info[2], info[3], info[4]);
        }
    }
    
    void Set_Graph::processing_Stage3()
    {
        if(info[0]=="EVAL")
        {
            int times = atoi(info[2].data());     //读取操作次数
            for(int i = 1; i<= times; i++)
            {
                int pos = 2+(i-1)*2 + 1;       //此时读取的位置
                string name = info[pos];
                float num = atof(info[pos+1].data());
                if(graph[name].Mode!=Placehold) std::cerr<<"Can not Initalize a non-PlaceHolder Object\n";
                else graph[name].node->Initalize(num);
            }
            Compute(info[1]);
        }
        else if(info[0]=="SETCONSTANT")
        {
            string name = info[1];   //获得名字
            float num = atof(info[2].data());
            if(graph[name].Mode!=Varible) std::cerr<<"Can not setconstant a non-Varible Object\n";
            else
            {
                graph[name].node->Initalize(num);
            }
            Answer.push_back(Minus_Max);
        }
        else if(info[0]=="SETANSWER")
        {
            string name = info[1];   //获得名字
            int n = atoi(info[2].data()); //获得第n次的值
            SetAnswer(name, n);
            Answer.push_back(Minus_Max);
        }
    }
    
}
