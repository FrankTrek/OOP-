//
//  Operation.h
//  OOP Computation Graph
//
//  Created by 王一诺 on 2019/4/13.
//  Copyright © 2019 王一诺. All rights reserved.
//

//
//  Operation.h
//  真正的大作业
//
//  Created by 蔡 on 2019/4/8.
//  Copyright © 2019年 蔡. All rights reserved.
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
            if(flag==false)
                return Minus_Max;
            else if(value!=Minus_Max){
                return value;
            }
            
            else {
                float a=input_nodes[0]->Forward();
                if(a==Minus_Max){
                    flag=false;
                    return Minus_Max;
                }
                float b=input_nodes[1]->Forward();
                if(b==Minus_Max){
                    flag=false;
                    return Minus_Max;
                }
                value=a+b;
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
            if(flag==false)
                return Minus_Max;
            else if(value!=Minus_Max){
                return value;
            }
            
            else {
                float a=input_nodes[0]->Forward();
                if(a==Minus_Max){
                    flag=false;
                    return Minus_Max;
                }
                float b=input_nodes[1]->Forward();
                if(b==Minus_Max){
                    flag=false;
                    return Minus_Max;
                }
                value=a*b;
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
            if(flag==false)
                return Minus_Max;
            else if(value!=Minus_Max){
                return value;
            }
            
            else {
                float a=input_nodes[0]->Forward();
                if(a==Minus_Max){
                    flag=false;
                    return Minus_Max;
                }
                float b=input_nodes[1]->Forward();
                if(b==Minus_Max){
                    flag=false;
                    return Minus_Max;
                }
                value=a-b;
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
            if(flag==false)
                return Minus_Max;
            else if(value!=Minus_Max){
                return value;
            }
            
            else {
                float b=input_nodes[1]->Forward();
                if(b==Minus_Max){
                    flag=false;
                    return Minus_Max;
                }
                else if(abs(b-0.0)<eps){
                    flag=false;
                    std::cerr<<"ERROR: Division by zero"<<endl;
                    return Minus_Max;
                }
                float a=input_nodes[0]->Forward();
                if(a==Minus_Max){
                    flag=false;
                    return Minus_Max;
                }
                
                value=a/b;
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
            if(flag==false)
                return Minus_Max;
            else if(value!=Minus_Max){
                return value;
            }
            
            else {
                float a=input_nodes[0]->Forward();
                if(a==Minus_Max){
                    flag=false;
                    return Minus_Max;
                }
                float b=input_nodes[1]->Forward();
                if(b==Minus_Max){
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
            if(flag==false)
                return Minus_Max;
            else if(value!=Minus_Max){
                return value;
            }
            
            else {
                float a=input_nodes[0]->Forward();
                if(a==Minus_Max){
                    flag=false;
                    return Minus_Max;
                }
                float b=input_nodes[1]->Forward();
                if(b==Minus_Max){
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
            if(flag==false)
                return Minus_Max;
            else if(value!=Minus_Max){
                return value;
            }
            
            else {
                float a=input_nodes[0]->Forward();
                if(a==Minus_Max){
                    flag=false;
                    return Minus_Max;
                }
                float b=input_nodes[1]->Forward();
                if(b==Minus_Max){
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
            if(flag==false)
                return Minus_Max;
            else if(value!=Minus_Max){
                return value;
            }
            
            else {
                float a=input_nodes[0]->Forward();
                if(a==Minus_Max){
                    flag=false;
                    return Minus_Max;
                }
                float b=input_nodes[1]->Forward();
                if(b==Minus_Max){
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
            if(flag==false)
                return Minus_Max;
            else if(value!=Minus_Max){
                return value;
            }
            
            else {
                float a=input_nodes[0]->Forward();
                if(a==Minus_Max){
                    flag=false;
                    return Minus_Max;
                }
                float b=input_nodes[1]->Forward();
                if(b==Minus_Max){
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
            if(flag==false)
                return Minus_Max;
            else if(value!=Minus_Max){
                return value;
            }
            
            else {
                float a=input_nodes[0]->Forward();
                if(a==Minus_Max){
                    flag=false;
                    return Minus_Max;
                }
                float b=input_nodes[1]->Forward();
                if(b==Minus_Max){
                    flag=false;
                    return Minus_Max;
                }
                value=(abs(a-b)>=eps? 1.0:0.0);
                return value;
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
            if(flag==false)
                return Minus_Max;
            else if(value!=Minus_Max){
                return value;
            }
            
            else {
                bool flag;
                float c=input_nodes[0]->Forward();
                if(c==Minus_Max){
                    flag=false;
                    return Minus_Max;
                }
                if(abs(c-1.0)<eps)
                    flag=true;
                else if(abs(c-0.0)<eps)
                    flag=false;
                else {
                    std::cerr<<"ERROR: COND parameter c is not a comparison expression"<<endl;
                    flag=false;
                    return Minus_Max;
                }
                
                float a=input_nodes[1]->Forward();
                if(a==Minus_Max){
                    flag=false;
                    return Minus_Max;
                }
                float b=input_nodes[2]->Forward();
                if(b==Minus_Max){
                    flag=false;
                    return Minus_Max;
                }
                value=(flag? a:b);
                return value;
            }
            
        }
        void Backward() override {
            ;
        }
    };
    
    
    
}
#endif /* Operation_h */
