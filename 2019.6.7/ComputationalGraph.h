#ifndef COMPUTATIONALGRAPH_H
#define COMPUTATIONALGRAPH_H

#include "Node.h"
#include <map>
#include <utility>
#include <sstream>
#include <iostream>
#include "Session.h"
template <typename T >
class ComputationalGraph
{
private:
    friend class AssignOperator;
    std::map<std::string, Node<T>*>NodeMap;    //NodeMap: 结点名到指向结点的指针的映射
    std::vector<float>PreAnswer;            //PreAnswer: 保存前序操作的答案
    std::string ErrorSignal;                //ErrorSignal: 记录错误信息
    int TimeTag;                            //TimeTag: 记录结点更新与计算的时间
    std::vector<Node<T>*>NodeAddress;           //NodeAddress：记录所有出现过的结点的指针，用于析构
    Session_Manager Manager;         //对不同varible存值的管理
public:
    ComputationalGraph(){
        NodeMap.clear();
        PreAnswer.clear();
        NodeAddress.clear();
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
    float Calc(const std::string& NodeName, const std::vector<std::pair<std::string, T> >& InitNode, std::ostream& OutStream);    //  计算图中的结点值并输出（或输出错误信息）
    void AddNode(Node<T>* NewNode){
        NodeMap[NewNode->GetName()] = NewNode;
        NodeAddress.push_back(NewNode);
    }                //    向计算图中增添新结点
    void EmptyCall();                            //    记录 SETCONSTANT 和 SETANSWER 操作
    
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



class AssignOperator: public Node<float>{
private:
    Session_Manager* Manager;
public:
    AssignOperator(const std::string& InitName, const std::vector<Node*>& InitPre, Session_Manager* Manager1);
    float Solve(std::string& ErrorSignal);
    void Backward(float ,std::string&ErrorSignal);
};


#endif
