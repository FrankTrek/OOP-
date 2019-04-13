//OOP Computational_graph

//更新日志 latest date 4.7
//4.7我觉得Node中In 和 forward 都可以直接挂final?
//感觉用不到移动&拷贝，或许可以delete? 
//C V 构造时必带数值，P构造时禁止带值 


#pragma once
#include <iostream> 
#include "Node.h"


namespace Computational_Graph{


  class Constant : public Node<float> {
    
    public :
    
    	using Node<float>::Forward ;
    	//不允许除去构造时的初始化 
    
    	Const() = delete ;
		Constant(float i):Node(i){
			this->flag_IsValid = 1 ;
		} ;
		//构造：只允许带参数构造，此时无论如何都合法 
		~Constant(){} ;
		//setanswer依赖输出 
		 
	}; 
    
    
    class Variable : public Node<float> {
    
    public :

    	using Node<float>::Forward ;
    	using Node<float>::Initalize ;
    	
		Varaible() = delete ;
		Variable(float i):Node(i){
			this->flag_IsValid = 1 ;
		} ;
		//setanswer依赖输出 
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
