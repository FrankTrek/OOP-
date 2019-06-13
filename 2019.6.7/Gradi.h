#pragma once#pragma once
#include "Node.h"
#include "Tensor.h"
//默认pre中顺序先走后右
//本张图不考虑任何有关Time的问题 ，于是一切涉及Time的位置都赋值为-1

//todo
//修改构造函数 带名构造&带前继节点
//完善ErrorSIgnal
//完善报错-Debug机制
class Gradi_Base :public Node<Tensor> {
protected:
	float step;//步长 实例中main
public:
	Gradi_Base(const std::vector<int>& a) :Node(a) {};//用shape赋值
	virtual Tensor SolveG(std::string& ErrorSignal) = 0;//单独开设的Solve 绕过Timetag机制 纯粹递推
	void SetTensor(const Tensor& a) {
		SetValue(a, -1);
	}
	void SetStep(float a) {
		step = a;
	}
	float getStep(float a) {
		return a;
	}
	virtual void Adjust() {
		Tensor a = GetValue() - step * GetGradi();
		SetValue(a, -1);
	}
	~Gradi_Base() = 0;

};
//to do
//构造函数 析构函数
//Solve
//Backword
class A :public Gradi_Base {
public:
	A(const std::vector<int>& a) :Gradi_Base(a) {};

	Tensor SolveG(std::string& ErrorSignal) override {
		return GetValue();
	}
	~A() {};
	void Backward(Tensor gradient, std::string& ErrorSignal) override {
		gradient.slim(0);//这个地方完全没看懂，根据示例cpp照抄
		SetGradi(gradient);
		return;
	}

};
class X :public Gradi_Base {
	X(const std::vector<int>& a) :Gradi_Base(a) {};
	Tensor SolveG(std::string& ErrorSignal) {
		return GetValue();
	}

};
class Temp :public Gradi_Base {
	Temp(const std::vector<int>& a) :Gradi_Base(a) {};
	Tensor SolveG(std::string& ErrorSignal) {
		return Pre[0]->GetValue() * Pre[1]->GetValue();
	}
	void Backward(Tensor gradient, std::string& ErrorSignal) override {
		SetGradi(gradient);
		Pre[0]->Backward(gradient * Derive_Mutiply_left(GetValue(), Pre[0]->GetValue(), Pre[1]->GetValue()), ErrorSignal);
		return;
	}
};
class b :public Gradi_Base {
	b(const std::vector<int>& a) :Gradi_Base(a) {};
	Tensor SolveG(std::string& ErrorSignal) {
		return GetValue();
	}
	void Backward(Tensor gradient, std::string& ErrorSignal) override {
		gradient.transposition();
		SetGradi(gradient);
		return;
	}
};
class Y :public Gradi_Base {
	Y(const std::vector<int>& a) :Gradi_Base(a) {};
	Tensor SolveG(std::string& ErrorSignal) {
		return Pre[0]->GetValue() + Pre[1]->GetValue();
	}
	void Backward(Tensor gradient, std::string& ErrorSignal) override {
		SetGradi(gradient);
		Pre[0]->Backward(GetGradi(), ErrorSignal);
		Pre[1]->Backward(GetGradi(), ErrorSignal);
		return;
	}
};
class Yg :public Gradi_Base {
	Yg(const std::vector<int>& a) :Gradi_Base(a) {};
	Tensor SolveG(std::string& ErrorSignal) {
		return Pre[0]->GetValue() * Pre[1]->GetValue();
	}
};
class Dis :public Gradi_Base {
	Dis(const std::vector<int>& a) :Gradi_Base(a) {};
	Tensor SolveG(std::string& ErrorSignal) {
		float k = Distance(Pre[1]->GetValue, Pre[0]->GetValue);
		Tensor tempk(k);
		SetValue(tempk, -1);
		return GetValue();
	}//注意这里distance 1、0顺序
	void Backward(Tensor gradient, std::string& ErrorSignal) override {
		SetGradi(gradient);
		Pre[0]->Backward(Derive_Distance(Pre[1]->GetValue, Pre[0]->GetValue), ErrorSignal);
		return;
	}

};//最后为了方便统一，这个点我仍然是继承了Gradi_Base让它作为Node的类型，存0维Tensor
