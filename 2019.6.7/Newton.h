#pragma once
#include "Operator.h"
#include "Scalar.h" 
#include <vector>
#include <iostream>
//todo
//设置ErrorSignal兼容报错 
class Newton{
	int n ;
	std::vector<Node*> Nodes1 ;
	std::vector<Node*> Parameter ;
	std::vector<Node*> Nodes2 ;
	std::vector<Node*> Nodes3 ;
	Node* res ;
	Node* x ;
public :
	//搭建1-n次方节点
	Newton(int nn) ;
	void Construct_Stage1() ;
	void Construct_Stage2() ;
	void Construct_Stage3() ;
	void Construct_Stage4() ;
	
	float Cal() ;
	
//	void NewtonMethod() ;
	
};
