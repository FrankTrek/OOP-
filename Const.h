
//  Const.h
//  OOP Computation Graph
//
//  Created by 王一诺 on 2019/4/13.
//  Copyright ? 2019 王一诺. All rights reserved.
//
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
        }//创建一个名字name
        string returntype() override{
            return "Placeholder" ;
        }
        ~Placeholder(){} ;
        
        
    };
}
