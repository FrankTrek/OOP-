#include "Scalar.h"

Variable::Variable(const std::string& InitName, const float& InitValue) : Node(InitName, InitValue, 0) {}

float Variable::Solve(std::string&ErrorSignal)
{
	return GetValue();
}


Placeholder::Placeholder(const std::string& InitName) : Node(InitName, 0, 0) {}

float Placeholder::Solve(std::string&ErrorSignal)
{
	ErrorSignal = "Placeholder missing";				//	若需要计算某结点所依赖的占位符结点的值（而不是给出或者可以直接获得其取值），
	return 0;											//	则说明占位符未赋值 
}

Constant::Constant(const std::string& InitName, const float& InitValue) : Node(InitName, InitValue, 0) {}

float Constant::Solve(std::string&ErrorSignal)
{
	return GetValue();
}
