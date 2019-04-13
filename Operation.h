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
#ifndef Operation_h
#define Operation_h
#include "BaseNode.h"
#include "Node.h"
namespace  Computational_Graph{
    class Addition : public Operation<float>{
        
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
    class Multiply: public Operation<float>{
        
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
    class Minus: public Operation<float>{
        
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
    
    
    class Division: public Operation<float>{
        
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
                else if(b==0.0){
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
}
#endif /* Operation_h */
