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
	std::vector<Node*>Pre;		//Pre: 计算某结点的Value依赖的前序结点
public:
	Node();
	Node(const std::string& InitName, const float& InitValue, const int& InitTime);
	float Calc(const int& CurTime, std::string& ErrorSignal);							//	计算某一结点的值
	void SetValue(const float& Input, const int& CurTime);								//	为结点赋值
	std::string GetName();																//	获得结点名
	float GetValue();																	//	获得结点值
	int GetTime();																		//	获得结点的时间标记
	virtual float Solve(std::string&ErrorSignal) = 0;									//	纯虚函数，便于派生类中重写覆盖: 进行不同种类运算符的计算
	virtual ~Node() = 0;																//	纯虚析构函数
};
#endif