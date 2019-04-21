//
//  Set_Graph.h
//  OOP Computation Graph
//
//  Created by 王一诺 on 2019/4/12.
//  Copyright © 2019 王一诺. All rights reserved.
//

/*
 *4.13 Cai. 补充极小量eps
 *4.21 Cai. 补全了Set_Graph:: Operation类所有构造函数
 */


#ifndef Set_Graph_h
#define Set_Graph_h
#include "Node.h"
#include <map>
#include "Const.h"
#include "Operation.h"
#include "Operation2.h"
namespace Computational_Graph{
    class Set_Graph{
        typedef Graph_Node<float> GNode;
        std::map<string, GNode> graph;          //图
        std::vector<string> info;              //处理的信息
        std::vector<float> Answer;             //输出的信息
    public:
        Set_Graph() {}
        Set_Graph(std::vector<string> && a)       //直接传入信息的构造函数
        {
            info = std::move(a);
        }
        void Input_info(std::vector<string> && a) //传入信息
        {
            info = std::move(a);
        }
        void processing_Stage3();//对输入字符串的处理  未完成
        /*
         注意这里是修改
        void ADD(const string& obj, const string& p1, const string& p2);                //加法操作
        void Multi(const string& obj, const string& p1, const string& p2);               //乘法操作
        void MINUS(const string& obj, const string& p1, const string& p2);               //减法操作
        void Div(const string& obj, const string& p1, const string& p2);                 //除法操作
        void Print(const string& name);//执行打印操作  未完成
        //假装这里有一吨操作符
        //add by Cai on 4.21
        void Cond(const string& obj, const string &p1, const string& p2, const string& p3);//Cond 操作
        void XIAOYU (const string& obj, const string& p1, const string& p2);
        void XIAODENG (const string& obj, const string& p1, const string& p2);
        void DAYU (const string& obj, const string& p1, const string& p2);
        void DADENG (const string& obj, const string& p1, const string& p2);
        void DENGYU (const string& obj, const string& p1, const string& p2);
        void BUDENG (const string& obj, const string& p1, const string& p2);
        
        void Sin(const string& obj, const string &p1);
        void Exp(const string& obj, const string &p1);
        void Tanh(const string& obj, const string &p1);
        void Log(const string& obj, const string &p1);
        void Sigmoid(const string& obj, const string &p1);
        void Print(const string& obj, const string &p1);
         */
        //----------------------------------------------------------------------------
        //4.21 针对代码重复过于严重，我要换一个写法
        template <class A>
        void Jianli_2(const string& obj, const string& p1, const string& p2)
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
                graph[obj].node = std::make_shared<A>(obj,para1, para2);
            }
        }
        template <class A>
        void Jianli_1(const string& obj, const string& p1)
        {
            auto x = graph.find(obj);  auto pt1 = graph.find(p1);
            if(x!=graph.end())           //被重定义错误
            {
                std::cerr<<"False Redefination\n";
            }
            else if (pt1 == graph.end())
            {
                std::cerr<<"False Parameter defination\n";
            }
            else
            {
                graph[obj].Mode = Operator;
                graph[obj].Nodename = obj;
                BaseNode<float>* para1 = graph[p1].node.get();
                graph[obj].node = std::make_shared<A>(obj,para1);
            }
        }
        template <class A>
        void Jianli_3(const string& obj, const string& p1, const string& p2,const string & p3)
        {
            auto x = graph.find(obj);  auto pt1 = graph.find(p1); auto pt2 = graph.find(p2); auto pt3= graph.find(p3);
            if(x!=graph.end())           //被重定义错误
            {
                std::cerr<<"False Redefination\n";
            }
            else if (pt3==graph.end()||pt2==graph.end()||pt1 == graph.end())
            {
                std::cerr<<"False Parameter defination\n";
            }
            else
            {
                graph[obj].Mode = Operator;
                graph[obj].Nodename = obj;
                BaseNode<float>* para1 = graph[p1].node.get();
                BaseNode<float>* para2 = graph[p2].node.get();
                BaseNode<float>* para3 = graph[p2].node.get();
                graph[obj].node = std::make_shared<A>(obj,para1, para2,para3);
            }
        }
        
        
        //----------------------------------------------------------------------------
        void Compute(const string& a)             //对于表达式进行计算
        {
             float b = graph[a].node->Forward();
             Answer.push_back(b);
             cout<<b<<std::endl;
        }
        void SetAnswer(const string& name, int n)                       //对Variable进行seranswer操作 未完成
        {
            if(Answer[n]<=Minus_Max+eps) std::cerr<<"Invalid Operation\n";
            else if(graph[name].Mode== Varible) graph[name].node->Initalize(Answer[n]);
            else std::cerr<<"Set_answer option only for Varible\n";            //如果不为Varible则报错
        }
        void Initalize_PVC();                          //未完成
        void Initalize_Op();                           //未完成
        void Initalize_Ph(const string& name);               //对于Ph(n名字为name)进行初始化；
        void Initalize_V(const string& name, float num);               //对于V(n名字为name)进行初始化；
        void Initalize_C(const string& name, float num);               //对于C(n名字为name)进行初始化；
        void Initalize_Input(const string& name, float num)           //在第三阶段对于输入进行初始化;
        {
           if(graph[name].Mode==Placehold) graph[name].node->Initalize(num);
           else std::cerr<<"Invalid Operation\n";
        }
        bool IsValid(const string& name)           //关于这个节点建立是否合法
        {
            return graph[name].node->IsCycle(graph[name].Nodename);
        }
        
    };
}

#endif /* Set_Graph_h */
