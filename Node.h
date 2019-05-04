//
//  Node.h
//  OOP Computation Graph
//
//  Created by 王一诺 on 2019/4/5.
//  Copyright ? 2019 王一诺. All rights reserved.
//

//更新日志 latest date 4.7
/*
 *4.7  在Node.h中的枚举量中添加Trinary，
 *4.7  在Node.h中的Node类补充提供参数的构造函数
 *4.8  将Node.h中vlaue转移至保护成员
 *4.8  补充了查看数值的方法
 *4.8  Z.补充了Reset，将所有后续flag设置为0 value为-Max的接口
 *4.8  Z.补充了只有string初始化Node的接口
 * 4.10 Z.补充了forward的报错信息和对flag的设置
 * 4.10 Z.修改了只用string初始化Node,使placeholder初始化为-max
 * 4.10 Z.Attention:修改RESET
 * 4.12 将operation类的构造函数由传引用改为传指针
 * 4.13 补充了三元运算符的构造函数
 * 4.20 Z.修改了Error的报错信息
 * 4.20 Z.补充了Node类中的type函数 返回type
 *5.2 移除了与后继节点相关的方法
 */
#ifndef Node_h
#define Node_h
#include "BaseNode.h"
#include <vector>
#include <sstream>
using std::vector ;

namespace Computational_Graph{
    enum{Nullary, Unary, Binary, Trinary};                               //用于标记计算符的参数个数
    
    template <typename T>
    class Node : public BaseNode<T>
    {
        
    protected:
        T value;    //节点的值
        T gradi;    //节点的导数
        
    public:
        Node() = default;
        Node(const T& a): value(a) {}                                      //包含数值初始化的构造函数
        Node(const T& a, const string& b):BaseNode<T>(b), value(a) {}
        Node(const string& b):BaseNode<T>(b){
            value = Minus_Max ;
        } ;
        virtual void Initalize(T& data) override
        {
            value = data;
        }
        virtual T Forward () override                                       //正向传播的零元运算的接口
        {
            if(value == Minus_Max) {
                std::cout << "ERROR: Placeholder missing\n";
                this->flag = 0 ;
            }
            return value;
        }
        virtual T Value () const override                                       //返回节点数值
        {
            return value;
        }
        //调试用函数
        void debug_print(){
            std::cerr << this->value << "|" << this->flag << endl ;
        }
        //
        void Reset() override final{//重置此节点至未计算状态
            this->flag = 1;
            this->value = Minus_Max ;
        }
        

        void Reset_b() override final{//反向重置-重置此节点和它的所有直接间接前序节点至未计算状态
            if(this->returntype() == "Constant" || this->returntype() == "Variable"){//
                return ;
            }
            else
            {
                this->Reset();
                for(auto i: this->input_nodes){
                    SPointer temp(i);      //得到Spointer
                    temp->Reset_b() ;
                }
            }
        }
        
        
        ~Node(){}
        
    };
    template <typename T>
    class Operation : public BaseNode<T>
    {
        
    protected:
        T value;    //节点的值
        T gradi;    //节点的导数
        int type;
    public:
        using BaseNode<T>::Set_input_nodes;
        Operation() { type = Nullary; }       //0元运算符
        Operation (std::shared_ptr<BaseNode<T> >node1)        //1元运算符
        {
            
            Set_input_nodes(node1);
            type = Unary;
            value = Minus_Max;
        }
        Operation (std::shared_ptr<BaseNode<T> > node1,std::shared_ptr<BaseNode<T> > node2) //2元运算符
        {
           
            Set_input_nodes(node1);
            Set_input_nodes(node2);
            type = Binary;
            value = Minus_Max;
        }
        //这里补充三元运算符
        Operation (std::shared_ptr<BaseNode<T> > node1, std::shared_ptr<BaseNode<T> > node2, std::shared_ptr<BaseNode<T> > node3)// 三元运算符
        {
            Set_input_nodes(node1);
            Set_input_nodes(node2);
            Set_input_nodes(node3);
            type = Trinary;
            value = Minus_Max;
        }
        //结束
        
        string returntype() override final{
            return "Operation" ;
        }
        
        void Reset() override final{//重置这一操作符节点至未计算状态
            this->flag = 1;
            this->value = Minus_Max ;
        }
        
        void Reset_b() override final{//重置这一节点的所有前序（直接&间接）至未计算状态
            if(this->returntype() == "Constant" || this->returntype() == "Variable"){
                return ;
            }
            else
            {
                this->Reset();
                for(auto i: this->input_nodes){
                    SPointer temp(i);
                    temp->Reset_b() ;
                }
            }
            
        }
        
        //以上为匿名版本
        //以下为带名称的版本
        Operation(const string& a):BaseNode<T>(a) { type = Nullary; }       //0元运算符
        Operation (const string& a,std::shared_ptr<BaseNode<T> > node1):BaseNode<T>(a)        //1元运算符
        {
            
            Set_input_nodes(node1);
            type = Unary;
            value = Minus_Max;
        }
        Operation (const string& a,std::shared_ptr<BaseNode<T> > node1,std::shared_ptr<BaseNode<T> > node2):BaseNode<T>(a) //2元运算符
        {
            
            Set_input_nodes(node1);
            Set_input_nodes(node2);//这里需要改动
            type = Binary;
            value = Minus_Max;
        }
        
        Operation (const string& a,std::shared_ptr<BaseNode<T> > node1,std::shared_ptr<BaseNode<T> > node2,std::shared_ptr<BaseNode<T> > node3):BaseNode<T>(a) //2元运算符
        {
            
            Set_input_nodes(node1);
            Set_input_nodes(node2);
            Set_input_nodes(node3);
            type = Trinary;
            value = Minus_Max;
        }
        virtual T Value () const override                                       //返回节点数值
        {
            return value;
        }
        //
        void debug_print(){
            std::cerr << this->value << "|" << this->flag << endl ;
        }
        
        //
    };
}


#endif /* Node_h */
