//
//  BaseNode.h
//  OOP Computation Graph
//
//  Created by ��һŵ on 2019/4/4.
//  Copyright ? 2019 ��һŵ. All rights reserved.
//
//������־ lastest date 4.7
/*
 *4.7 ������initalise�Ľӿ�ע�Ͳ���BaseNode������ָ��
 *4.7 ���������ƺ�������Ϊ������Ա��֧�ֶ�̬
 *4.8 �����˷����Ƿ�Ϸ��ķ���
 *4.8 �����˽ڵ����ƣ��������˹��캯��
 *4.8 ���������ú����Ľӿ�
 *4.8 �������ṩ�ڵ���ֵ�Ľӿڣ�Ϊconst���ʹ��麯��
 *4.8 Z.������setflag�ӿ�
 *4.12 �����˼���Ƿ���������·�ķ���
 *4.12 ��Struct�е�ָ���Ϊshared_ptr
 *4.13 ���伫С��eps
 *4.17 ��Print()������Ϊר������ڵ����ĺ���
 */




//hhh
#ifndef BaseNode_h
#define BaseNode_h
#include <vector>
#include <string>
#include <iostream>
#include <memory>
namespace Computational_Graph
{
    //���е�Computatal Garph����ഢ����Computational_Graph���ƿռ���
    using std::string;
    using std::ostream;
    using std::istream;
    using std::cout;
    using std::endl;
    const float Minus_Max = -100000000000;//���ڸ���float�½����ж��Ƿ��������
    const float eps=1e-7;
    enum { Varible, Const, Operator ,Placehold};
    //д��֮ǰ�ľ���??��������֮��ļ̳����в������ǰ�򴫲��Ķ��壬����̳��ཫ��Ȼ��Ϊ����??????
    template <typename T>
    class BaseNode
    {
   
        
       
    protected:
        typedef std::vector<BaseNode*> NodeArray;  //��BaseNode���ƿռ���NodeArrayΪstd::vector<BaseNode*>�ı���
        bool flag;            //���������Ƿ�Ϸ��ı��
        NodeArray output_nodes;       //��¼��̽ڵ������
        NodeArray input_nodes;        //��¼ǰ�̽ڵ������
        string name;                  //��¼�ڵ�����
        
    public:
        BaseNode() { flag = true; }
        BaseNode(const string& a): name(a){flag = true;}
        virtual ~BaseNode() {}
        
        //����Ϊ�ṩ�Ľӿ�
        bool IsValid() const {return flag;}       //�����Ƿ�Ϸ��ķ���
        virtual void Reset_f() {
            cout<<"Reset_f funct has not been defined yet\n"; }  //�ṩ���³�ʼ���Ľӿڣ����㣩
        virtual void Reset_b() {
            cout<<"Reset_b funct has not been defined yet\n"; }  //�ṩ���³�ʼ���Ľӿڣ����㣩
        virtual void Reset(){
			cout<<"func: Reset has not been defined yet\n";	} 
        virtual void Reset(T& a) { cout<<"this funct has not been defined yet\n"; } //�ṩ���³�ʼ���Ľӿڣ���������
        virtual T Value() const =0;//��ʾvalue�Ľӿ�
        
        void Set_flag(bool i){
            flag = i ;
        }
        void Set_output_nodes( BaseNode* b)      //������̽ڵ㼯
        {
            output_nodes.push_back(b);
        }
        
        void Set_input_nodes( BaseNode* b)       //����ǰ�̽ڵ㼯
        {
            input_nodes.push_back(b);
        }
        virtual void Initalize(T& data)          //��������ڵ�ĳ�ʼ���ӿ�
        {
            cout<<"Func Initalize(T data) has not yet been defined\n";
        }
        virtual void SetConst(T& data)     //Variable�ڵ�Ĳ����ӿ�
        {
            cout<<"Func SetConst(T data) has not yet been defined\n";
        }
        virtual void SetAnswer(int n)     //Variable�ڵ�Ĳ����ӿ�
        {
            cout<<"Func SetAnswer(int n) has not yet been defined\n";
        }
        
        virtual T Forward () = 0;                                  //���򴫲�������Ľӿ�
        
        virtual void Backward()     //���򴫲��Ľӿ�
        {
            cout<<"Func Backward()  has not yet been defined\n";
        }
        virtual void Print()          //��ӡ��Ϣ�Ľӿ� 4.17 ��Ϊר�Ŵ�ӡ�ڵ���
        {
            cout<<name;
        }
        //����4.12 ����Ƿ���������·  true for ��
        bool IsCycle(const string& a)
        {
            for(auto x : input_nodes)
            {
                if(x->name == a)
                {
                    std::cerr<<"Loop Error\n";
                    return true;
                }
                x->IsCycle(a);
            }
            return false;
        }
       virtual string returntype() {
			return "func: returntype has not been defined yet\n";
	}  
	
		//debugʱʹ�õĺ��� 
               
        // ����Ϊ����һЩĬ�ϵĸ�ʽת��
        BaseNode (const BaseNode& A) = delete;
        BaseNode (BaseNode&& A) =delete ;
        BaseNode& operator = (const BaseNode& A) = delete;
        BaseNode& operator = (BaseNode&& A) = delete;
    };
    
    /* �������ʵ�ֵĹ��ܣ�
     *��ʽΪģ������
     *���ܱ�����Ա����ʽ�ṩ���ж��Ƿ�����Ϸ�������
     *���ܱ�����Ա����ʽ�ṩ��ǰ�̽ڵ㼯�ͺ�̽ڵ㼯
     *�ṩ��ǰ�򴫲�����Ҫ�ӿ�
     *Ϊ���򴫲�Ԥ���˽��
     *�ر��˸��ָ����Լ�����ת��
     *����ڵ�ĳ�ʼ���ӿ�
     
     
     
     *����Operator���в���������͵��������
     *����Variable��Const���в���������ֵ��Ϣ�Լ���ֵ����
     */
    template <typename T>
    struct Graph_Node{
        std::shared_ptr<BaseNode<T> > node;              //ָ�����ڵ��ָ��
        string Nodename;                 //�ڵ������
        int Mode;                        //�ڵ������
    };                                   //����ͼ�еĽڵ�
}

#endif /* BaseNode_h */
