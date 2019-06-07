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
    //add by Cai on 6.6
    float gradi=0;
    //
protected:
	std::vector<Node*>Pre;		//Pre: ����ĳ����Value������ǰ����
public:
	Node();
	Node(const std::string& InitName, const float& InitValue, const int& InitTime);
	float Calc(const int& CurTime, std::string& ErrorSignal);							//	����ĳһ����ֵ
	void SetValue(const float& Input, const int& CurTime);								//	Ϊ��㸳ֵ
	std::string GetName();																//	��ý����
	float GetValue();																	//	��ý��ֵ
    //
    float GetGradi ();
    void SetGradi (float);
    //
    
	int GetTime();																		//	��ý���ʱ����
	virtual float Solve(std::string&ErrorSignal) = 0;									//	���麯������������������д����: ���в�ͬ����������ļ���
    
    //add by Cai on 6.6
    virtual void Backward(float ,std::string&ErrorSignal) = 0;
    //
	virtual ~Node() = 0;																//	������������
};
#endif