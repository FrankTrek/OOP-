
//  Operation.h
//  OOP Computation Graph
//
//  Created by 王一诺 on 2019/4/13.
//  Copyright ? 2019 王一诺. All rights reserved.
//

//
//  Operation.h
//  真正的大作业
//
//  Created by 蔡 on 2019/4/8.
//  Copyright ? 2019年 蔡. All rights reserved.
//
//4.12 将operation类的构造函数由传引用改为传指针
//4.13 补充了所有二元函数以及COND函数
#ifndef Operation_h
#define Operation_h
#include "BaseNode.h"
#include "Node.h"
#include <cmath>


namespace  Computational_Graph{
    class Addition : public Operation<float>{//加号
        
    public:
        
        Addition(BaseNode<float>* Node1, BaseNode<float> *Node2): Operation(Node1,Node2){}
        Addition(const string& a, BaseNode<float>* Node1, BaseNode<float> *Node2) : Operation(a,Node1,Node2){}
        
        float Forward() override{
            if(flag==false)                           //上一次计算得到的结果不合法
                return Minus_Max;
            else if(abs(value-Minus_Max)>eps){      //上一次计算得到结果且合法
                return value;
            }
            
            else {                                     //第一次访问这个节点
                float a=input_nodes[0]->Forward();     //得到其中一个参数数值
                if(abs(a-Minus_Max)<eps){              //一个参数不合法
                    flag=false;
                    return Minus_Max;
                }
                float b=input_nodes[1]->Forward();      //得到第二个参数
                if(abs(b-Minus_Max)<eps){               //第二个参数不合法
                    flag=false;
                    return Minus_Max;
                }
                value=a+b;
                if(value> - Minus_Max + eps||value < Minus_Max - eps)      //考虑结果超过上下界
                {
                    std::cerr<<"Numeric Limit Exceeded\n";
                    flag = false;
                    return Minus_Max;
                }
                return value;
            }
            
        }
        void Backward() override {
            ;
        }
    };
    class Multiply: public Operation<float>{//乘号
        
    public:
        
        Multiply(BaseNode<float>* Node1, BaseNode<float> *Node2): Operation(Node1,Node2){}
        Multiply(const string a, BaseNode<float>* Node1, BaseNode<float> *Node2) : Operation(a,Node1,Node2){}
        
        float Forward() override{
            if(flag==false)                         //上一次计算结果不合法
                return Minus_Max;
            else if(abs(value-Minus_Max)>eps){      //上次计算结果合法
                return value;
            }
            
            else {                                   //第一次访问这个节点
                float a=input_nodes[0]->Forward();   //得到第一个参数
                if(abs(a-Minus_Max)<eps){            //第一个参数不合法
                    flag=false;
                    return Minus_Max;
                }
                float b=input_nodes[1]->Forward();   //得到第二个参数
                if(abs(b-Minus_Max)<eps){            //第二个参数不合法
                    flag=false;
                    return Minus_Max;
                }
                value=a*b;
                if(value> - Minus_Max + eps||value < Minus_Max - eps)      //考虑结果超过上下界
                {
                    std::cerr<<"Numeric Limit Exceeded\n";
                    flag = false;
                    return Minus_Max;
                }
                return value;
            }
            
        }
        void Backward() override {
            ;
        }
    };
    class Minus: public Operation<float>{//减号
        
    public:
        
        Minus(BaseNode<float>* Node1, BaseNode<float>* Node2): Operation(Node1,Node2){}
        Minus(const string a, BaseNode<float>* Node1, BaseNode<float> *Node2) : Operation(a,Node1,Node2){}
        
        float Forward() override{
            if(flag==false)                          //上次计算结果不合法
                return Minus_Max;
            else if(abs(value-Minus_Max)>eps){       //上一次计算结果合法
                return value;
            }
            
            else {                                    //第一次访问这个节点
                float a=input_nodes[0]->Forward();    //得到第一个参数
                if(abs(a-Minus_Max)<eps){             //第一个参数不合法
                    flag=false;
                    return Minus_Max;
                }
                float b=input_nodes[1]->Forward();     //得到第二个参数
                if(abs(b-Minus_Max)<eps){              //第二个参数不合法
                    flag=false;
                    return Minus_Max;
                }
                value=a-b;
                if(value> - Minus_Max + eps||value < Minus_Max - eps)      //考虑结果超过上下界
                {
                    std::cerr<<"Numeric Limit Exceeded\n";
                    flag = false;
                    return Minus_Max;
                }
                return value;
            }
            
        }
        void Backward() override {
            ;
        }
    };
    
    
    class Division: public Operation<float>{//除号
        
    public:
        
        Division(BaseNode<float>* Node1, BaseNode<float> *Node2): Operation(Node1,Node2){}
        Division(const string a, BaseNode<float>* Node1, BaseNode<float>* Node2) : Operation(a,Node1,Node2){}
        
