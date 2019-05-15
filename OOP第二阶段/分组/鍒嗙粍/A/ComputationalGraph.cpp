#include "ComputationalGraph.h"
#include <iomanip>

ComputationalGraph::ComputationalGraph()
{
	NodeMap.clear();
	PreAnswer.clear();
	NodeAddress.clear();
	TimeTag = 0;
}

//	��õ�ǰ����ͼ��ʱ����
int ComputationalGraph::GetTime()
{
	return TimeTag;
}

//	���ݽ����Ѱ����Ӧ���
Node* ComputationalGraph::Find(const std::string& NodeName)
{
	if (NodeMap.find(NodeName) == NodeMap.end())	return NULL;
	else return NodeMap[NodeName];
}

//	��õ� Index �������Ĵ�
float ComputationalGraph::GetPreviousAnswer(const int& Index)
{
	return PreAnswer[Index - 1];
}

//	�����ͼ�������½��
void ComputationalGraph::AddNode(Node* NewNode)
{
	NodeMap[NewNode->GetName()] = NewNode;
	NodeAddress.push_back(NewNode);
}

//	�����Ӧ�Ĵ�����Ϣ
void ComputationalGraph::ErrorPrint(std::ostream& OutStream)
{
	OutStream << "ERROR: " << ErrorSignal << std::endl;
}

//  ������ֵ������������������Ϣ��
float ComputationalGraph::Calc(const std::string& NodeName, const std::vector< std::pair<std::string, float> >& InitNode, std::ostream& OutStream)
{
	TimeTag++;							//	����ʱ����
	for (auto it : InitNode)
	{
		NodeMap[it.first]->SetValue(it.second, TimeTag);
	}
	ErrorSignal.clear();
	float tmpans = NodeMap[NodeName]->Calc(TimeTag, ErrorSignal);
	if (ErrorSignal.size() != 0)
	{
		PreAnswer.push_back(0);			//	��ĳ������ʹErrorSignal�ǿգ��޴𰸣���0ռλ;
		this->ErrorPrint(OutStream);	//	�����������Ϣ;
		return 0;						//	����
	}
	PreAnswer.push_back(tmpans);
	OutStream.setf(std::ios::fixed);
	OutStream << std::setprecision(4) << tmpans << std::endl;
	return tmpans;
}

//	��¼ SETCONSTANT �� SETANSWER ����
void ComputationalGraph::EmptyCall()
{
	PreAnswer.push_back(0);				//	��ĳ������ΪSET����ʱ����������𰸣�����0ռλ
	TimeTag++;
}

//	��������ͼ
ComputationalGraph::~ComputationalGraph()
{
	//	ɾ��NodeAddress��ÿ�����ָ��ָ����ڴ�
	for (auto it : NodeAddress)
	{
		delete it;
	}
	NodeMap.clear();
	NodeAddress.clear();
	PreAnswer.clear();
}