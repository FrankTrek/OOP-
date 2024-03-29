
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
        void Backward(float gradient) override
        {
            gradi = 0;
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
        void Backward(float gradient) override
        {
            gradi = 0;
        }
        
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
        void Backward(float gradient) override
        {
            gradi += gradient;
        }
        ~Placeholder(){} ;
        
        
    };
}
