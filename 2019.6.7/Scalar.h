#ifndef SCALAR_H
#define SCALAR_H

#include "Node.h"

//	变量
class Variable : public Node<float>
{
private:
public:
	Variable(const std::string& InitName, const float& InitValue);
	float Solve(std::string& ErrorSignal);
    void Backward (float , std::string &);
};

//	占位符
class Placeholder : public Node<float>
{
private:
public:
	Placeholder(const std::string& InitName);
	float Solve(std::string& ErrorSignal);
    void Backward (float , std::string &);
};

//	常量
class Constant : public Node<float>
{
private:
public:
	Constant(const std::string& InitName, const float& InitValue);
	float Solve(std::string& ErrorSignal);
    void Backward (float , std::string &);
};
#endif
