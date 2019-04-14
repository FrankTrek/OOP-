//
//  Set_Graph.h
//  OOP Computation Graph
//
//  Created by 王一诺 on 2019/4/12.
//  Copyright © 2019 王一诺. All rights reserved.
//

#ifndef Set_Graph_h
#define Set_Graph_h
#include "Node.h"
#include <map>
#include "Const.h"
#include "Operation.h"
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
        void processing_Stage3();                        //对输入字符串的处理  未完成
        void ADD(const string& obj, const string& p1, const string& p2);                //加法操作
        void Multi(const string& obj, const string& p1, const string& p2);               //乘法操作
        void MINUS(const string& obj, const string& p1, const string& p2);               //减法操作
        void Div(const string& obj, const string& p1, const string& p2);                 //除法操作
        void Print(const string& name);           //执行打印操作  未完成
        //假装这里有一吨操作符
        void Compute(const string& a)             //对于表达式进行计算
        {
             float b = graph[a].node->Forward();
             Answer.push_back(b);
             cout<<b<<std::endl;
        }
        void SetAnswer(const string& name, int n)                       //对Variable进行seranswer操作 未完成
        {
            if(Answer[n]<Minus_Max+0.0000001) std::cerr<<"Invalid Operation\n";
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
