//
//  Set_Graph_Advanced.cpp
//  OOP Computation Graph
//
//  Created by 王一诺 on 2019/5/6.
//  Copyright © 2019 王一诺. All rights reserved.
//

//
//  Set_Graph_Advanced.cpp
//  真正最后的大作业
//
//  Created by 蔡 on 2019/5/5.
//  Copyright © 2019年 蔡. All rights reserved.
//

#include "Set_Graph_Advanced.h"
namespace Computational_Graph{
    void Set_Graph_Advanced::processing_Stage3()
    {
        if(info[0]=="EVAL")
        {
            auto ttmp=graph[map_for_name[info[1]]];
            ttmp.node->Reset_b() ;
            if(info.size()<=2)          //对于简单节点的计算情况
            {
                
                Compute(info[1]);
                
            }
            else {                            //考虑需要Ph参数赋值的情况
                int times = atoi(info[2].data());     //读取操作次数
                for(int i = 1; i<= times; i++)
                {
                    int pos = 2+(i-1)*2 + 1;       //此时读取的位置
                    string name = info[pos];         //得到Ph的名字
                    float value = atof(info[pos+1].data());  //对ph赋的值
                    auto tttmp=graph[map_for_name[name]];   //得到GNode
                    if(tttmp.Mode!=Placehold) std::cerr<<"Can not Initalize a non-PlaceHolder Object\n";
                    else tttmp.node->Initalize(value);
                }
                Compute(info[1]);
                
            }
        }
        else if(info[0]=="SETCONSTANT")
        {
            string name = info[1];   //获得名字
            float value = atof(info[2].data());  //
            auto ttmp=graph[map_for_name[name]];  //得到要操作的V对应的GNode
            if(ttmp.Mode!=Varible) std::cerr<<"Can not setconstant a non-Varible Object\n";
            else
            {
                ttmp.node->Initalize(value);
            }
            Answer.push_back(Minus_Max);
        }
        else if(info[0]=="SETANSWER")
        {
            string name = info[1];   //获得名字
            int n = atoi(info[2].data()); //获得第n次的值
            SetAnswer(name, n-1);//用Answer的第n个元素赋值
            Answer.push_back(Minus_Max);//压入MinusMax用来占行
        }
        else if(info[0]=="DERIVE")
        {
            auto ttmp=graph[map_for_name[info[1]]];
            ttmp.node->Reset_b() ;
            if(info.size()<=2)          //对于简单节点的计算情况
            {
                
            }
            else {                            //考虑需要Ph参数赋值的情况
                int times = atoi(info[2].data());     //读取操作次数
                for(int i = 1; i<= times; i++)
                {
                    int pos = 2+(i-1)*2 + 1;       //此时读取的位置
                    string name = info[pos];         //得到Ph的名字
                    float value = atof(info[pos+1].data());  //对ph赋的值
                    auto tttmp=graph[map_for_name[name]];   //得到GNode
                    if(tttmp.Mode!=Placehold) std::cerr<<"Can not Initalize a non-PlaceHolder Object\n";
                    else tttmp.node->Initalize(value);
                }
                
                
            }
            
            if(fabs(ttmp.node->Forward()-Minus_Max)>eps)//计算一遍图，激活网络
            {
                ttmp.node->Backward(1); //计算导数
                
                
                //以下为输出程序
                bool chk = false ;      //是否输出
                cout << "d" << info[1] << " " << "=";
                for(auto &it : graph){
                    if(it.second.Mode==Placehold){
                        cout<<" ";
                        float a = it.second.node -> get_gradi();
                        if(fabs(a)>eps){
                            //
                            if(!chk)
                                cout<<"Sigma";
                            cout<<" ";
                            cout<<std::fixed<<std::setprecision(4)<<a;
                            cout<<" d";
                            it.second.node->Print();
                            chk = true;
                        
                        }
                    }
                }
                if(!chk) cout << " constant" << endl;   //说明res与所有placeholder节点无关
                else cout << endl;
                Answer.push_back(Minus_Max);
                
            }
        }
    }
    
