//
//  Set_Graph_Advanced.h
//  OOP Computation Graph
//
//  Created by 王一诺 on 2019/5/6.
//  Copyright © 2019 王一诺. All rights reserved.
//

//
//  Set_Graph_Advanced.h
//  真正最后的大作业
//
//  Created by 蔡 on 2019/5/5.
//  Copyright © 2019年 蔡. All rights reserved.
//

#ifndef Set_Graph_Advanced_h
#define Set_Graph_Advanced_h

#include "Node.h"
#include <map>
#include <iomanip>
#include "Const.h"
#include "Operation.h"
#include "Operation2.h"
#include "Set_Graph.h"
#include "stack"
namespace Computational_Graph{
    using std::cin;
    class Set_Graph_Advanced : public Set_Graph {
    protected:
        
        std::map<string,int> priority;
        std::stack<string> expression;
        std::stack<string> token ;
        int k ;
        
        
    public:
        Set_Graph_Advanced(): Set_Graph(){
            priority["("] = 5;
            priority[")"] = 6;
            priority["=="] = 1;
            priority["!="] = 1;
            priority["<"] = 1;
            priority["<="] = 1;
            priority[">"] = 1;
            priority[">="] = 1;
            priority["+"] = 2;
            priority["-"] = 2;
            priority["*"] = 3;
            priority["/"] = 3;
            priority["SIN"] = 4;
            priority["COS"] = 4;
            priority["LOG"] = 4;
            priority["EXP"] = 4;
            priority["SIGMOID"] = 4;
            priority["TANH"] = 4;
        };
        
        
        bool Is_Token(int k)
        {
            if(info[k]=="(") return true;
            else if(info[k]==")") return true;
            else if(info[k]=="==") return true;
            else if(info[k]=="!=") return true;
            else if(info[k]=="<") return true;
            else if(info[k]==">") return true;
            else if(info[k]=="<=") return true;
            else if(info[k]==">=") return true;
            else if(info[k]=="+") return true;
            else if(info[k]=="-") return true;
            else if(info[k]=="*") return true;
            else if(info[k]=="/") return true;
            else if(info[k]=="SIN") return true;
            else if(info[k]=="COS") return true;
            else if(info[k]=="LOG") return true;
            else if(info[k]=="EXP") return true;
            else if(info[k]=="SIGMOID") return true;
            else if(info[k]=="TANH") return true;
            else return false;
        }
        void  ESTABLISH();
        
        // Cai : 这里不是虚函数，直接替换原来的
        void Stage2()
        {
            
            info = incision();   //得到信息
            k = 0;
            while(k<info.size())
            {
                if(!Is_Token(k))
                {
                    float num = atof(info[k].data());
                    if(fabs(num-0)<eps)
                    {
                        Initalize_Ph(info[k]);
                        expression.push(info[k]);
                        k++;
                    }
                    else
                    {
                        Initalize_C(info[k], num);
                        expression.push(info[k]);
                        k++;
                    }
                    
                }
                else
                {
                    if(token.empty()) { token.push(info[k]); k++;}
                    else
                    {
                        string token1 = token.top();
                        string token2 = info[k];
                        if(priority[token1]==5&&priority[token2]==6)
                        {
                            
                            token.pop();
                            k++;
                        }
                        else if(priority[token1]!=5&&priority[token2]==6)
                        {
                            ESTABLISH();
                        }
                        else if(priority[token1]==5)
                        {
                            token.push(token2);
                            k++;
                        }
                        else if(priority[token2]>priority[token1])
                        {
                            token.push(token2);
                            k++;
                        }
                        else ESTABLISH();
                    }
                }
            }
            while(!token.empty()) ESTABLISH();
            
        }
        
        void processing_Stage3();
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


#endif /* Set_Graph_Advanced_h */
