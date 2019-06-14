#ifndef COMPUTATIONALGRAPH_H
#define COMPUTATIONALGRAPH_H

#include "Node.h"
#include "Scalar.h"
#include "Operator.h"
#include "Tensor.h"
#include <map>
#include <utility>
#include <sstream>
#include <iostream>
#include "Session.h"
template <typename T >
class ComputationalGraph
{
private:
    template <typename To>
    friend class AssignOperator;
    std::map<std::string, Node<T>*>NodeMap;    //NodeMap: 结点名到指向结点的指针的映射
    std::vector<T>PreAnswer;            //PreAnswer: 保存前序操作的答案
    std::string ErrorSignal;                //ErrorSignal: 记录错误信息
    int TimeTag;                            //TimeTag: 记录结点更新与计算的时间
    std::vector<Node<T>*>NodeAddress;           //NodeAddress：记录所有出现过的结点的指针，用于析构
    Session_Manager<T> Manager;         //对不同varible存值的管理
    std::vector<Node<T>*> Order_of_Derive;
public:
    ComputationalGraph(){
        NodeMap.clear();
        PreAnswer.clear();
        NodeAddress.clear();
        Order_of_Derive.clear();
        TimeTag = 0;
    }
    void ErrorPrint(std::ostream& OutStream);    //    输出对应的错误信息
    Node<T> *Find(const std::string& NodeName){
        if (NodeMap.find(NodeName) == NodeMap.end())    return NULL;
        else return NodeMap[NodeName];
    }    //    根据结点名寻找相应结点
    int GetTime(){
        return TimeTag;
    }                             //    获得当前计算图的时间标记
    T GetPreviousAnswer(const int& Index){
        return PreAnswer[Index - 1];
    }    //    获得第 Index 个操作的答案
    void Calc(const std::string& NodeName, const std::vector<std::pair<std::string, T> >& InitNode, std::ostream& OutStream);    //  计算图中的结点值并输出（或输出错误信息）
    void AddNode(Node<T>* NewNode){
        NodeMap[NewNode->GetName()] = NewNode;
        NodeAddress.push_back(NewNode);
    }                //    向计算图中增添新结点
    void EmptyCall();                            //    记录 SETCONSTANT 和 SETANSWER 操作
    
    //准备特化为Tensor的计算图
    friend Tensor ToTensor(std::vector<std::string>& a,int& start);
    ///
    
    //Add by Cai on 5.22
    
    std::vector<std::string> info;
    
    void  incision(){
        while (!info.empty()) info.pop_back();
        std::string sentence;
        std::getline(std::cin, sentence);
        std::stringstream s1(sentence);
        std::string tmp;
        while (s1>>tmp) {
            if(tmp!="=") info.push_back(tmp);
        }
    }
    
    void workstage1();
    void workstage2();
    void workstage3();
    
    //End Add
    
    ~ComputationalGraph(){
        for (auto it : NodeAddress)
        {
            delete it;
        }
        NodeMap.clear();
        NodeAddress.clear();
        PreAnswer.clear();
    }
};





template <typename T>
class AssignOperator: public Node<T>{
private:
    Session_Manager<T>* Manager;
public:
    AssignOperator(const std::string& InitName, const std::vector<Node<T>*>& InitPre, Session_Manager<T>* Manager1);
    T Solve(std::string& ErrorSignal, std::vector<Node<T>*>* Order_of_Derive=0){
        
            if (ErrorSignal.size() != 0)  return 0;
            this->Pre[1]->Calc(this->GetTime(), ErrorSignal);
            if (ErrorSignal.size() != 0)  return 0;
            Tensor Value_receive = this->Pre[1]->GetValue();
            Manager->Set_Value(this->Pre[0]->GetName(), Value_receive);
            return this->Pre[0]->Calc(this->GetTime(), ErrorSignal);
        
    };
    void Backward(T ,std::string&ErrorSignal);
};


