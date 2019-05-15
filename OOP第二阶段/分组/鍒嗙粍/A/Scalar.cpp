#include "Scalar.h"

Variable::Variable(const std::string& InitName, const float& InitValue) : Node(InitName, InitValue, 0) {}

float Variable::Solve(std::string&ErrorSignal)
{
	return GetValue();
}


Placeholder::Placeholder(const std::string& InitName) : Node(InitName, 0, 0) {}

float Placeholder::Solve(std::string&ErrorSignal)
{
	ErrorSignal = "Placeholder missing";				//	����Ҫ����ĳ�����������ռλ������ֵ�������Ǹ������߿���ֱ�ӻ����ȡֵ����
	return 0;											//	��˵��ռλ��δ��ֵ 
}

Constant::Constant(const std::string& InitName, const float& InitValue) : Node(InitName, InitValue, 0) {}

float Constant::Solve(std::string&ErrorSignal)
{
	return GetValue();
}