    void Set_Graph_Advanced::ESTABLISH()
    {
        string temp = token.top();
        token.pop();
        
        if(temp=="+")                 //为加法;
        {
            string name1 = expression.top();
            expression.pop();
            string name2 = expression.top();
            expression.pop();
            string name = name2 + " " + "+" + " " + name1;
            //ADD(info[0], info[1], info[3]);
            string Final = "res";
            if(token.empty()&&k==info.size()) Jianli_2<Addition>(Final, name2, name1);
            else Jianli_2<Addition>(name, name2, name1);
            expression.push(name);
        }
        else if(temp=="*")                 //为乘法
        {
            //Multi(info[0], info[1], info[3]);
            string name1 = expression.top();
            expression.pop();
            string name2 = expression.top();
            expression.pop();
            string name = name2 + " " + "*" + " " + name1;
            string Final = "res";
            if(token.empty()&&k==info.size()) Jianli_2<Multiply>(Final, name2, name1);
            else Jianli_2<Multiply>(name, name2, name1);
            expression.push(name);
        }
        else if(temp=="-")            //为减法
        {
            //MINUS(info[0], info[1], info[3]);
            string name1 = expression.top();
            expression.pop();
            string name2 = expression.top();
            expression.pop();
            string name = name2 + " " + "-" + " " + name1;
            string Final = "res";
            if(token.empty()&&k==info.size())  Jianli_2<Minus>(Final, name2, name1);
            else Jianli_2<Minus>(name, name2, name1);
            expression.push(name);
        }
        else if(temp=="/")
        {
            //Div(info[0], info[1], info[3]);
            string name1 = expression.top();
            expression.pop();
            string name2 = expression.top();
            expression.pop();
            string name = name2 + " " + "/" + " " + name1;
            string Final = "res";
            if(token.empty()&&k==info.size())  Jianli_2<Division>(Final, name2, name1);
            else Jianli_2<Division>(name, name2, name1);
            expression.push(name);
        }
        else if(temp=="<")
        {
            string name1 = expression.top();
            expression.pop();
            string name2 = expression.top();
            expression.pop();
            string name = name2 + " " + "<" + " " + name1;
            string Final = "res";
            if(token.empty()&&k==info.size()) Jianli_2<Xiaoyu>(Final, name2, name1);
            else Jianli_2<Xiaoyu>(name, name2, name1);
            expression.push(name);
        }
        else if(temp=="<=")
        {
            string name1 = expression.top();
            expression.pop();
            string name2 = expression.top();
            expression.pop();
            string name = name2 + " " + "<=" + " " + name1;
            string Final = "res";
            if(token.empty()&&k==info.size())  Jianli_2<Xiaodeng>(Final, name2, name1);
            else Jianli_2<Xiaodeng>(name, name2, name1);
            expression.push(name);
        }
        else if(temp==">")
        {
            string name1 = expression.top();
            expression.pop();
            string name2 = expression.top();
            expression.pop();
            string name = name2 + " " + ">=" + " " + name1;
            string Final = "res";
            if(token.empty()&&k==info.size()) Jianli_2<Dayu>(Final, name2, name1);
            else Jianli_2<Dayu>(name, name2, name1);
            expression.push(name);
        }
        else if(temp==">=")
        {
            string name1 = expression.top();
            expression.pop();
            string name2 = expression.top();
            expression.pop();
            string name = name2 + " " + ">=" + " " + name1;
            string Final = "res";
            if(token.empty()&&k==info.size()) Jianli_2<Dadeng>(Final, name2, name1);
            else Jianli_2<Dadeng>(name, name2, name1);
            expression.push(name);
        }
        else if(temp=="==")
        {
            string name1 = expression.top();
            expression.pop();
            string name2 = expression.top();
            expression.pop();
            string name = name2 + " " + "==" + " " + name1;
            string Final = "res";
            if(token.empty()&&k==info.size())  Jianli_2<Dengyu>(Final, name2, name1);
            else Jianli_2<Dengyu>(name, name2, name1);
            expression.push(name);
        }
        else if(temp=="!=")
        {
            string name1 = expression.top();
            expression.pop();
            string name2 = expression.top();
            expression.pop();
            string name = name2 + " " + "!=" + " " + name1;
            string Final = "res";
            if(token.empty()&&k==info.size())  Jianli_2<Budeng>(Final, name2, name1);
            else Jianli_2<Budeng>(name, name2, name1);
            expression.push(name);
        }
        else if(temp=="SIN")
        {
            string name1 = expression.top();
            expression.pop();
            string f = "SIN";
            
            string name = f + " " + name1;
            string Final = "res";
            if(token.empty()&&k==info.size())  Jianli_1<SIN>(Final, name1);
            else Jianli_1<SIN>(name, name1);
            expression.push(name);
        }
        else if(temp=="LOG")
        {
            string name1 = expression.top();
            expression.pop();
            string f = "LOG";
            
            string name = f + " " + name1;
            string Final = "res";
            if(token.empty()&&k==info.size()) Jianli_1<LOG>(Final, name1);
            else Jianli_1<LOG>(name, name1);
            expression.push(name);
        }
        else if(temp=="TANH")
        {
            string name1 = expression.top();
            expression.pop();
            string f = "TANH";
            
            string name = f + " " + name1;
            string Final = "res";
            if(token.empty()&&k==info.size()) Jianli_1<TANH>(Final, name1);
            else Jianli_1<TANH>(name, name1);
            expression.push(name);
        }
        else if(temp=="EXP")
        {
            string name1 = expression.top();
            expression.pop();
            string f = "EXP";
            
            string name = f + " " + name1;
            string Final = "res";
            if(token.empty()&&k==info.size()) Jianli_1<EXP>(Final, name1);
            else Jianli_1<EXP>(name, name1);
            expression.push(name);
        }
        else if(temp=="SIGMOID")
        {
            string name1 = expression.top();
            expression.pop();
            string f = "SIGMOID";
            
            string name = f + " " + name1;
            string Final = "res";
            if(token.empty()&&k==info.size()) Jianli_1<SINGMOID>(Final, name1);
            else Jianli_1<SINGMOID>(name, name1);
            expression.push(name);
        }
        
    }
    
}
