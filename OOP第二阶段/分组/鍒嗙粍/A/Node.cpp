#include "Node.h"

Node::Node()
{
	Name = "";
	Value = 0;
	Time = 0;
	Pre.clear();
}

Node::Node(const std::string& InitName, const float& InitValue, const int& InitTime)
{
	Name = InitName;
	Value = InitValue;
	Time = InitTime;
	Pre.clear();
}

float Node::Calc(const int& CurTime, std::string&ErrorSignal)
{
	if (Time == CurTime)					//	若结点对应的时间等于当前时间，可以直接返回Value;
	{
		return Value;
	}
	Time = CurTime;
	Value = this->Solve(ErrorSignal);		//	否则，重新计算
	return Value;
}

void Node::SetValue(const float& Input, const int& CurTime)
{
	Value = Input;
	Time = CurTime;
}

int Node::GetTime()
{
	return Time;
}

std::string Node::GetName()
{
	return Name;
}

float Node::GetValue()
{
	return Value;
}

Node::~Node() {}