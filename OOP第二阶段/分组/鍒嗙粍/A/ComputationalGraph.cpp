#include "ComputationalGraph.h"
#include <iomanip>

ComputationalGraph::ComputationalGraph()
{
	NodeMap.clear();
	PreAnswer.clear();
	NodeAddress.clear();
	TimeTag = 0;
}

//	获得当前计算图的时间标记
int ComputationalGraph::GetTime()
{
	return TimeTag;
}

//	根据结点名寻找相应结点
Node* ComputationalGraph::Find(const std::string& NodeName)
{
	if (NodeMap.find(NodeName) == NodeMap.end())	return NULL;
	else return NodeMap[NodeName];
}

//	获得第 Index 个操作的答案
float ComputationalGraph::GetPreviousAnswer(const int& Index)
{
	return PreAnswer[Index - 1];
}

//	向计算图中增添新结点
void ComputationalGraph::AddNode(Node* NewNode)
{
	NodeMap[NewNode->GetName()] = NewNode;
	NodeAddress.push_back(NewNode);
}

//	输出对应的错误信息
void ComputationalGraph::ErrorPrint(std::ostream& OutStream)
{
	OutStream << "ERROR: " << ErrorSignal << std::endl;
}

//  计算结点值并输出（或输出错误信息）
float ComputationalGraph::Calc(const std::string& NodeName, const std::vector< std::pair<std::string, float> >& InitNode, std::ostream& OutStream)
{
	TimeTag++;							//	更新时间标记
	for (auto it : InitNode)
	{
		NodeMap[it.first]->SetValue(it.second, TimeTag);
	}
	ErrorSignal.clear();
	float tmpans = NodeMap[NodeName]->Calc(TimeTag, ErrorSignal);
	if (ErrorSignal.size() != 0)
	{
		PreAnswer.push_back(0);			//	当某个操作使ErrorSignal非空，无答案，用0占位;
		this->ErrorPrint(OutStream);	//	并输出错误信息;
		return 0;						//	返回
	}
	PreAnswer.push_back(tmpans);
	OutStream.setf(std::ios::fixed);
	OutStream << std::setprecision(4) << tmpans << std::endl;
	return tmpans;
}

//	记录 SETCONSTANT 和 SETANSWER 操作
void ComputationalGraph::EmptyCall()
{
	PreAnswer.push_back(0);				//	当某个操作为SET操作时，无输出（答案），用0占位
	TimeTag++;
}

//	析构计算图
ComputationalGraph::~ComputationalGraph()
{
	//	删除NodeAddress里每个结点指针指向的内存
	for (auto it : NodeAddress)
	{
		delete it;
	}
	NodeMap.clear();
	NodeAddress.clear();
	PreAnswer.clear();
}