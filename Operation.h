
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
        
        Addition(SPointer Node1, SPointer Node2): Operation(Node1,Node2){}
        Addition(const string& a, SPointer Node1, SPointer Node2) : Operation(a,Node1,Node2){}
        
        float Forward() override{
            if(flag==false)                           //上一次计算得到的结果不合法
                return Minus_Max;
            else if(fabs(value-Minus_Max)>eps){      //上一次计算得到结果且合法
                return value;
            }
            
            else {                                     //第一次访问这个节点
                SPointer temp1(input_nodes[0]);        //将Wpointer转化为Spointer
                float a = temp1->Forward();     //得到其中一个参数数值
                if(fabs(a-Minus_Max)<eps){              //一个参数不合法
                    flag=false;
                    return Minus_Max;
                }
                SPointer temp2(input_nodes[1]);        //将Wpointer转化为Spointer
                float b=temp2->Forward();      //得到第二个参数
                if(fabs(b-Minus_Max)<eps){               //第二个参数不合法
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
        
        Multiply(SPointer Node1, SPointer Node2): Operation(Node1,Node2){}
        Multiply(const string a, SPointer Node1, SPointer Node2) : Operation(a,Node1,Node2){}
        
        float Forward() override{
            if(flag==false)                         //上一次计算结果不合法
                return Minus_Max;
            else if(fabs(value-Minus_Max)>eps){      //上次计算结果合法
                return value;
            }
        
            else {                                   //第一次访问这个节点
                SPointer temp1(input_nodes[0]);      //将Wpointer转化为Spointer
                float a = temp1->Forward();   //得到第一个参数
                if(fabs(a-Minus_Max)<eps){            //第一个参数不合法
                    flag=false;
                    return Minus_Max;
                }
                SPointer temp2(input_nodes[1]);     //将Wpointer转化为Spointer
                float b = temp2->Forward();         //得到第二个参数
                if(fabs(b-Minus_Max)<eps){           //第二个参数不合法
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
        
        Minus(SPointer Node1, SPointer Node2): Operation(Node1,Node2){}
        Minus(const string a, SPointer Node1, SPointer Node2) : Operation(a,Node1,Node2){}
        
        float Forward() override{
            if(flag==false)                          //上次计算结果不合法
                return Minus_Max;
            else if(fabs(value-Minus_Max>eps)){       //上一次计算结果合法
                return value;
            }
            
            else {                                    //第一次访问这个节点
                SPointer temp1(input_nodes[0]);         //将Wpointer转化为Spointer
                float a = temp1->Forward();    //得到第一个参数
                if(fabs(a-Minus_Max)<eps){             //第一个参数不合法
                    flag=false;
                    return Minus_Max;
                }
                SPointer temp2(input_nodes[1]);       //将Wpointer转化为Spointer
                float b=temp2->Forward();            //得到第二个参数
                if(fabs(b-Minus_Max)<eps){              //第二个参数不合法
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
        
        Division(SPointer Node1, SPointer Node2): Operation(Node1,Node2){}
        Division(const string a, SPointer Node1, SPointer Node2) : Operation(a,Node1,Node2){}
        
        float Forward() override{
            if(flag==false)                              //上一次访问结果不合法
                return Minus_Max;
            else if(fabs(value-Minus_Max>eps)){           //上一次j访问结果合法
                return value;
            }
            
            else {                                       //第一次访问这个节点
                SPointer temp1(input_nodes[1]);          //将Wpointer转化为Spointer
                float b = temp1->Forward(); 
                if(fabs(b-Minus_Max)<eps){                //第一个参数不合法
                    flag=false;
                   cout <<"!!!";           
                    return Minus_Max;
                }
              
                else if(fabs(b-0.0)<eps){                 //分母为0的特殊情况
                    flag=false;
                    std::cout<<"ERROR: Division by zero"<<endl;
                    return Minus_Max;
                }
                SPointer temp2(input_nodes[0]);          //将Wpointer转化为Spointer
                float a = temp2->Forward();    
		        //得到第二个参数
                if(fabs(a-Minus_Max<eps)){                 //第二个参数b不合法
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
        Xiaoyu(SPointer Node1, SPointer Node2): Operation(Node1,Node2){}
        Xiaoyu(const string a, SPointer Node1, SPointer Node2) : Operation(a,Node1,Node2){}
        float Forward() override{
            if(flag==false)                             //上一次访问结果不合法
                return Minus_Max;
            else if(fabs(value-Minus_Max)>eps){          //上一次访问结果合法
                return value;
            }
            
            else {                                       //第一次访问这个节点
                SPointer temp1(input_nodes[0]);          //将Wpointer转化为Spointer
                float a = temp1->Forward();       //得到第一个参数
                if(fabs(a-Minus_Max)<eps){                //第一个参数不合法
                    flag=false;
                    return Minus_Max;
                }
                SPointer temp2(input_nodes[1]);          //将Wpointer转化为Spointer
                float b = temp2->Forward();        //得到第二个参数
                if(fabs(b-Minus_Max)<eps){                 //第二个参数不合法
                    flag=false;
                    return Minus_Max;
                }
                value=(a-b<eps? 1.0:0.0);
                return value;
            }
            
        }
        void Backward() override {
            ;
        }
    };
    class Xiaodeng: public Operation<float>{//小于等于
    public:
        Xiaodeng(SPointer Node1, SPointer Node2): Operation(Node1,Node2){}
        Xiaodeng(const string a, SPointer Node1, SPointer Node2) : Operation(a,Node1,Node2){}
        float Forward() override{
            if(flag==false)                             //上一次访问结果不合法
                return Minus_Max;
            else if(fabs(value-Minus_Max)>eps){          //上一次访问结果合法
                return value;
            }
            
            else {                                       //第一次访问这个节点
                SPointer temp1(input_nodes[0]);          //将Wpointer转化为Spointer
                float a = temp1->Forward();       //得到第一个参数
                if(fabs(a-Minus_Max)<eps){                //第一个参数不合法
                    flag=false;
                    return Minus_Max;
                }
                SPointer temp2(input_nodes[1]);          //将Wpointer转化为Spointer
                float b = temp2->Forward();        //得到第二个参数
                if(fabs(b-Minus_Max)<eps){                 //第二个参数不合法
                    flag=false;
                    return Minus_Max;
                }
                value=(a-b<=eps? 1.0:0.0);
                return value;
            }
            
        }
        void Backward() override {
            ;
        }
    };
    class Dayu: public Operation<float>{//大于
    public:
        Dayu(SPointer Node1, SPointer Node2): Operation(Node1,Node2){}
        Dayu(const string a, SPointer Node1, SPointer Node2) : Operation(a,Node1,Node2){}
        float Forward() override{
            if(flag==false)                             //上一次访问结果不合法
                return Minus_Max;
            else if(fabs(value-Minus_Max)>eps){          //上一次访问结果合法
                return value;
            }
            
            else {                                       //第一次访问这个节点
                SPointer temp1(input_nodes[0]);          //将Wpointer转化为Spointer
                float a = temp1->Forward();       //得到第一个参数
                if(fabs(a-Minus_Max)<eps){                //第一个参数不合法
                    flag=false;
                    return Minus_Max;
                }
                SPointer temp2(input_nodes[1]);          //将Wpointer转化为Spointer
                float b = temp2->Forward();        //得到第二个参数
                if(fabs(b-Minus_Max)<eps){                 //第二个参数不合法
                    flag=false;
                    return Minus_Max;
                }
                value=(a-b>eps? 1.0:0.0);
                return value;
            }
            
        }
        void Backward() override {
            ;
        }
    };
    class Dadeng: public Operation<float>{//大于等于
    public:
        Dadeng(SPointer Node1, SPointer Node2): Operation(Node1,Node2){}
        Dadeng(const string a, SPointer Node1, SPointer Node2) : Operation(a,Node1,Node2){}
        float Forward() override{
            if(flag==false)                             //上一次访问结果不合法
                return Minus_Max;
            else if(fabs(value-Minus_Max)>eps){          //上一次访问结果合法
                return value;
            }
            
            else {                                       //第一次访问这个节点
                SPointer temp1(input_nodes[0]);          //将Wpointer转化为Spointer
                float a = temp1->Forward();       //得到第一个参数
                if(fabs(a-Minus_Max)<eps){                //第一个参数不合法
                    flag=false;
                    return Minus_Max;
                }
                SPointer temp2(input_nodes[1]);          //将Wpointer转化为Spointer
                float b = temp2->Forward();        //得到第二个参数
                if(fabs(b-Minus_Max)<eps){                 //第二个参数不合法
                    flag=false;
                    return Minus_Max;
                }
                value=(a-b>=eps? 1.0:0.0);
                return value;
            }
            
        }
        void Backward() override {
            ;
        }
    };
    class Dengyu: public Operation<float>{//等于号
    public:
        Dengyu(SPointer Node1, SPointer Node2): Operation(Node1,Node2){}
        Dengyu(const string a, SPointer Node1, SPointer Node2) : Operation(a,Node1,Node2){}
        float Forward() override{
            if(flag==false)                             //上一次访问结果不合法
                return Minus_Max;
            else if(fabs(value-Minus_Max)>eps){          //上一次访问结果合法
                return value;
            }
            
            else {                                       //第一次访问这个节点
                SPointer temp1(input_nodes[0]);          //将Wpointer转化为Spointer
                float a = temp1->Forward();       //得到第一个参数
                if(fabs(a-Minus_Max)<eps){                //第一个参数不合法
                    flag=false;
                    return Minus_Max;
                }
                SPointer temp2(input_nodes[1]);          //将Wpointer转化为Spointer
                float b = temp2->Forward();        //得到第二个参数
                if(fabs(b-Minus_Max)<eps){                 //第二个参数不合法
                    flag=false;
                    return Minus_Max;
                }
                value=(fabs(a-b)<eps? 1.0:0.0);
                return value;
            }
            
        }
        void Backward() override {
            ;
        }
    };
    class Budeng: public Operation<float>{//不等于号
    public:
        Budeng(SPointer Node1, SPointer Node2): Operation(Node1,Node2){}
        Budeng(const string a, SPointer Node1, SPointer Node2) : Operation(a,Node1,Node2){}
        float Forward() override{
            if(flag==false)                             //上一次访问结果不合法
                return Minus_Max;
            else if(fabs(value-Minus_Max)>eps){          //上一次访问结果合法
                return value;
            }
            
            else {                                       //第一次访问这个节点
                SPointer temp1(input_nodes[0]);          //将Wpointer转化为Spointer
                float a = temp1->Forward();       //得到第一个参数
                if(fabs(a-Minus_Max)<eps){                //第一个参数不合法
                    flag=false;
                    return Minus_Max;
                }
                SPointer temp2(input_nodes[1]);          //将Wpointer转化为Spointer
                float b = temp2->Forward();        //得到第二个参数
                if(fabs(b-Minus_Max)<eps){                 //第二个参数不合法
                    flag=false;
                    return Minus_Max;
                }
                value=(fabs(a-b)>eps? 1.0:0.0);
                return value;
            }
            
        }
        void Backward() override {
            ;
        }
    };
    
    class COND: public Operation<float>{
    public:
        COND(SPointer Node1, SPointer Node2, SPointer Node3): Operation(Node1,Node2,Node3){}
        COND(const string a, SPointer Node1, SPointer Node2, SPointer Node3) : Operation(a, Node1,Node2, Node3){}
        float Forward() override{
            if(flag==false)                             //上一次访问结果不合法
                return Minus_Max;
            else if(fabs(value-Minus_Max)>eps){          //上一次j访问结果合法
                return value;
            }
            
            else {                                      //第一次访问这个节点
                bool flag_t = true;
                SPointer temp1(input_nodes[0]);  //将Wpointer转化为Spointer
                float c = temp1->Forward();      //得到第一个参数
                if(fabs(c-Minus_Max)<eps){           //得到第一个参数不合法
                    flag=false;
                    return Minus_Max;
                }
                if(c > eps) flag_t=true;
                else if(c <= eps ) flag_t=false;
                SPointer temp2(input_nodes[1]);  //将Wpointer转化为Spointer
                float a = temp2->Forward();    //得到第2个参数
                if(fabs(a-Minus_Max)<eps){             //得到第2个参数不合法
                    flag=false;
                    return Minus_Max;
                }
                SPointer temp3(input_nodes[2]);  //将Wpointer转化为Spointer
                float b = temp3->Forward();     //得到第3个参数
                //      cout << b ;
                if(fabs(b-Minus_Max)<eps){              //得到第2个参数不合法
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
