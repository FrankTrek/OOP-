#include "Operator.h"
#include <iomanip>
#include <cmath>

PlusOperator::PlusOperator(const std::string& InitName, const std::vector<Node*>& InitPre) : Node(InitName, 0, 0)
{
	Pre = InitPre;
}
float PlusOperator::Solve(std::string&ErrorSignal)
{
    
	if (ErrorSignal.size() != 0)	return 0;						//	»Ù∏√Ω·µ„º∆À„π˝≥Ã÷–≥ˆœ÷¥ÌŒÛ–≈œ¢£¨‘Ú÷’÷πº∆À„π˝≥Ã; œ¬Õ¨
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
	if (std::fabs(Tempb) < Epsi)			//	øº¬«∏°µ„‘ÀÀ„µƒŒÛ≤Ó
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
    SetGradi(0);
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
	if (Temp <= 0 || std::fabs(Temp) < Epsi)	//	øº¬«∏°µ„‘ÀÀ„µƒŒÛ≤Ó
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
	float tmpa = Pre[1]->Calc(this->GetTime(), ErrorSignal);		//	COND µœ÷£∫œ»º∆À„∫Û¡Ω∏ˆΩ·µ„µƒ÷µ‘ŸÃıº˛≈–∂œ£¨±£÷§∂˛’ﬂæ˘ø…«Û÷µ
	if (ErrorSignal.size() != 0)  return 0;
	float tmpb = Pre[2]->Calc(this->GetTime(), ErrorSignal);		//	Õ¨…œ
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

//第二阶段更新

AssertOperator::AssertOperator(const std::string& InitName, const std::vector<Node*>& InitPre) : Node(InitName, 0, 0)
{
    Pre = InitPre;
}
float AssertOperator::Solve(std::string& ErrorSignal)
{
    if (ErrorSignal.size() != 0)  return 0;
    float Temp = Pre[0]->Calc(this->GetTime(), ErrorSignal);
    if (ErrorSignal.size() != 0)  return 0;
    if (Temp <= Epsi)    //    考虑浮点运算的误差
    {
        ErrorSignal = "Assertion failed";
        return 0;
    }
    return 0;
}



BindOperator::BindOperator(const std::string& InitName, const std::vector<Node*>& InitPre) : Node(InitName, 0, 0)
{
    Pre = InitPre;
}
float BindOperator::Solve(std::string&ErrorSignal)
{
    if (ErrorSignal.size() != 0)return 0;
    float Tempa = Pre[0]->Calc(this->GetTime(), ErrorSignal);
    if (ErrorSignal.size() != 0)return 0;
    float Tempb = Pre[1]->Calc(this->GetTime(), ErrorSignal);
    if (ErrorSignal.size() != 0)return 0;
    return Tempa;
}


GradOperator::GradOperator(const std::string & InitName, const std::vector<Node*>& InitPre) : Node(InitName,0,0)
{
    Pre = InitPre;
}
float GradOperator::Solve(std::string & ErrorSignal)
{
    if (ErrorSignal.size() != 0)  return 0;
    Pre[0]->Calc(this->GetTime(), ErrorSignal);
    if (ErrorSignal.size() != 0)  return 0;
    Pre[0]->Backward(1,ErrorSignal);
    return 0;
}

AtOperator::AtOperator(const std::string & InitName, const std::vector<Node*>& InitPre) : Node(InitName,0,0)
{
    Pre = InitPre;
}
float AtOperator::Solve(std::string &ErrorSignal)
{
    if (ErrorSignal.size() != 0)  return 0;
    Pre[0]->Calc(this->GetTime(), ErrorSignal);
    if (ErrorSignal.size() != 0)  return 0;
    return Pre[1]->GetGradi();
}

void PlusOperator::Backward(float gradient,std::string&ErrorSignal)
{
    SetGradi(GetGradi()+gradient);
    Pre[0]->Backward(gradient,ErrorSignal);
    if (ErrorSignal.size() != 0) return;
    Pre[1]->Backward(gradient,ErrorSignal);
    
}
void MinusOperator::Backward(float gradient,std::string&ErrorSignal)
{
    SetGradi(GetGradi()+gradient);
    Pre[0]->Backward(gradient,ErrorSignal);
    if (ErrorSignal.size() != 0) return;
    Pre[1]->Backward(-gradient,ErrorSignal);
    
}
void MultipleOperator::Backward(float gradient,std::string&ErrorSignal)
{
    SetGradi(GetGradi()+gradient);
    Pre[0]->Backward(gradient*Pre[1]->GetValue(),ErrorSignal);
    if (ErrorSignal.size() != 0) return;
    Pre[1]->Backward(gradient*Pre[0]->GetValue(),ErrorSignal);
    
}
void DivisionOperator::Backward(float gradient, std::string &ErrorSignal)
{
    SetGradi(GetGradi()+gradient);
    Pre[0]->Backward(gradient/Pre[1]->GetValue(),ErrorSignal);
    if (ErrorSignal.size() != 0) return;
    Pre[1]->Backward(-gradient*Pre[0]->GetValue()/(Pre[1]->GetValue()*Pre[1]->GetValue()),ErrorSignal);
    
}
void SinOperator::Backward(float gradient, std::string &ErrorSignal)
{
    SetGradi(GetGradi()+gradient);
    Pre[0]->Backward(cos(GetValue()), ErrorSignal);
}
void LogOperator::Backward(float gradient, std::string &ErrorSignal)
{
    SetGradi(GetGradi()+gradient);
    Pre[0]->Backward(gradient/(GetValue()), ErrorSignal);
}
void TanhOperator::Backward(float gradient, std::string &ErrorSignal)
{
    float value = GetValue();
    SetGradi(GetGradi()+gradient);
    Pre[0]->Backward(gradient*(1-value*value), ErrorSignal);
}
void SigmoidOperator::Backward(float gradient, std::string &ErrorSignal)
{
    float a = GetValue();
    SetGradi(GetGradi()+gradient);
    Pre[0]->Backward(gradient*(exp(-a))/((1+exp(-a))*(1+exp(-a))), ErrorSignal);
}
void ExpOperator::Backward(float gradient, std::string &ErrorSignal)
{
    SetGradi(GetGradi()+gradient);
    Pre[0]->Backward(exp(GetValue()), ErrorSignal);
}
void LessOperator:: Backward(float, std::string &ErrorSignal)
{
    ErrorSignal= "Not defined Grad for LessOperator yet!";
}
void GreaterOperator:: Backward(float, std::string &ErrorSignal)
{
    ErrorSignal= "Not defined Grad for GreaterOperator yet!";
}
void CondOperator:: Backward(float , std::string & ErrorSignal)
{
    ErrorSignal= "Not defined Grad for CondOperator yet!";
}
void GreaterEqualOperator:: Backward(float , std::string &ErrorSignal)
{
    ErrorSignal= "Not defined Grad for GreaterEqualOperator yet!";
}
void LessEqualOperator:: Backward(float , std::string &ErrorSignal)
{
    ErrorSignal= "Not defined Grad for LessEqualOperator yet!";
}
void EqualOperator:: Backward(float, std::string &ErrorSignal)
{
    ErrorSignal= "Not defined Grad for EqualOperator yet!";
}
void GradOperator:: Backward(float, std::string &ErrorSignal)
{
    ErrorSignal= "Not defined Grad for GradOperator yet!";
}
void AtOperator:: Backward(float, std::string &ErrorSignal)
{
    ErrorSignal= "Not defined Grad for AtOperator yet!";
}
void PrintOperator:: Backward(float, std::string &ErrorSignal)
{
    ErrorSignal= "Not defined Grad for PrintOperator yet!";
}

void AssertOperator:: Backward(float, std::string &ErrorSignal)
{
    ErrorSignal= "Not defined Grad for AssertOperator yet!";
}
void BindOperator:: Backward(float, std::string &ErrorSignal)
{
    ErrorSignal= "Not defined Grad for BindOperator yet!";
}

