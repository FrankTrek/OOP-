#include "Newton.h"

Newton::Newton(int nn):n(nn){} ;

void Newton::Construct_Stage1(){
	Nodes1.push_back(new Constant("0|Nodes1",1.0f));
	Nodes1.push_back(new Placeholder("x")) ;
	x = Nodes1[1] ;
	if(n <= 1) return ;
	for(int i = 2; i <= n ; i++){
		std::vector<Node*>temp ;
		temp.push_back(Nodes1[1]) ;
		temp.push_back(Nodes1[i-1]) ;
		Nodes1.push_back(new MultipleOperator(std::to_string(i)+"Nodes1",temp)) ;
	}
} 

void Newton::Construct_Stage2(){
	for(int i = 0 ; i <= n ; i++ ){
		float temp ;
		std::cin >> temp ;
		Parameter.push_back(new Constant(std::to_string(n-i)+"Parameter",temp)) ;
	}
}

void Newton::Construct_Stage3(){
	for(int i = 0 ; i <= n ; i++ ){
		std::vector<Node*>temp ;
		temp.push_back(Parameter[n-i]) ;
		temp.push_back(Nodes1[i]) ;
		Nodes2.push_back(new MultipleOperator(std::to_string(i)+"Nodes2",temp)) ;
	}
	
}

void Newton::Construct_Stage4(){
	for(int i = 0 ; i <= n ; i++ ){
		if(i == 0 ){
			Nodes3.push_back(Nodes2[0]) ;
			continue ;
		}
		std::vector<Node*>temp ;
		temp.push_back(Nodes2[i]) ;
		temp.push_back(Nodes3[i-1]) ;
		Nodes3.push_back(new PlusOperator(std::to_string(i)+"Nodes3",temp)) ; 
	}
	res = Nodes3[n] ;
}

float Newton::Cal(){
	Construct_Stage1() ;
	Construct_Stage2() ;
	Construct_Stage3() ;
	Construct_Stage4() ;
	float temp ;
	std::cin>>temp ;
	Nodes1[1]->SetValue(temp,1) ;
	float result ;
	std::string E ;
	result = res->Calc(1,E) ;
	return result ;
	
}

/*
void Newton::NewtonMethond(){
	float Init ;
	std::cin>>Init ;
*/	



