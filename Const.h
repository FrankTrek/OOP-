//OOP Computational_graph

//������־ latest date 4.7
//4.7�Ҿ���Node��In �� forward ������ֱ�ӹ�final?
//�о��ò����ƶ�&�������������delete? 
//C V ����ʱ�ش���ֵ��P����ʱ��ֹ��ֵ 


#pragma once
#include <iostream> 
#include "Node.h"


namespace Computational_Graph{


  class Constant : public Node<float> {
    
    public :
    
    	using Node<float>::Forward ;
    	//�������ȥ����ʱ�ĳ�ʼ�� 
    
    	Const() = delete ;
		Constant(float i):Node(i){
			this->flag_IsValid = 1 ;
		} ;
		//���죺ֻ������������죬��ʱ������ζ��Ϸ� 
		~Constant(){} ;
		//setanswer������� 
		 
	}; 
    
    
    class Variable : public Node<float> {
    
    public :

    	using Node<float>::Forward ;
    	using Node<float>::Initalize ;
    	
		Varaible() = delete ;
		Variable(float i):Node(i){
			this->flag_IsValid = 1 ;
		} ;
		//setanswer������� 
		~Variable() ;
		 
	}; 
    
    class Placeholder : public Node<float>{
    	
    public :
    	using Node<float>::Forward ;
		using Node<float>::Initalize ;
		
		Placeholder(){} ; 
		Placeholder(float) = delete ;
		~Placeholder(){} ;
		
		 
	};
}
