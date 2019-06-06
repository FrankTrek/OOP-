#ifndef COMPUTATIONALGRAPH_H
#define COMPUTATIONALGRAPH_H

#include "Node.h"
#include "Scalar.h"
#include "Operator.h"
#include <map>
#include <utility>
#include <sstream>
#include <iostream>

class ComputationalGraph
{
private:
	std::map<std::string, Node*>NodeMap;	//NodeMap: �������ָ�����ָ���ӳ��
	std::vector<float>PreAnswer;			//PreAnswer: ����ǰ������Ĵ�
	std::string ErrorSignal;				//ErrorSignal: ��¼������Ϣ
	int TimeTag;							//TimeTag: ��¼������������ʱ��
	std::vector<Node*>NodeAddress;			//NodeAddress����¼���г��ֹ��Ľ���ָ�룬��������
	
public:
	ComputationalGraph();
	void ErrorPrint(std::ostream& OutStream);	//	�����Ӧ�Ĵ�����Ϣ
	Node *Find(const std::string& NodeName);	//	���ݽ����Ѱ����Ӧ���
	int GetTime();								//	��õ�ǰ����ͼ��ʱ����
	float GetPreviousAnswer(const int& Index);	//	��õ� Index �������Ĵ�
	float Calc(const std::string& NodeName, const std::vector<std::pair<std::string, float> >& InitNode, std::ostream& OutStream);	//  ����ͼ�еĽ��ֵ������������������Ϣ��
	void AddNode(Node* NewNode);				//	�����ͼ�������½��
	void EmptyCall();							//	��¼ SETCONSTANT �� SETANSWER ����
    
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
