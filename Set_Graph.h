//
//  Set_Graph.h
//  OOP Computation Graph
//
//  Created by 王一诺 on 2019/4/12.
//  Copyright ? 2019 王一诺. All rights reserved.
//

/*
 *4.13补充极小量eps
 *4.20 Z.I.PVC()实现
 *4.20 Z.processing Stage3 加入Reset
 *4.20 加入 最终节点res 的记录
 *4.20 Z.40行有一个心里没底的可能危险操作
 *4.23 修改Compute 使计算错误的点不输出
 */


#ifndef Set_Graph_h
#define Set_Graph_h
#include "Node.h"
#include <map>
#include <iomanip>
#include "Const.h"
#include "Operation.h"
#include "Operation2.h"
namespace Computational_Graph{
    using std::cin;
    class Set_Graph{
    protected:
        typedef Graph_Node<float> GNode;
        std::map<string , int > map_for_name;
        std::map<int, GNode> graph;          //图
        std::vector<string> info;              //处理的信息
        std::vector<float> Answer;             //输出的信息
        
    public:
        int num=0;
        Set_Graph() {}
        /*
        Set_Graph(std::vector<string> && a)       //直接传入信息的构造函数
        {
            info = std::move(a);
        }
        
        void Input_info(std::vector<string> &&a) //传入信息
        {
            info = std::move(a);
        }
        */
        vector<string> incision()        //对每一次字符串进行切割
        {
            vector<string> info;
            string sentence;
            std::getline(cin,sentence);   //读一整行
            std::stringstream s1(sentence);  //建立string流
            string temp;       //存放每一次输入
            while(s1>>temp)
            {
                if(temp!="=") info.push_back(temp);  //压入vector(不存入=)
            }
            return info;
        }
       
        
        
        void processing_Stage3();                        //对输入字符串的处理  
        
        template <class A>
        void Jianli_1(const string& obj, const string& p1)
        {
           
            auto pt1 = map_for_name.find(p1);
            if (pt1 == map_for_name.end())                      //参数未定义
            {
                std::cerr<<"False Parameter defination\n";
            }
            else
            {
                graph[num].Mode = Operator;       //注明类型
                graph[num].Nodename = obj;        //注明名称
                graph[num].node = std::make_shared<A>(obj,graph[map_for_name[p1]].node);  //建立节点
                map_for_name[obj]=num;            //更新对应关系
                num++;                            //第num个节点建立完毕，num++
            }
        }
        
        template <class A>
        void Jianli_2(const string& obj, const string& p1, const string& p2)
        {
            
            auto pt1 = map_for_name.find(p1);
            auto pt2 = map_for_name.find(p2);
           
            if (pt2==map_for_name.end()||pt1 == map_for_name.end())  //参数未定义
            {
                std::cerr<<"False Parameter defination\n";
            }
            else
            {
                graph[num].Mode = Operator;
                graph[num].Nodename = obj;
                graph[num].node = std::make_shared<A>(obj,graph[map_for_name[p1]].node, graph[map_for_name[p2]].node);//建立节点
                map_for_name[obj]=num;           //更新对应关系
                num++;                          //第num个节点建立完毕，num++
            }
        }
        
        template <class A>
        void Jianli_3(const string& obj, const string& p1, const string& p2,const string & p3)
        {
            //auto x = graph.find(obj);
            auto pt1 = map_for_name.find(p1);
            auto pt2 = map_for_name.find(p2);
            auto pt3 = map_for_name.find(p3);
           
            if (pt3==map_for_name.end()||pt2==map_for_name.end()||pt1 == map_for_name.end())
            {
                std::cerr<<"False Parameter defination\n";
            }
            else
            {
                graph[num].Mode = Operator;
                graph[num].Nodename = obj;
                
                graph[num].node = std::make_shared<A>(obj,graph[map_for_name[p1]].node, graph[map_for_name[p2]].node,graph[map_for_name[p3]].node);
                map_for_name[obj]=num;                    //更新对应关系
                num++;                                   //第num个节点建立完毕，num++
            }
        }
        
        
      
        void Compute(const string& a)             //对于表达式进行计算
        {
        
            float b = graph[map_for_name[a]].node->Forward();
            // cout.setf(std::ios_base::showpoint);
            Answer.push_back(b);
            if((b!=Minus_Max)) cout<<std::fixed<<std::setprecision(4)<<b<<std::endl;
        }
        
        
        
        void SetAnswer(const string& name, int n)                       //对Variable进行seranswer操作
        {
            if(Answer[n]<=Minus_Max+eps) std::cerr<<"Invalid Operation\n";
            else if(graph[map_for_name[name]].Mode== Varible) graph[map_for_name[name]].node->Initalize(Answer[n]);
            else std::cerr<<"Set_answer option only for Varible\n";            //如果不为Varible则报错
        }
        void Initalize_PVC();                          //
        void Initalize_Op();                           //
        void Initalize_Ph(const string& name);               //对于Ph(n名字为name)进行初始化；
        void Initalize_V(const string& name, float num);               //对于V(n名字为name)进行初始化；
        void Initalize_C(const string& name, float num);               //对于C(n名字为name)进行初始化；
        void Initalize_Input(const string& name, float num)           //在第三阶段对于输入进行初始化;
        {
            if(graph[map_for_name[name]].Mode==Placehold)
                graph[map_for_name[name]].node->Initalize(num);
            else std::cerr<<"Invalid Operation\n";
        }
        void Stage1()                    //第一阶段的处理
        {
            string tmp;
            getline(cin,tmp);
            int times = std::stoi(tmp);               //记录输入的次数
            for(int i = 1; i<=times; i++)  //进行第i次操作
            {
                info = incision();   //得到信息
                Initalize_PVC();     //进行处理
            }
        }
        void Stage2()
        {
            string tmp;
            getline(cin,tmp);
            int times = std::stoi(tmp);               //记录输入的次数
            for(int i = 1; i<=times; i++)  //进行第i次操作
            {
                info = incision();   //得到信息
                Initalize_Op();     //进行处理
            }
        }
        void Stage3()
        {
            string tmp;
            getline(cin,tmp);
            int times = std::stoi(tmp);               //记录输入的次数
            for(int i = 1; i<=times; i++)  //进行第i次操作
            {
                info = incision();   //得到信息
                processing_Stage3();     //进行处理
            }
        }
       
    };
}








#endif /* Set_Graph_h */
