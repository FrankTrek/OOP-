//
//  Set_Graph.cpp
//  OOP Computation Graph
//
//  Created by 王一诺 on 2019/4/13.
//  Copyright ? 2019 王一诺. All rights reserved.
//
/*
 *4.20 Z.实现Initalize PVC()
 */

#include <stdio.h>
#include "Set_Graph.h"
#include "Const.h"
#include "Node.h"
namespace Computational_Graph{
    /*
    vector<string> Set_Graph::Input(int stage){
        string s ;
        vector<string>Input1 ;
        getline(std::cin,s) ;
        std::stringstream ss(s) ;
        string x ;
        while(ss >> x){
            if(stage == 2 && x == "=") continue ;
            Input1.push_back(x) ;
        }
        ss.str("") ;
        ss.clear() ;
        return Input1 ;
    }
    void Set_Graph::Construct(int stage,int line_N){
        for(int i = 1; i<= line_N ; i++ ){
            this->Input_info(Input(stage)) ;
            if(stage == 1){
                this->Initalize_PVC() ;
            }
            else if(stage == 2){
                
                this->Initalize_Op() ;
            }
            else if(stage == 3){
                this->processing_Stage3() ;
            }
            else{
                cout <<"。显然这是不可能的" ;
            }
        }
    }
     */
    
    void Set_Graph::Initalize_PVC(){
        if(info[1] == "P"){
            Initalize_Ph(info[0]) ;
            
        }
        else if(info[1] == "C"){
            Initalize_C(info[0],atof(info[2].c_str())) ;
            
        }
        else if(info[1] == "V"){
            Initalize_V(info[0],atof(info[2].c_str())) ;
            
        }
        else std::cerr << "in func'Initalize_PVC': Defination unavailable\n" ;
    }
    
    void Set_Graph::Initalize_Ph(const string& name)               //对于Ph(n名字为name)进行初始化；
    {
        auto x = map_for_name.find(name);
        if(x!=map_for_name.end())
        {
            std::cerr<<"False Redefination\n";
        }
        else
        {
            graph[num].Mode = Placehold;                    //注明类型
            graph[num].Nodename = name;                     //标记名字
            graph[num].node = std::make_shared<Placeholder>(name);  //创建节点
            map_for_name[name]=num;                         //建立name和num的对应
            num++;                                          //第num个节点建立完毕，num++
        }
    }
    void Set_Graph::Initalize_V(const string& name, float number)               //对于V(n名字为name)进行初始化；
    {
        auto x = map_for_name.find(name);
        if(x!=map_for_name.end())
        {
            std::cerr<<"False Redefination\n";
        }
        else
        {
           
            graph[num].Nodename = name;
            graph[num].Mode = Varible;
            graph[num].node = std::make_shared<Variable>(number,name);   //创建节点
             map_for_name[name]=num;                        //建立num与name的对应
            num++;                                           //第num个节点建立完毕，num++
        }
    }
    void Set_Graph::Initalize_C(const string& name, float number)               //对于C(n名字为name)进行初始化；
    {
        auto x = map_for_name.find(name);
        if(x!=map_for_name.end())
        {
            std::cerr<<"False Redefination\n";
        }
        else
        {
            
            graph[num].Mode = Const;
            graph[num].Nodename = name;
            graph[num].node = std::make_shared<Constant>(number,name);  //建立节点
            map_for_name[name]=num;                                   //建立num与name的对应
            num++;                                                      //第num个节点建立完毕，num++
        }
    }
    
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
        else if(info[1]=="SIGMOID")
        {
            Jianli_1<SINGMOID>(info[0], info[2]);
        }
        else if(info[1]=="PRINT" || info[1] == "Print")
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
            SetAnswer(name, n-1);
            Answer.push_back(Minus_Max);
        }
    }
    
}
