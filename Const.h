//OOP Computational_graph

//更新日志 lastest date 4.8
/* 
 4.8
*/
#pragma once
#include <iostream> 
#include "Node.h"


namespace Computational_Graph{


  class Constant : public Node<float> {
    
    public :
    
    	using Node<float>::Forward ;
    
    	Const() = delete ;
    	Const(const float& i) = delete ;

		Constant(const float& i ,const string& s):Node<float>(i,s){
		} ;

		~Constant(){} ;
	}; 
    
    
    class Variable : public Node<float> {
    
    public :

    	using Node<float>::Forward ;
    	using Node<float>::Initalize ;
    	
		Variable() = delete ;
		Variable(const float& i) = delete ;
		Variable(const float& i ,const string& s):Node<float>(i,s){
		} ;
		//setanswer依靠于输出，待补充
		~Variable(){} ;
		 
	}; 
    
    class Placeholder : public Node<float>{
    	
    public :
    	using Node<float>::Forward ;
		using Node<float>::Initalize ;

		Placeholder(){} ;
		Placeholder(const float& a) = delete ;
		Placeholder(const string& s):Node<float>(s){
		} 
		~Placeholder(){} ;
		
		 
	};
}

