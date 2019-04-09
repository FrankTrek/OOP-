//
//  BaseNode.h
//  OOP Computation Graph
//
//  Created by 王一诺 on 2019/4/4.
//  Copyright © 2019 王一诺. All rights reserved.
//
//更新日志 lastest date 4.7
/*
 *4.7 补充了initalise的接口注释并在BaseNode功能中指出
 *4.7 补充了重制函数，作为保护成员，支持多态
 *4.8 增加了返回是否合法的方法
 *4.8 补充了节点名称，并更新了构造函数
 *4.8 补充了重置函数的接口
 *4.8 补充了提供节点数值的接口，为const类型纯虚函数
 *4.8 Z.设置了setflag接口
 */




//hhh
#ifndef BaseNode_h
#define BaseNode_h
#include <vector>
#include <string>
#include <iostream>
namespace Computational_Graph
{
    //所有的Computatal Garph相关类储存在Computational_Graph名称空间中
    using std::string;
    using std::ostream;
    using std::istream;
    using std::cout;
    using std::endl;
    const float Minus_Max = -100000000000;    //用于给定float下界以判断是否完成输入
    enum { Varible, Const, Operator };
    //写在之前的警告⚠️：必须在之后的继承类中补充关于前向传播的定义，否则继承类将依然成为虚类⚠️⚠️⚠️
    template <typename T>
    class BaseNode
    {
    protected:
        typedef std::vector<BaseNode*> NodeArray;  //在BaseNode名称空间中NodeArray为std::vector<BaseNode*>的别名
        bool flag;            //检验输入是否合法的标记
        NodeArray output_nodes;       //记录后继节点的数组
        NodeArray input_nodes;        //记录前继节点的数组
        string name;                  //记录节点名称
        
    public:
        BaseNode() { flag = true; }
        BaseNode(const string& a): name(a){flag = true;}
        virtual ~BaseNode() {}
        
        //以下为提供的接口
        bool IsValid() const {return flag;}       //返回是否合法的方法
        virtual void Reset() { 
			cout<<"this funct has not been defined yet\n"; }  //提供重新初始化的接口（归零）
        virtual void Reset(T& a) { cout<<"this funct has not been defined yet\n"; } //提供重新初始化的接口（含参数）
        virtual T Value() const =0;//显示value的接口
        
        void Set_flag(bool i){
        	flag = i ;
		} 
        void Set_output_nodes( BaseNode* b)      //构建后继节点集
        {
            output_nodes.push_back(b);
        }
        
        void Set_input_nodes( BaseNode* b)       //构建前继节点集
        {
            input_nodes.push_back(b);
        }
        virtual void Initalize(T& data)          //用于输入节点的初始话接口
        {
            cout<<"Func Initalize(T data) has not yet been defined\n";
        }
        virtual void SetConst(T& data)     //Variable节点的操作接口
        {
            cout<<"Func SetConst(T data) has not yet been defined\n";
        }
        virtual void SetAnswer(int n)     //Variable节点的操作接口
        {
            cout<<"Func SetAnswer(int n) has not yet been defined\n";
        }
        
        virtual T Forward () = 0;                                  //正向传播的运算的接口
        
        virtual void Backward()     //后向传播的接口
        {
            cout<<"Func Backward()  has not yet been defined\n";
        }
        virtual void Print()          //打印信息的接口
        {
            cout<<"Func Print() has not yet been defined\n";
        }
        
        
        // 以下为禁用一些默认的格式转换
        BaseNode (const BaseNode& A) = delete;
        BaseNode (BaseNode&& A) =delete ;
        BaseNode& operator = (const BaseNode& A) = delete;
        BaseNode& operator = (BaseNode&& A) = delete;
    };
    
    /* 这个基类实现的功能：
     *形式为模版类编程
     *以受保护成员的形式提供了判断是否输入合法的旗帜
     *以受保护成员的形式提供了前继节点集和后继节点集
     *提供了前向传播的主要接口
     *为后向传播预留了借口
     *关闭了各种复制以及类型转换
     *输入节点的初始话接口
     
     
     
     *将在Operator类中补充各种类型的运算操作
     *将在Variable与Const类中补充它的数值信息以及赋值操作
     */
    template <typename T>
    struct Graph_Node{
        BaseNode<T> * node;              //指向基类节点的指针
        string Nodename;                 //节点的名称
        int Mode;                        //节点的种类
    };                                   //计算图中的节点
}

#endif /* BaseNode_h */

