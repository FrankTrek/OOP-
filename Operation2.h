//
//  Operation2.h
//  ÕæÕýµÄ´ó×÷Òµ
//
//  Created by ²Ì on 2019/4/15.
//  Copyright ? 2019Äê ²Ì. All rights reserved.
//

#ifndef Operation2_h
#define Operation2_h
#include "Node.h"
#include <cmath>
#include <iomanip>
//SIN,LOG,EXP,TANH,sigmoid,Print
namespace Computational_Graph{
    class SIN: public Operation<float>{
    public:
        SIN(BaseNode<float>* Node1): Operation(Node1){}
        SIN(const string& a, BaseNode<float>* Node1) : Operation(a,Node1){}
        float Forward() override{
            if(flag==false)
                return Minus_Max;
            else if(abs(value-Minus_Max)>eps)           //上一次j访问结果合法
                return value;
            else {                                      //第一次访问这个节点
                float a=input_nodes[0]->Forward();      //得到第一个参数
                if(abs(a-Minus_Max)<eps){               //得到第一个参数不合法
                    flag=false;
                    return Minus_Max;
                }
                else {
                    value=sin(a);
                    return value;
                }
            }
        }
        void Backward() override{
            
        }
    };
    class EXP: public Operation<float>{
    public:
        EXP(BaseNode<float>* Node1): Operation(Node1){}
        EXP(const string& a, BaseNode<float>* Node1) : Operation(a,Node1){}
        float Forward() override{
            if(flag==false)
                return Minus_Max;
            else if(abs(value-Minus_Max)>eps)            //上一次j访问结果合法
                return value;
            else {                                       //第一次访问这个节点
                float a=input_nodes[0]->Forward();        //得到第一个参数
                if(abs(a-Minus_Max)<eps){                //得到第一个参数不合法
                    flag=false;
                    return Minus_Max;
                }
                else {
                    value=exp(a);
                    if(value> - Minus_Max + eps)
                    {
                        std::cerr<<"Numeric Limit Exceeded\n";
                        flag = false;
                        return Minus_Max;
                    }
                    return value;
                }
            }
        }
        void Backward() override{
            
        }
    };
    class TANH: public Operation<float>{
    public:
        TANH(BaseNode<float>* Node1): Operation(Node1){}
        TANH(const string& a, BaseNode<float>* Node1) : Operation(a,Node1){}
        float Forward() override{
            if(flag==false)
                return Minus_Max;
            else if(abs(value-Minus_Max)>eps)          //上一次j访问结果合法
                return value;
            else {                                     //第一次访问这个节点
                float a=input_nodes[0]->Forward();     //得到第一个参数
                if(abs(a-Minus_Max)<eps){              //得到第一个参数不合法
                    flag=false;
                    return Minus_Max;
                }
                else {
                    value=tanh(a);
                    if(value> - Minus_Max + eps||value < Minus_Max - eps)
                    {
                        std::cerr<<"Numeric Limit Exceeded\n";
                        flag = false;
                        return Minus_Max;
                    }
                    return value;
                }
            }
        }
        void Backward() override{
            
        }
    };
    class LOG: public Operation<float>{
    public:
        LOG(BaseNode<float>* Node1): Operation(Node1){}
        LOG(const string& a, BaseNode<float>* Node1) : Operation(a,Node1){}
        float Forward() override{
            if(flag==false)
                return Minus_Max;
            else if(abs(value-Minus_Max)>eps)          //上一次j访问结果合法
                return value;
            else {                                     //第一次访问这个节点
                float a=input_nodes[0]->Forward();     //得到第一个参数
                if(abs(a-Minus_Max)<eps){              //得到第一个参数不合法
                    flag=false;
                    return Minus_Max;
                }
                else {
                    if(a<eps){
                        flag=false;
                        std::cerr<<"Error: LOG operator's input must be positive"<<endl;
                        return Minus_Max;
                    }
                    else{
                        value=log(a);
                        if(value> - Minus_Max + eps||value < Minus_Max - eps)
                        {
                            std::cerr<<"Numeric Limit Exceeded\n";
                            flag = false;
                            return Minus_Max;
                        }
                        return value;
                    }
                }
            }
        }
        void Backward() override{
            
        }
    };
    class SINGMOID: public Operation<float>{
    public:
        SINGMOID(BaseNode<float>* Node1): Operation(Node1){}
        SINGMOID(const string& a, BaseNode<float>* Node1) : Operation(a,Node1){}
        float Forward() override{
            if(flag==false)
                return Minus_Max;
            else if(abs(value-Minus_Max)>eps)       //上一次j访问结果合法
                return value;
            else {                                  //第一次访问这个节点
                float a=input_nodes[0]->Forward();  //得到第一个参数
                if(abs(a-Minus_Max)<eps){           //得到第一个参数不合法
                    flag=false;
                    return Minus_Max;
                }
                else {
                    value=1/(1+exp(-1*a));
                    return value;
                }
            }
        }
        void Backward() override{
            
        }
    };
    //*****
    class Print: public Operation<float>{
    public:
        Print(BaseNode<float>* Node1): Operation(Node1){}
        Print(const string& a, BaseNode<float>* Node1) : Operation(a,Node1){}
        float Forward() override{
            if(flag==false){
                return Minus_Max;
            }
            else if(abs(value-Minus_Max)>eps)         //上一次j访问结果合法
                return value;
            else {                                    //第一次访问这个节点
                float a=input_nodes[0]->Forward();    //得到第一个参数
                if(abs(a-Minus_Max)<eps){             //得到第一个参数不合法
                    flag=false;
                    //cout<<"Print Operator: ";input_nodes[0]->Print();cout<<"= "<<a<<endl;
                    return Minus_Max;
                }
                else {
                    value=a;
                    cout<<"Print Operator: ";input_nodes[0]->Print();cout<<"= "<<std::fixed<<std::setprecision(4)<<a<<endl;
                    return value;
                }
            }
        }
        void Backward() override{
            
        }
    };
    
    
}


#endif /* Operation2_h */
