#ifndef COMPUTATIONALGRAPH_H
#define COMPUTATIONALGRAPH_H

#include "Node.h"
#include <map>
#include <utility>
#include <iostream>

class ComputationalGraph
{
private:
	std::map<std::string, Node*>NodeMap;	//NodeMap: 结点名到指向结点的指针的映射
	std::vector<float>PreAnswer;			//PreAnswer: 保存前序操作的答案
	std::string ErrorSignal;				//ErrorSignal: 记录错误信息
	int TimeTag;							//TimeTag: 记录结点更新与计算的时间
	std::vector<Node*>NodeAddress;			//NodeAddress：记录所有出现过的结点的指针，用于析构
public:
	ComputationalGraph();
	void ErrorPrint(std::ostream& OutStream);	//	输出对应的错误信息
	Node *Find(const std::string& NodeName);	//	根据结点名寻找相应结点
	int GetTime();								//	获得当前计算图的时间标记
	float GetPreviousAnswer(const int& Index);	//	获得第 Index 个操作的答案
	float Calc(const std::string& NodeName, const std::vector<std::pair<std::string, float> >& InitNode, std::ostream& OutStream);	//  计算图中的结点值并输出（或输出错误信息）
	void AddNode(Node* NewNode);				//	向计算图中增添新结点
	void EmptyCall();							//	记录 SETCONSTANT 和 SETANSWER 操作
	
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
	
	
	~ComputationalGraph();
};
#endif
