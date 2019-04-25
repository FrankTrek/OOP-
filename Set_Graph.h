//
//  Set_Graph.h
//  OOP Computation Graph
//
//  Created by ��һŵ on 2019/4/12.
//  Copyright ? 2019 ��һŵ. All rights reserved.
//

/*
 *4.13���伫С��eps
 *4.20 Z.I.PVC()ʵ�� 
 *4.20 Z.processing Stage3 ����Reset
 *4.20 ���� ���սڵ�res �ļ�¼ 
 *4.20 Z.40����һ������û�׵Ŀ���Σ�ղ��� 
 *4.23 �޸�Compute ʹ�������ĵ㲻��� 
 */


#ifndef Set_Graph_h
#define Set_Graph_h
#include "Node.h"
#include <map>
#include "Const.h"
#include "Operation.h"
#include "Operation2.h"
namespace Computational_Graph{
    class Set_Graph{
        typedef Graph_Node<float> GNode;
        std::map<string, GNode> graph;          //ͼ
        std::vector<string> info;              //�������Ϣ
        std::vector<float> Answer;             //�������Ϣ
        string res ; 
    public:
        Set_Graph() {
			res = "HAVEN't BEEN PUT IN" ;
		}
        Set_Graph(std::vector<string> && a)       //ֱ�Ӵ�����Ϣ�Ĺ��캯��
        {
            info = std::move(a);
        }

        void Input_info(std::vector<string> &&a) //������Ϣ
        {
            info = std::move(a);
            //WARNING?
        }
        void processing_Stage3();                        //�������ַ����Ĵ���  δ���
    template <class A>
        void Jianli_2(const string& obj, const string& p1, const string& p2)
        {
            auto x = graph.find(obj);  auto pt1 = graph.find(p1); auto pt2 = graph.find(p2);
            if(x!=graph.end())           //���ض������
            {
                std::cerr<<"False Redefination\n";
            }
            else if (pt2==graph.end()||pt1 == graph.end())
            {
                std::cerr<<"False Parameter defination\n";
            }
            else
            {
                graph[obj].Mode = Operator;
                graph[obj].Nodename = obj;
                BaseNode<float>* para1 = graph[p1].node.get();
                BaseNode<float>* para2 = graph[p2].node.get();
                graph[obj].node = std::make_shared<A>(obj,para1, para2);
            }
        }
        template <class A>
        void Jianli_1(const string& obj, const string& p1)
        {
            auto x = graph.find(obj);  auto pt1 = graph.find(p1);
            if(x!=graph.end())           //���ض������
            {
                std::cerr<<"False Redefination\n";
            }
            else if (pt1 == graph.end())
            {
                std::cerr<<"False Parameter defination\n";
            }
            else
            {
                graph[obj].Mode = Operator;
                graph[obj].Nodename = obj;
                BaseNode<float>* para1 = graph[p1].node.get();
                graph[obj].node = std::make_shared<A>(obj,para1);
            }
        }
        template <class A>
        void Jianli_3(const string& obj, const string& p1, const string& p2,const string & p3)
        {
            auto x = graph.find(obj);  auto pt1 = graph.find(p1); auto pt2 = graph.find(p2); auto pt3= graph.find(p3);
            if(x!=graph.end())           //���ض������
            {
                std::cerr<<"False Redefination\n";
            }
            else if (pt3==graph.end()||pt2==graph.end()||pt1 == graph.end())
            {
                std::cerr<<"False Parameter defination\n";
            }
            else
            {
                graph[obj].Mode = Operator;
                graph[obj].Nodename = obj;
                BaseNode<float>* para1 = graph[p1].node.get();
                BaseNode<float>* para2 = graph[p2].node.get();
                BaseNode<float>* para3 = graph[p3].node.get();
                graph[obj].node = std::make_shared<A>(obj,para1, para2,para3);
            }
        }
        
        
        //��װ������һ�ֲ�����
        void Compute(const string& a)             //���ڱ��ʽ���м���
        {
             float b = graph[a].node->Forward();
             Answer.push_back(b);
             if(b!= Minus_Max) cout<<b<<std::endl;
        }
        
        
		
        void SetAnswer(const string& name, int n)                       //��Variable����seranswer���� δ���
        {
            if(Answer[n]<=Minus_Max+eps) std::cerr<<"Invalid Operation\n";
            else if(graph[name].Mode== Varible) graph[name].node->Initalize(Answer[n]);
            else std::cerr<<"Set_answer option only for Varible\n";            //�����ΪVarible�򱨴�
        }
        void Initalize_PVC();                          //δ���
        void Initalize_Op();                           //δ���
        void Initalize_Ph(const string& name);               //����Ph(n����Ϊname)���г�ʼ����
        void Initalize_V(const string& name, float num);               //����V(n����Ϊname)���г�ʼ����
        void Initalize_C(const string& name, float num);               //����C(n����Ϊname)���г�ʼ����
        void Initalize_Input(const string& name, float num)           //�ڵ����׶ζ���������г�ʼ��;
        {
           if(graph[name].Mode==Placehold) graph[name].node->Initalize(num);
           else std::cerr<<"Invalid Operation\n";
        }
        bool IsValid(const string& name)           //��������ڵ㽨���Ƿ�Ϸ�
        {
            return graph[name].node->IsCycle(graph[name].Nodename);
        }
        
        //debug�ú���
		void print_debug(){
			for(auto i : info){
				cout << i << " " ;
			}
			cout << "\n" ;
			cout << res << "\n" ;
		} 
		string getres(){
			return res ;
		} 
    };
}

#endif /* Set_Graph_h */
