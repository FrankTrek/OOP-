//
//  Const.h
//  OOP Computation Graph
//
//  Created by ��һŵ on 2019/4/13.
//  Copyright ? 2019 ��һŵ. All rights reserved.
//
//OOP Computational_graph

//������־ lastest date 4.8
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
        
        Constant() = delete;
        Constant(const float& i) = delete;
        
        Constant(const float& i ,const string& s):Node<float>(i,s){
        } ;
        string returntype() override{
        	return "Constant" ;
		} 
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
        string returntype() override{
        	return "Variable" ;
		} 
        //setanswer�����������������
        ~Variable(){} ;
        
    };
    
    class Placeholder : public Node<float>{
        
        public :
        using Node<float>::Forward ;
        using Node<float>::Initalize ;
        
        Placeholder(){} ;
        Placeholder(const float& a) = delete ;
        Placeholder(const string& s):Node<float>(s){
        }//����һ������name 
        string returntype() override{
        	return "Placeholder" ;
		} 
        ~Placeholder(){} ;
        
        
    };
}