        float Forward() override{
            if(flag==false)                              //上一次访问结果不合法
                return Minus_Max;
            else if(abs(value-Minus_Max)>eps){           //上一次j访问结果合法
                return value;
            }
            
            else {                                       //第一次访问这个节点
                float b=input_nodes[1]->Forward();       //得到第一个参数
                if(abs(b-Minus_Max)<eps){                //第一个参数不合法
                    flag=false;
                    return Minus_Max;
                }
                else if(abs(b-0.0)<eps){                 //分母为0的特殊情况
                    flag=false;
                    std::cerr<<"ERROR: Division by zero"<<endl;
                    return Minus_Max;
                }
                float a=input_nodes[0]->Forward();        //得到第二个参数
                if(abs(a-Minus_Max)<eps){                 //第二个参数b不合法
                    flag=false;
                    return Minus_Max;
                }
                
                value=a/b;
                if(value> - Minus_Max + eps||value < Minus_Max - eps)      //考虑结果超过上下界
                {
                    std::cerr<<"Numeric Limit Exceeded\n";
                    flag = false;
                    return Minus_Max;
                }
                return value;
            }
            
        }
        void Backward() override {
            ;
        }
    };
    //-------------------------------------------------------------------
    //
    class Xiaoyu: public Operation<float>{//小于
    public:
        Xiaoyu(BaseNode<float>* Node1, BaseNode<float> *Node2): Operation(Node1,Node2){}
        Xiaoyu(const string a, BaseNode<float>* Node1, BaseNode<float>* Node2) : Operation(a,Node1,Node2){}
        float Forward() override{
            if(flag==false)                             //上一次访问结果不合法
                return Minus_Max;
            else if(abs(value-Minus_Max)>eps){          //上一次访问结果合法
                return value;
            }
            
            else {                                       //第一次访问这个节点
                float a=input_nodes[0]->Forward();       //得到第一个参数
                if(abs(a-Minus_Max)<eps){                //第一个参数不合法
                    flag=false;
                    return Minus_Max;
                }
                float b=input_nodes[1]->Forward();        //得到第二个参数
                if(abs(b-Minus_Max)<eps){                 //第二个参数不合法
                    flag=false;
                    return Minus_Max;
                }
                value=(a<b? 1.0:0.0);
                return value;
            }
            
        }
        void Backward() override {
            ;
        }
    };
    class Xiaodeng: public Operation<float>{//小于等于
    public:
        Xiaodeng(BaseNode<float>* Node1, BaseNode<float> *Node2): Operation(Node1,Node2){}
        Xiaodeng(const string a, BaseNode<float>* Node1, BaseNode<float>* Node2) : Operation(a,Node1,Node2){}
        float Forward() override{
            if(flag==false)                              //上一次访问结果不合法
                return Minus_Max;
            else if(abs(value-Minus_Max)>eps){            //上一次j访问结果合法
                return value;
            }
            
            else {                                        //第一次访问这个节点
                float a=input_nodes[0]->Forward();        //得到第一个参数
                if(abs(a-Minus_Max)<eps){                 //第一个参数不合法
                    flag=false;
                    return Minus_Max;
                }
                float b=input_nodes[1]->Forward();         //第二个参数
                if(abs(b-Minus_Max)<eps){                  //第二个参数不合法
                    flag=false;
                    return Minus_Max;
                }
                value=(a<=b? 1.0:0.0);
                return value;
            }
            
        }
        void Backward() override {
            ;
        }
    };
    class Dayu: public Operation<float>{//大于
    public:
        Dayu(BaseNode<float>* Node1, BaseNode<float> *Node2): Operation(Node1,Node2){}
        Dayu(const string a, BaseNode<float>* Node1, BaseNode<float>* Node2) : Operation(a,Node1,Node2){}
        float Forward() override{
            if(flag==false)                          //上一次访问结果不合法
                return Minus_Max;
            else if(abs(value-Minus_Max)>eps){       //上一次j访问结果合法
                return value;
            }
            
            else {                                    //第一次访问这个节点
                float a=input_nodes[0]->Forward();     //得到第一个参数
                if(abs(a-Minus_Max)<eps){             //得到第1个参数不合法
                    flag=false;
                    return Minus_Max;
                }
                float b=input_nodes[1]->Forward();     //第二个参数
                if(abs(b-Minus_Max)<eps){              //第二个参数不合法
                    flag=false;
                    return Minus_Max;
                }
                value=(a>b? 1.0:0.0);
                return value;
            }
            
        }
        void Backward() override {
            ;
        }
    };
    class Dadeng: public Operation<float>{//大于等于
    public:
        Dadeng(BaseNode<float>* Node1, BaseNode<float> *Node2): Operation(Node1,Node2){}
        Dadeng(const string a, BaseNode<float>* Node1, BaseNode<float>* Node2) : Operation(a,Node1,Node2){}
        float Forward() override{
            if(flag==false)                               //上一次访问结果不合法
                return Minus_Max;
            else if(abs(value-Minus_Max)>eps){            //上一次j访问结果合法
                return value;
            }
            
            else {                                         //第一次访问这个节点
                float a=input_nodes[0]->Forward();         //得到第一个参数
                if(abs(a-Minus_Max)<eps){                  //得到第一个参数不合法
                    flag=false;
                    return Minus_Max;
                }
                float b=input_nodes[1]->Forward();         //第二个参数
                if(abs(b-Minus_Max)<eps){                  //第二个参数不合法
                    flag=false;
                    return Minus_Max;
                }
                value=(a>=b? 1.0:0.0);
                return value;
            }
            
        }
        void Backward() override {
            ;
        }
    };
    class Dengyu: public Operation<float>{//等于号
    public:
        Dengyu(BaseNode<float>* Node1, BaseNode<float> *Node2): Operation(Node1,Node2){}
        Dengyu(const string a, BaseNode<float>* Node1, BaseNode<float>* Node2) : Operation(a,Node1,Node2){}
        float Forward() override{
            if(flag==false)                        //上一次访问结果不合法
                return Minus_Max;
            else if(abs(value-Minus_Max)>eps){     //上一次j访问结果合法
                return value;
            }
            
            else {                                 //第一次访问这个节点
                float a=input_nodes[0]->Forward(); //得到第一个参数
                if(abs(a-Minus_Max)<eps){          //得到第一个参数不合法
                    flag=false;
                    return Minus_Max;
                }
                float b=input_nodes[1]->Forward();  //第二个参数
                if(abs(b-Minus_Max)<eps){           //第二个参数不合法
                    flag=false;
                    return Minus_Max;
                }
                value=(abs(a-b)<eps? 1.0:0.0);
                return value;
            }
            
        }
        void Backward() override {
            ;
        }
    };
    class Budeng: public Operation<float>{//不等于号
    public:
        Budeng(BaseNode<float>* Node1, BaseNode<float> *Node2): Operation(Node1,Node2){}
        Budeng(const string a, BaseNode<float>* Node1, BaseNode<float>* Node2) : Operation(a,Node1,Node2){}
        float Forward() override{
            if(flag==false)                           //上一次访问结果不合法
                return Minus_Max;
            else if(abs(value-Minus_Max)>eps){        //上一次j访问结果合法
                return value;
            }
            
            else {                                    //第一次访问这个节点
                float a=input_nodes[0]->Forward();    //得到第一个参数
                if(abs(a-Minus_Max)<eps){         //得到第一个参数不合法
                    flag=false;
                    return Minus_Max;
                }
                else
                {
                   float b=input_nodes[1]->Forward(); //得到第2个参数不合法
                   if(abs(b-Minus_Max)<eps){          //得到第2个参数
                    flag=false;
                    return Minus_Max;
                }
                value=(abs(a-b)>=eps? 1.0:0.0);
                return value;
                }
            }
            
        }
        void Backward() override {
            ;
        }
    };
    
