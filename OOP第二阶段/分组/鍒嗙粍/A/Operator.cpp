#include "Operator.h"
#include <iomanip>
#include <cmath>

PlusOperator::PlusOperator(const std::string& InitName, const std::vector<Node*>& InitPre) : Node(InitName, 0, 0)
{
	Pre = InitPre;
}
float PlusOperator::Solve(std::string&ErrorSignal)
{
	if (ErrorSignal.size() != 0)	return 0;						//	若该结点计算过程中出现错误信息，则终止计算过程; 下同
	float Tempa = Pre[0]->Calc(this->GetTime(), ErrorSignal);
	if (ErrorSignal.size() != 0)	return 0;
	float Tempb = Pre[1]->Calc(this->GetTime(), ErrorSignal);
	if (ErrorSignal.size() != 0)	return 0;
	return Tempa + Tempb;
}

MinusOperator::MinusOperator(const std::string& InitName, const std::vector<Node*>& InitPre) : Node(InitName, 0, 0)
{
	Pre = InitPre;
}
float MinusOperator::Solve(std::string& ErrorSignal)
{
	if (ErrorSignal.size() != 0)return 0;
	float Tempa = Pre[0]->Calc(this->GetTime(), ErrorSignal);
	if (ErrorSignal.size() != 0)return 0;
	float Tempb = Pre[1]->Calc(this->GetTime(), ErrorSignal);
	if (ErrorSignal.size() != 0)return 0;
	return Tempa - Tempb;
}

MultipleOperator::MultipleOperator(const std::string& InitName, const std::vector<Node*>& InitPre) : Node(InitName, 0, 0)
{
	Pre = InitPre;
}
float MultipleOperator::Solve(std::string&ErrorSignal)
{
	if (ErrorSignal.size() != 0)return 0;
	float Tempa = Pre[0]->Calc(this->GetTime(), ErrorSignal);
	if (ErrorSignal.size() != 0)return 0;
	float Tempb = Pre[1]->Calc(this->GetTime(), ErrorSignal);
	if (ErrorSignal.size() != 0)return 0;
	return Tempa * Tempb;
}

DivisionOperator::DivisionOperator(const std::string& InitName, const std::vector<Node*>& InitPre) : Node(InitName, 0, 0)
{
	Pre = InitPre;
}
float DivisionOperator::Solve(std::string&ErrorSignal)
{
	if (ErrorSignal.size() != 0)	return 0;
	float Tempa = Pre[0]->Calc(this->GetTime(), ErrorSignal);
	if (ErrorSignal.size() != 0)	return 0;
	float Tempb = Pre[1]->Calc(this->GetTime(), ErrorSignal);
	if (ErrorSignal.size() != 0)	return 0;
	if (std::fabs(Tempb) < Epsi)			//	考虑浮点运算的误差
	{
		ErrorSignal = "Division by zero";
		return 0;
	}
	return Tempa / Tempb;
}

PrintOperator::PrintOperator(const std::string& InitName, const std::vector<Node*>& InitPre, std::ostream& InitOut) : Node(InitName, 0, 0)
{
	Pre = InitPre;
	OutStream = &InitOut;
}
float PrintOperator::Solve(std::string& ErrorSignal)
{
	if (ErrorSignal.size() != 0)  return 0;
	float Tempa = Pre[0]->Calc(this->GetTime(), ErrorSignal);
	if (ErrorSignal.size() != 0)	 return 0;
	(*OutStream).setf(std::ios::fixed);
	(*OutStream) << std::setprecision(4) << "PRINT operator: " << Pre[0]->GetName() << " = " << Tempa << std::endl;
	return Tempa;
}

SinOperator::SinOperator(const std::string& InitName, const std::vector<Node*>& InitPre) :Node(InitName, 0, 0)
{
	Pre = InitPre;
}
float SinOperator::Solve(std::string& ErrorSignal)
{
	if (ErrorSignal.size() != 0)  return 0;
	float Temp = Pre[0]->Calc(this->GetTime(), ErrorSignal);
	if (ErrorSignal.size() != 0)  return 0;
	return  std::sin(Temp);
}

ExpOperator::ExpOperator(const std::string& InitName, const std::vector<Node*>& InitPre) : Node(InitName, 0, 0)
{
	Pre = InitPre;
}
float ExpOperator::Solve(std::string& ErrorSignal)
{
	if (ErrorSignal.size() != 0)  return 0;
	float Temp = Pre[0]->Calc(this->GetTime(), ErrorSignal);
	if (ErrorSignal.size() != 0)  return 0;
	return std::exp(Temp);
}

LogOperator::LogOperator(const std::string & InitName, const std::vector<Node*>& InitPre) :Node(InitName, 0, 0)
{
	Pre = InitPre;
}
float LogOperator::Solve(std::string& ErrorSignal)
{
	if (ErrorSignal.size() != 0)  return 0;
	float Temp = Pre[0]->Calc(this->GetTime(), ErrorSignal);
	if (ErrorSignal.size() != 0)  return 0;
	if (Temp <= 0 || std::fabs(Temp) < Epsi)	//	考虑浮点运算的误差
	{
		ErrorSignal = "LOG operator's input must be positive";
		return 0;
	}
	return std::log(Temp);
}

