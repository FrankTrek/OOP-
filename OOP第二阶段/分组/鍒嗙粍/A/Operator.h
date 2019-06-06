#ifndef OPERATOR_H
#define OPERATOR_H

#include "Node.h"
#include<iostream>

//  加法
class PlusOperator : public Node
{
private:
public:
	PlusOperator(const std::string& InitName, const std::vector<Node*>& InitPre);
	float Solve(std::string&ErrorSignal);
};

//  减法
class MinusOperator : public Node
{
private:
public:
	MinusOperator(const std::string& InitName, const std::vector<Node*>& InitPre);
	float Solve(std::string&ErrorSignal);
};

//  乘法
class MultipleOperator : public Node
{
private:
public:
	MultipleOperator(const std::string& InitName, const std::vector<Node*>& InitPre);
	float Solve(std::string&ErrorSignal);
};

//  除法
class DivisionOperator : public Node
{
private:
public:
	DivisionOperator(const std::string& InitName, const std::vector<Node*>& InitPre);
	float Solve(std::string&ErrorSignal);
};

// PRINT
class PrintOperator :public Node
{
private:
	std::ostream* OutStream;
public:
	PrintOperator(const std::string& InitName, const std::vector<Node*>& InitPre, std::ostream& InitOut);
	float Solve(std::string&ErrorSignal);
};

//  SIN
class SinOperator :public Node
{
private:
public:
	SinOperator(const std::string& InitName, const std::vector<Node*>& InitPre);
	float Solve(std::string& ErrorSignal);
};

//  EXP
class ExpOperator :public Node {
private:
public:
	ExpOperator(const std::string& InitName, const std::vector<Node*>& InitPre);
	float Solve(std::string& ErrorSignal);
};

//  LOG
class LogOperator :public Node {
private:
public:
	LogOperator(const std::string& InitName, const std::vector<Node*>& InitPre);
	float Solve(std::string& ErrorSignal);
};

//  TANH
class TanhOperator :public Node {
private:
public:
	TanhOperator(const std::string& InitName, const std::vector<Node*>& InitPre);
	float Solve(std::string& ErrorSignal);
};

//  SIGMOID
class SigmoidOperator :public Node {
private:
public:
	SigmoidOperator(const std::string& InitName, const std::vector<Node*>& InitPre);
	float Solve(std::string& ErrorSignal);
};

//  COND
class CondOperator :public Node {
private:
public:
	CondOperator(const std::string& InitName, const std::vector<Node*>& InitPre);
	float Solve(std::string& ErrorSignal);
};

//  >
class GreaterOperator :public Node {
private:
public:
	GreaterOperator(const std::string& InitName, const std::vector<Node*>& InitPre);
	float Solve(std::string& ErrorSignal);
};

//  >=
class GreaterEqualOperator :public Node {
private:
public:
	GreaterEqualOperator(const std::string& InitName, const std::vector<Node*>& InitPre);
	float Solve(std::string& ErrorSignal);
};

//  <
class LessOperator :public Node {
private:
public:
	LessOperator(const std::string& InitName, const std::vector<Node*>& InitPre);
	float Solve(std::string& ErrorSignal);
};

//  <=
class LessEqualOperator :public Node {
private:
public:
	LessEqualOperator(const std::string& InitName, const std::vector<Node*>& InitPre);
	float Solve(std::string& ErrorSignal);
};

//  ==
class EqualOperator :public Node {
private:
public:
	EqualOperator(const std::string& InitName, const std::vector<Node*>& InitPre);
	float Solve(std::string& ErrorSignal);
};

//————————————————————
//——————以下是第二阶段修改中添加的部分 

class AssertOperator :public Node {
private:
public:
	AssertOperator(const std::string& InitName, const std::vector<Node*>& InitPre);
	float Solve(std::string& ErrorSignal);
};

class BindOperator :public Node {
private:
public:
	BindOperator(const std::string& InitName, const std::vector<Node*>& InitPre);
	float Solve(std::string& ErrorSignal);
};


#endif