    class COND: public Operation<float>{
    public:
        COND(BaseNode<float>* Node1, BaseNode<float> *Node2, BaseNode<float>* Node3): Operation(Node1,Node2,Node3){}
        COND(const string a, BaseNode<float>* Node1, BaseNode<float>* Node2, BaseNode<float>* Node3) : Operation(a, Node1,Node2, Node3){}
        float Forward() override{
            if(flag==false)                             //上一次访问结果不合法
                return Minus_Max;
            else if(abs(value-Minus_Max)>eps){          //上一次j访问结果合法
                return value;
            }
            
            else {                                      //第一次访问这个节点
                bool flag_t;
                float c=input_nodes[0]->Forward();      //得到第一个参数
                if(abs(c-Minus_Max)<eps){           //得到第一个参数不合法
                    flag=false;
                    return Minus_Max;
                }
                if(c > eps) flag_t=true;
                else if(c <= eps ) flag_t=false;
                
                float a=input_nodes[1]->Forward();    //得到第2个参数
                if(abs(a-Minus_Max)<eps){             //得到第2个参数不合法
                    flag=false;
                    return Minus_Max;
                }
                float b=input_nodes[2]->Forward();     //得到第3个参数
                //      cout << b ;
                if(abs(b-Minus_Max)<eps){              //得到第2个参数不合法
                    flag=false;
                    return Minus_Max;
                }
                value=(flag_t? a:b);
                //        std::cout << " a" << a << " b" << b << " value" << value <<"\n" ;
                return value;
            }
            
        }
        void Backward() override {
            ;
        }
    };
    
    
    
}
#endif /* Operation_h */
