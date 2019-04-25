//
//  Set_Graph.cpp
//  OOP Computation Graph
//
//  Created by ��һŵ on 2019/4/13.
//  Copyright ? 2019 ��һŵ. All rights reserved.
//
/*
	*4.20 Z.ʵ��Initalize PVC() 
*/ 

#include <stdio.h>
#include "Set_Graph.h"
#include "Const.h"
#include "Node.h"
namespace Computational_Graph{
	
	void Set_Graph::Initalize_PVC(){
		if(info[1] == "P"){
			Initalize_Ph(info[0]) ;
//			cout << " P"   ; 
		} 
		else if(info[1] == "C"){
			Initalize_C(info[0],atof(info[2].c_str())) ;
//			cout << "C" ; 
		}
		else if(info[1] == "V"){
			Initalize_V(info[0],atof(info[2].c_str())) ; 
//			cout <<"V" ;
		}
		else std::cerr << "in func'Initalize_PVC': Defination unavailable\n" ;
	}
    
    void Set_Graph::Initalize_Ph(const string& name)               //����Ph(n����Ϊname)���г�ʼ����
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
    void Set_Graph::Initalize_V(const string& name, float num)               //����V(n����Ϊname)���г�ʼ����
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
    void Set_Graph::Initalize_C(const string& name, float num)               //����C(n����Ϊname)���г�ʼ����
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

     void Set_Graph::Initalize_Op()          //�ڶ��׶εĲ���
    {//add by Cai on 4.21
    	res = info[0] ;
        if(info[2]=="+")                 //Ϊ�ӷ�;
        {
            //ADD(info[0], info[1], info[3]);
            Jianli_2<Addition>(info[0], info[1], info[3]);
        }
        else if(info[2]=="*")                 //Ϊ�˷�
        {
            //Multi(info[0], info[1], info[3]);
            Jianli_2<Multiply>(info[0], info[1], info[3]);
        }
        else if(info[2]=="-")            //Ϊ����
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
        	graph[info[1]].node->Reset_b() ;
            int times = atoi(info[2].data());     //��ȡ��������
            for(int i = 1; i<= times; i++)
            {
                int pos = 2+(i-1)*2 + 1;       //��ʱ��ȡ��λ��
                string name = info[pos];
                float num = atof(info[pos+1].data());
                if(graph[name].Mode!=Placehold) std::cerr<<"Can not Initalize a non-PlaceHolder Object\n";
                else graph[name].node->Initalize(num);
            }
            Compute(info[1]);
        }
        else if(info[0]=="SETCONSTANT")
        {
            string name = info[1];   //�������
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
            string name = info[1];   //�������
            int n = atoi(info[2].data()); //��õ�n�ε�ֵ
            SetAnswer(name, n-1);
            Answer.push_back(Minus_Max);
        }
    }
    
}
