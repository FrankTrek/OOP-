#ifndef NODE_H
#define NODE_H

#include<vector>
#include<string>
#include "Tensor.h"

const float Epsi = 1e-7;

template <typename T>
class Node {
private:
	int Time;
	std::string Name;
	T Value;
    //add by Cai on 6.6
    T gradi=0;
    //
protected:
	std::vector<Node*> Pre;		//Pre: 计算某结点的Value依赖的前序结点
public:
    Node(){
        Name = "";
        Value = 0;
        Time = 0;
        Pre.clear();
    }
	Node(const std::string& InitName, const T& InitValue, const int& InitTime)
    {
        Name = InitName;
        Value = InitValue;
        Time = InitTime;
        Pre.clear();

    }
	Node(const std::vector<int>& a) {
		std::cout << "Tensor Only" << std::endl;
	}

	T Calc(const int& CurTime, std::string& ErrorSignal)
    {
        SetGradi(0);
        if (Time == CurTime)                    //    若结点对应的时间等于当前时间，可以直接返回Value;
        {
            return Value;
        }
        
        Time = CurTime;
        Value = this->Solve(ErrorSignal);        //    否则，重新计算
        return Value;
    }//	计算某一结点的值
    void SetValue(const T& Input, const int& CurTime){
        Value = Input;
        Time = CurTime;
    }						//	为结点赋值
    std::string GetName(){
        return Name;
    }														//	获得结点名
    T GetValue(){
        return Value;
    }																//	获得结点值
    //
    T GetGradi (){
        return gradi;
    }
    void SetGradi (T G){
        gradi= G;
    }
    //
    
    int GetTime(){
        return Time;
    }																	//	获得结点的时间标记
	virtual T Solve(std::string&ErrorSignal) = 0;									//	纯虚函数，便于派生类中重写覆盖: 进行不同种类运算符的计算
    
    //add by Cai on 6.6
    virtual void Backward(T ,std::string&ErrorSignal) = 0;
    //
    virtual ~Node() {}															//	纯虚析构函数
};

template<>
Node<Tensor>::Node(const std::vector<int>& a) {
	Tensor k(a,0);
	Value = k;//在递降中使用全部为0
}

#endif