TanhOperator::TanhOperator(const std::string& InitName, const std::vector<Node*>& InitPre) : Node(InitName, 0, 0)
{
	Pre = InitPre;
}
float TanhOperator::Solve(std::string& ErrorSignal)
{
	if (ErrorSignal.size() != 0)  return 0;
	float Temp = Pre[0]->Calc(this->GetTime(), ErrorSignal);
	if (ErrorSignal.size() != 0)  return 0;
	float tmpa = std::exp(2.0 * Temp);
	float tmpb = (tmpa - 1.0) / (tmpa + 1.0);
	return tmpb;
}

SigmoidOperator::SigmoidOperator(const std::string& InitName, const std::vector<Node*>& InitPre) : Node(InitName, 0, 0)
{
	Pre = InitPre;
}
float SigmoidOperator::Solve(std::string& ErrorSignal)
{
	if (ErrorSignal.size() != 0)  return 0;
	float Temp = Pre[0]->Calc(this->GetTime(), ErrorSignal);
	if (ErrorSignal.size() != 0)  return 0;
	float tmpa = std::exp(-Temp);
	float tmpb = 1.0 / (1.0 + tmpa);
	return tmpb;
}

CondOperator::CondOperator(const std::string& InitName, const std::vector<Node*>& InitPre) : Node(InitName, 0, 0)
{
	Pre = InitPre;
}
float CondOperator::Solve(std::string& ErrorSignal)
{
	if (ErrorSignal.size() != 0)  return 0;
	float tmp = Pre[0]->Calc(this->GetTime(), ErrorSignal);
	if (ErrorSignal.size() != 0)  return 0;
	float tmpa = Pre[1]->Calc(this->GetTime(), ErrorSignal);		//	COND实现：先计算后两个结点的值再条件判断，保证二者均可求值
	if (ErrorSignal.size() != 0)  return 0;
	float tmpb = Pre[2]->Calc(this->GetTime(), ErrorSignal);		//	同上
	if (ErrorSignal.size() != 0)  return 0;
	if (tmp > 0) {
		return tmpa;
	}
	else {
		return tmpb;
	}
}

GreaterOperator::GreaterOperator(const std::string & InitName, const std::vector<Node*>& InitPre) : Node(InitName, 0, 0)
{
	Pre = InitPre;
}
float GreaterOperator::Solve(std::string& ErrorSignal) {
	if (ErrorSignal.size() != 0)  return 0;
	float Tempa = Pre[0]->Calc(this->GetTime(), ErrorSignal);
	if (ErrorSignal.size() != 0)  return 0;
	float Tempb = Pre[1]->Calc(this->GetTime(), ErrorSignal);
	if (ErrorSignal.size() != 0)  return 0;
	return Tempa > Tempb;
}

GreaterEqualOperator::GreaterEqualOperator(const std::string & InitName, const std::vector<Node*>& InitPre) : Node(InitName, 0, 0)
{
	Pre = InitPre;
}
float GreaterEqualOperator::Solve(std::string & ErrorSignal)
{
	if (ErrorSignal.size() != 0)  return 0;
	float Tempa = Pre[0]->Calc(this->GetTime(), ErrorSignal);
	if (ErrorSignal.size() != 0)  return 0;
	float Tempb = Pre[1]->Calc(this->GetTime(), ErrorSignal);
	if (ErrorSignal.size() != 0)  return 0;
	return Tempa >= Tempb;
}

LessOperator::LessOperator(const std::string & InitName, const std::vector<Node*>& InitPre) : Node(InitName, 0, 0)
{
	Pre = InitPre;
}
float LessOperator::Solve(std::string & ErrorSignal)
{
	if (ErrorSignal.size() != 0)  return 0;
	float Tempa = Pre[0]->Calc(this->GetTime(), ErrorSignal);
	if (ErrorSignal.size() != 0)  return 0;
	float Tempb = Pre[1]->Calc(this->GetTime(), ErrorSignal);
	if (ErrorSignal.size() != 0)  return 0;
	return Tempa < Tempb;
}

LessEqualOperator::LessEqualOperator(const std::string & InitName, const std::vector<Node*>& InitPre) : Node(InitName, 0, 0)
{
	Pre = InitPre;
}
float LessEqualOperator::Solve(std::string & ErrorSignal)
{
	if (ErrorSignal.size() != 0)  return 0;
	float Tempa = Pre[0]->Calc(this->GetTime(), ErrorSignal);
	if (ErrorSignal.size() != 0)  return 0;
	float Tempb = Pre[1]->Calc(this->GetTime(), ErrorSignal);
	if (ErrorSignal.size() != 0)  return 0;
	return Tempa <= Tempb;
}

EqualOperator::EqualOperator(const std::string & InitName, const std::vector<Node*>& InitPre) : Node(InitName, 0, 0)
{
	Pre = InitPre;
}

float EqualOperator::Solve(std::string & ErrorSignal)
{
	if (ErrorSignal.size() != 0)  return 0;
	float Tempa = Pre[0]->Calc(this->GetTime(), ErrorSignal);
	if (ErrorSignal.size() != 0)  return 0;
	float Tempb = Pre[1]->Calc(this->GetTime(), ErrorSignal);
	if (ErrorSignal.size() != 0)  return 0;
	return Tempa == Tempb;
}
