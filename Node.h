//
//  Node.h
//  OOP Computation Graph
//
//  Created by ��һŵ on 2019/4/5.
//  Copyright ? 2019 ��һŵ. All rights reserved.
//

//������־ latest date 4.7
/*
 *4.7  ��Node.h�е�ö���������Trinary��
 *4.7  ��Node.h�е�Node�ಹ���ṩ�����Ĺ��캯��
 *4.8  ��Node.h��vlaueת����������Ա
 *4.8  �����˲鿴��ֵ�ķ���
 *4.8  Z.������Reset�������к���flag����Ϊ0 valueΪ-Max�Ľӿ�
 *4.8  Z.������ֻ��string��ʼ��Node�Ľӿ�
 * 4.10 Z.������forward�ı�����Ϣ�Ͷ�flag������
 * 4.10 Z.�޸���ֻ��string��ʼ��Node,ʹplaceholder��ʼ��Ϊ-max
 * 4.10 Z.Attention:�޸�RESET
 * 4.12 ��operation��Ĺ��캯���ɴ����ø�Ϊ��ָ��
 * 4.13 ��������Ԫ������Ĺ��캯��
 * 4.20 Z.�޸���Error�ı�����Ϣ 
 * 4.20 Z.������Node���е�type���� ����type 
 */
#ifndef Node_h
#define Node_h
#include "BaseNode.h"
#include <vector>
#include <sstream>
using std::vector ; 

namespace Computational_Graph{
    enum{Nullary, Unary, Binary, Trinary};                               //���ڱ�Ǽ�����Ĳ�������
    
    template <typename T>
    class Node : public BaseNode<T>
    {
        
    protected:
        T value;    //�ڵ��ֵ
        T gradi;    //�ڵ�ĵ���
      
    public:
        Node() = default;
        Node(const T& a): value(a) {}                                      //������ֵ��ʼ���Ĺ��캯��
        Node(const T& a, const string& b):BaseNode<T>(b), value(a) {}
        Node(const string& b):BaseNode<T>(b){
            value = Minus_Max ;
        } ;
        virtual void Initalize(T& data) override
        {
            value = data;
        }
        virtual T Forward () override                                       //���򴫲�����Ԫ����Ľӿ�
        {
            if(value == Minus_Max) {
                std::cerr << "Error: an unavailable or ungiven value for Node\n";
                this->flag = 0 ;
            }
            return value;
        }
        virtual T Value () const override                                       //���ؽڵ���ֵ
        {
            return value;
        }
        //�����ú���
        void debug_print(){
            std::cerr << this->value << "|" << this->flag << endl ;
        }
        //
        void Reset() override final{
        	this->flag = 1;
        	this->value = Minus_Max ;
		}
        
        void Reset_f() override final{
            this->Reset() ;
            for(auto i: this->output_nodes){
                i->Reset_f() ;
            }
        }
        void Reset_b() override final{
        	if(this->returntype() == "Constant" || this->returntype() == "Variable"){
        		return ;
			}
			this->Reset();
			for(auto i: this->input_nodes){
				i->Reset_b() ;
			}
		}  

        
        ~Node(){}
        
    };
    template <typename T>
    class Operation : public BaseNode<T>
    {
        
    protected:
        T value;    //�ڵ��ֵ
        T gradi;    //�ڵ�ĵ���
        int type;
    public:
        using BaseNode<T>::Set_input_nodes;
        Operation() { type = Nullary; }       //0Ԫ�����
        Operation (BaseNode<T>* node1)        //1Ԫ�����
        {
            node1->Set_output_nodes(this);
            Set_input_nodes(node1);
            type = Unary;
            value = Minus_Max;
        }
        Operation (BaseNode<T>* node1,BaseNode<T>* node2) //2Ԫ�����
        {
            node1->Set_output_nodes(this);
            node2->Set_output_nodes(this);
            Set_input_nodes(node1);
            Set_input_nodes(node2);
            type = Binary;
            value = Minus_Max;
        }
            //���ﲹ����Ԫ�����
        Operation (BaseNode<T>* node1, BaseNode<T>* node2, BaseNode<T>* node3)// ��Ԫ�����
        {
            node1->Set_output_nodes(this);
            node2->Set_output_nodes(this);
            node3->Set_output_nodes(this);
            Set_input_nodes(node1);
            Set_input_nodes(node2);
            Set_input_nodes(node3);
            type = Trinary;
            value = Minus_Max;
        }
            //����
            
        string returntype() override final{
			return "Operation" ;
		}
		
	    void Reset() override final{
      	this->flag = 1;
       	this->value = Minus_Max ;
		}
            
        void Reset_f() override final{
            this->Reset() ; 
            for(auto i: this->output_nodes){
                i->Reset_f() ;
            }
        }
        void Reset_b() override final{
        	if(this->returntype() == "Constant" || this->returntype() == "Variable"){
        		return ;
			}
			this->Reset();
			for(auto i: this->input_nodes){
				i->Reset_b() ;
			}
		}
        
        //����Ϊ�����汾
        //����Ϊ�����Ƶİ汾
        Operation(const string& a):BaseNode<T>(a) { type = Nullary; }       //0Ԫ�����
        Operation (const string& a,BaseNode<T>* node1):BaseNode<T>(a)        //1Ԫ�����
        {
            node1->Set_output_nodes(this);
            Set_input_nodes(node1);
            type = Unary;
            value = Minus_Max;
        }
        Operation (const string& a,BaseNode<T>* node1,BaseNode<T>* node2):BaseNode<T>(a) //2Ԫ�����
        {
            node1->Set_output_nodes(this);
            node2->Set_output_nodes(this);
            Set_input_nodes(node1);
            Set_input_nodes(node2);//������Ҫ�Ķ�
            type = Binary;
            value = Minus_Max;
        }
        
        Operation (const string& a,BaseNode<T>* node1,BaseNode<T>* node2,BaseNode<T>* node3):BaseNode<T>(a) //2Ԫ�����
        {
            node1->Set_output_nodes(this);
            node2->Set_output_nodes(this);
            node3->Set_output_nodes(this);
            Set_input_nodes(node1);
            Set_input_nodes(node2);
            Set_input_nodes(node3);
            type = Trinary;
            value = Minus_Max;
        }
        virtual T Value () const override                                       //���ؽڵ���ֵ
        {
            return value;
        }
        //
        void debug_print(){
            std::cerr << this->value << "|" << this->flag << endl ;
        }
        
        //
    };
}


#endif /* Node_h */

