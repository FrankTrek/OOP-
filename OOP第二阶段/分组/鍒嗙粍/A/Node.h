#ifndef NODE_H
#define NODE_H

#include<vector>
#include<string>

const float Epsi = 1e-7;

class Node
{
private:
	int Time;
	std::string Name;
	float Value;
protected:
	std::vector<Node*>Pre;		//Pre: ����ĳ����Value������ǰ����
public:
	Node();
	Node(const std::string& InitName, const float& InitValue, const int& InitTime);
	float Calc(const int& CurTime, std::string& ErrorSignal);							//	����ĳһ����ֵ
	void SetValue(const float& Input, const int& CurTime);								//	Ϊ��㸳ֵ
	std::string GetName();																//	��ý����
	float GetValue();																	//	��ý��ֵ
	int GetTime();																		//	��ý���ʱ����
	virtual float Solve(std::string&ErrorSignal) = 0;									//	���麯������������������д����: ���в�ͬ����������ļ���
	virtual ~Node() = 0;																//	������������
};
#endif