
//
//  Operation.h
//  OOP Computation Graph
//
//  Created by ��һŵ on 2019/4/13.
//  Copyright ? 2019 ��һŵ. All rights reserved.
//

//
//  Operation.h
//  �����Ĵ���ҵ
//
//  Created by �� on 2019/4/8.
//  Copyright ? 2019�� ��. All rights reserved.
//
//4.12 ��operation��Ĺ��캯���ɴ����ø�Ϊ��ָ��
//4.13 ���������ж�Ԫ�����Լ�COND����
#ifndef Operation_h
#define Operation_h
#include "BaseNode.h"
#include "Node.h"
#include <cmath>


namespace  Computational_Graph{
    class Addition : public Operation<float>{//�Ӻ�
        
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
    class Multiply: public Operation<float>{//�˺�
        
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
    class Minus: public Operation<float>{//����
        
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
    
    
    class Division: public Operation<float>{//����
        
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
    class Xiaoyu: public Operation<float>{//С��
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
    class Xiaodeng: public Operation<float>{//С�ڵ���
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
    class Dayu: public Operation<float>{//����
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
    class Dadeng: public Operation<float>{//���ڵ���
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
    class Dengyu: public Operation<float>{//���ں�
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
    class Budeng: public Operation<float>{//�����ں�
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
                bool flag_t;
                float c=input_nodes[0]->Forward();
                if(c==Minus_Max){
                    flag=false;
                    return Minus_Max;
                }
                if(c > eps) flag_t=true;
                else if(c <= eps ) flag_t=false;
                
                float a=input_nodes[1]->Forward();
                if(a==Minus_Max){
                    flag=false;
                    return Minus_Max;
                }
                float b=input_nodes[2]->Forward();
          //      cout << b ;
                if(b==Minus_Max){
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