template <typename T>
void ComputationalGraph<T>::workstage2(){
    std::string ini;
    getline(std::cin, ini);
    int times= std::stoi(ini);
    
    while (times--) {
        incision();
        if(info[2]=="+")                 //为加法;
        {
            std::vector<Node<T>*> vs;
            vs.push_back(Find(info[1]));
            vs.push_back(Find(info[3]));
            AddNode(new PlusOperator<T>(info[0],vs));
        }
        else if(info[2]=="-")                 //为乘法
        {
            std::vector<Node<T>*> vs;
            vs.push_back(Find(info[1]));
            vs.push_back(Find(info[3]));
            AddNode(new MinusOperator<T>(info[0],vs));
        }
        else if(info[2]=="*"){
            std::vector<Node<T>*> vs;
            vs.push_back(Find(info[1]));
            vs.push_back(Find(info[3]));
            AddNode(new MultipleOperator<T>(info[0],vs));
        }
        else if(info[2]=="/")
        {
            //Div(info[0], info[1], info[3]);
            std::vector<Node<T>*> vs;
            vs.push_back(Find(info[1]));
            vs.push_back(Find(info[3]));
            AddNode(new DivisionOperator(info[0],vs));
        }
        else if(info[2]=="<")
        {
            std::vector<Node<T>*> vs;
            vs.push_back(Find(info[1]));
            vs.push_back(Find(info[3]));
            AddNode(new LessOperator(info[0],vs));
        }
        else if(info[2]=="<=")
        {
            std::vector<Node<T>*> vs;
            vs.push_back(Find(info[1]));
            vs.push_back(Find(info[3]));
            AddNode(new LessEqualOperator(info[0],vs));
        }
        else if(info[2]==">")
        {
            std::vector<Node<T>*> vs;
            vs.push_back(Find(info[1]));
            vs.push_back(Find(info[3]));
            AddNode(new GreaterOperator(info[0],vs));
        }
        else if(info[2]==">=")
        {
            std::vector<Node<T>*> vs;
            vs.push_back(Find(info[1]));
            vs.push_back(Find(info[3]));
            AddNode(new GreaterEqualOperator(info[0],vs));
        }
        else if(info[2]=="==")
        {
            std::vector<Node<T>*> vs;
            vs.push_back(Find(info[1]));
            vs.push_back(Find(info[3]));
            AddNode(new EqualOperator(info[0],vs));
        }
        else if (info[1]=="BIND")
        {
            std::vector<Node<T>*> vs;
            vs.push_back(Find(info[2]));
            vs.push_back(Find(info[3]));
            AddNode(new BindOperator(info[0],vs));
        }
        else if (info[2]=="AT")
        {
            std::vector<Node<T>*> vs;
            vs.push_back(Find(info[1]));
            vs.push_back(Find(info[3]));
            AddNode(new AtOperator(info[0],vs));
        }
        else if(info[1]=="ASSIGN")
        {
            std::vector<Node<T>*> vs;
            vs.push_back(Find(info[2]));
            vs.push_back(Find(info[3]));
            AddNode(new AssignOperator<T>(info[0],vs,&Manager));
        }
        else if(info[1]=="SIN")
        {
            std::vector<Node<T>*> vs;
            vs.push_back(Find(info[2]));
            AddNode(new SinOperator<T>(info[0],vs));
        }
        else if(info[1]=="LOG")
        {
            std::vector<Node<T>*> vs;
            vs.push_back(Find(info[2]));
            AddNode(new LogOperator<T>(info[0],vs));
        }
        else if(info[1]=="TANH")
        {
            std::vector<Node<T>*> vs;
            vs.push_back(Find(info[2]));
            AddNode(new TanhOperator<T>(info[0],vs));
        }
        else if(info[1]=="EXP")
        {
            std::vector<Node<T>*> vs;
            vs.push_back(Find(info[2]));
            AddNode(new ExpOperator<T>(info[0],vs));
        }
        else if(info[1]=="SIGMOID")
        {
            std::vector<Node<T>*> vs;
            vs.push_back(Find(info[2]));
            AddNode(new SigmoidOperator<T>(info[0],vs));
        }
        else if(info[1]=="PRINT" || info[1] == "Print")
        {
            std::vector<Node<T>*> vs;
            vs.push_back(Find(info[2]));
            AddNode(new PrintOperator<T>(info[0],vs,std::cout));
        }
        else if (info[1]=="ASSERT")
        {
            std::vector<Node<T>*> vs;
            vs.push_back(Find(info[2]));
            AddNode(new AssertOperator(info[0],vs));
        }
        else if (info[1]=="GRAD")
        {
            std::vector<Node<T>*> vs;
            vs.push_back(Find(info[2]));
            AddNode(new GradOperator(info[0],vs,&Order_of_Derive));
        }
        else if(info[1]=="COND")
        {
            std::vector<Node<T>*> vs;
            vs.push_back(Find(info[2]));
            vs.push_back(Find(info[3]));
            vs.push_back(Find(info[4]));
            AddNode(new CondOperator(info[0],vs));
        }
    }
}

#endif


