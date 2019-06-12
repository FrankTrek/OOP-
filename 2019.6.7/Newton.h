#ifndef NEWTON_H
#define NEWTON_H
#include "Operator.h"
#include "Scalar.h" 
#include "Node.h"
#include <vector>
#include <iostream>
//todo
//设置ErrorSignal兼容报错 
class Newton{
	int n ;
	int Timetag ;
	float eps = 1.0e-7;//这样可？
	std::string ErrorSignal;
	std::vector<Node<float>*> Nodes1 ;
	std::vector<Node<float>*> Parameter ;
	std::vector<Node<float>*> Nodes2 ;
	std::vector<Node<float>*> Nodes3 ;
	Node<float>* res ;
	Node<float>* x ;
public :
	//搭建1-n次方节点
	Newton(int nn) ;
	void Construct_Stage1() ;
	void Construct_Stage2() ;
	void Construct_Stage3() ;
	void Construct_Stage4() ;
	void Method();
	void Delete();
	float debug_Cal() ;
	~Newton();
//	void NewtonMethod() ;
	
};
#endif
