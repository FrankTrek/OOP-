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
        SIN(SPointer Node1): Operation(Node1){}
        SIN(const string& a, SPointer Node1) : Operation(a,Node1){}
        float Forward() override{
            if(flag==false)
                return Minus_Max;
            else if(fabs(value-Minus_Max)>eps)           //上一次j访问结果合法
                return value;
            else {                                     //第一次访问这个节点
                SPointer temp1(input_nodes[0]);       //将Wpointer转化为Spointer
                float a=temp1->Forward();      //得到第一个参数
                if(fabs(a-Minus_Max)<eps){               //得到第一个参数不合法
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
        EXP(SPointer Node1): Operation(Node1){}
        EXP(const string& a, SPointer Node1) : Operation(a,Node1){}
        float Forward() override{
            if(flag==false)
                return Minus_Max;
            else if(fabs(value-Minus_Max)>eps)            //上一次j访问结果合法
                return value;
            else {                                       //第一次访问这个节点
                SPointer temp1(input_nodes[0]);  //将Wpointer转化为Spointer
                float a=temp1->Forward();        //得到第一个参数
                if(fabs(a-Minus_Max)<eps){                //得到第一个参数不合法
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
        TANH(SPointer Node1): Operation(Node1){}
        TANH(const string& a, SPointer Node1) : Operation(a,Node1){}
        float Forward() override{
            if(flag==false)
                return Minus_Max;
            else if(fabs(value-Minus_Max)>eps)          //上一次j访问结果合法
                return value;
            else {                                     //第一次访问这个节点
                SPointer temp1(input_nodes[0]);        //将Wpointer转化为Spointer
                float a=temp1->Forward();              //得到第一个参数
                if(fabs(a-Minus_Max)<eps){              //得到第一个参数不合法
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
        LOG(SPointer Node1): Operation(Node1){}
        LOG(const string& a, SPointer Node1) : Operation(a,Node1){}
        float Forward() override{
            if(flag==false)
                return Minus_Max;
            else if(fabs(value-Minus_Max)>eps)          //上一次j访问结果合法
                return value;
            else {                                     //第一次访问这个节点
                SPointer temp1(input_nodes[0]);  //将Wpointer转化为Spointer
                float a=temp1->Forward();     //得到第一个参数
                if(fabs(a-Minus_Max)<eps){              //得到第一个参数不合法
                    flag=false;
                    return Minus_Max;
                }
                else {
                    if(a<eps){
                        flag=false;
                        std::cout<<"ERROR: LOG operator's input must be positive"<<endl;
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
        SINGMOID(SPointer Node1): Operation(Node1){}
        SINGMOID(const string& a, SPointer Node1) : Operation(a,Node1){}
        float Forward() override{
            if(flag==false)
                return Minus_Max;
            else if(fabs(value-Minus_Max)>eps)       //上一次j访问结果合法
                return value;
            else {                                  //第一次访问这个节点
                SPointer temp1(input_nodes[0]);  //将Wpointer转化为Spointer
                float a = temp1->Forward();      //得到第一个参数
                if(fabs(a-Minus_Max)<eps){           //得到第一个参数不合法
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
        Print(SPointer Node1): Operation(Node1){}
        Print(const string& a, SPointer Node1) : Operation(a,Node1){}
        float Forward() override{
            if(flag==false){
                return Minus_Max;
            }
            else if(fabs(value-Minus_Max)>eps)         //上一次j访问结果合法
                return value;
            else {                                    //第一次访问这个节点
                SPointer temp1(input_nodes[0]);  //将Wpointer转化为Spointer
                float a=temp1->Forward();    //得到第一个参数
                if(fabs(a-Minus_Max)<eps){             //得到第一个参数不合法
                    flag=false;
                    //cout<<"Print Operator: ";input_nodes[0]->Print();cout<<"= "<<a<<endl;
                    return Minus_Max;
                }
                else {
                    value=a;
                    cout<<"PRINT operator: ";temp1->Print();cout<<" = "<<std::fixed<<std::setprecision(4)<<a<<endl;
                    return value;
                }
            }
        }
        void Backward() override{
            
        }
    };
    
    
}


#endif /* Operation2_h */
