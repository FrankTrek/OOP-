#ifndef COMPUTATIONALGRAPH_H
#define COMPUTATIONALGRAPH_H

#include "Node.h"
#include "Scalar.h"
#include "Operator.h"
#include "Tensor.h"
#include <map>
#include <utility>
#include <sstream>
#include <iostream>
#include "Session.h"
template <typename T >
class ComputationalGraph
{
private:
    template <typename To>
    friend class AssignOperator;
    std::map<std::string, Node<T>*>NodeMap;    //NodeMap: 缁撶偣鍚嶅埌鎸囧悜缁撶偣鐨勬寚閽堢殑鏄犲皠
    std::vector<T>PreAnswer;            //PreAnswer: 淇濆瓨鍓嶅簭鎿嶄綔鐨勭瓟妗?
    std::string ErrorSignal;                //ErrorSignal: 璁板綍閿欒淇℃伅
    int TimeTag;                            //TimeTag: 璁板綍缁撶偣鏇存柊涓庤绠楃殑鏃堕棿
    std::vector<Node<T>*>NodeAddress;           //NodeAddress锛氳褰曟墍鏈夊嚭鐜拌繃鐨勭粨鐐圭殑鎸囬拡锛岀敤浜庢瀽鏋?
    Session_Manager<T> Manager;         //瀵逛笉鍚寁arible瀛樺€肩殑绠＄悊
    std::vector<Node<T>*> Order_of_Derive;
public:
    ComputationalGraph(){
        NodeMap.clear();
        PreAnswer.clear();
        NodeAddress.clear();
        Order_of_Derive.clear();
        TimeTag = 0;
    }
    void ErrorPrint(std::ostream& OutStream);    //    杈撳嚭瀵瑰簲鐨勯敊璇俊鎭?
    Node<T> *Find(const std::string& NodeName){
        if (NodeMap.find(NodeName) == NodeMap.end())    return NULL;
        else return NodeMap[NodeName];
    }    //    鏍规嵁缁撶偣鍚嶅鎵剧浉搴旂粨鐐?
    int GetTime(){
        return TimeTag;
    }                             //    鑾峰緱褰撳墠璁＄畻鍥剧殑鏃堕棿鏍囪
    T GetPreviousAnswer(const int& Index){
        return PreAnswer[Index - 1];
    }    //    鑾峰緱绗?Index 涓搷浣滅殑绛旀
    void Calc(const std::string& NodeName, const std::vector<std::pair<std::string, T> >& InitNode, std::ostream& OutStream);    //  璁＄畻鍥句腑鐨勭粨鐐瑰€煎苟杈撳嚭锛堟垨杈撳嚭閿欒淇℃伅锛?
    void AddNode(Node<T>* NewNode){
        NodeMap[NewNode->GetName()] = NewNode;
        NodeAddress.push_back(NewNode);
    }                //    鍚戣绠楀浘涓娣绘柊缁撶偣
    void EmptyCall();                            //    璁板綍 SETCONSTANT 鍜?SETANSWER 鎿嶄綔
    
    //鍑嗗鐗瑰寲涓篢ensor鐨勮绠楀浘
    friend Tensor ToTensor(std::vector<std::string>& a,int& start);
    ///
    
    //Add by Cai on 5.22
    
    std::vector<std::string> info;
    
    void  incision(){
        while (!info.empty()) info.pop_back();
        std::string sentence;
        std::getline(std::cin, sentence);
        std::stringstream s1(sentence);
        std::string tmp;
        while (s1>>tmp) {
            if(tmp!="=") info.push_back(tmp);
        }
    }
    
    void workstage1();
    void workstage2();
    void workstage3();
    
    //End Add
    
    ~ComputationalGraph(){
        for (auto it : NodeAddress)
        {
            delete it;
        }
        NodeMap.clear();
        NodeAddress.clear();
        PreAnswer.clear();
    }
};





template <typename T>
class AssignOperator: public Node<T>{
private:
    Session_Manager<T>* Manager;
public:
    AssignOperator(const std::string& InitName, const std::vector<Node<T>*>& InitPre, Session_Manager<T>* Manager1);
    T Solve(std::string& ErrorSignal, std::vector<Node<T>*>* Order_of_Derive=0){
        
            if (ErrorSignal.size() != 0)  return 0;
            this->Pre[1]->Calc(this->GetTime(), ErrorSignal);
            if (ErrorSignal.size() != 0)  return 0;
            Tensor Value_receive = this->Pre[1]->GetValue();
            Manager->Set_Value(this->Pre[0]->GetName(), Value_receive);
            return this->Pre[0]->Calc(this->GetTime(), ErrorSignal);
        
    };
    void Backward(T ,std::string&ErrorSignal);
};


template <typename T>
void ComputationalGraph<T>::workstage2(){
    std::string ini;
    getline(std::cin, ini);
    int times= std::stoi(ini);
    
    while (times--) {
        incision();
        if(info[2]=="+")                 //涓哄姞娉?
        {
            std::vector<Node<T>*> vs;
            vs.push_back(Find(info[1]));
            vs.push_back(Find(info[3]));
            AddNode(new PlusOperator<T>(info[0],vs));
        }
        else if(info[2]=="-")                 //涓轰箻娉?
        {
            std::vector<Node<T>*> vs;
            vs.push_back(Find(info[1]));
            vs.push_back(Find(info[3]));
            AddNode(new MinusOperator<T>(info[0],vs));
        }
        else if(info[2]=="*"){
            std::vector<Node<T>*> vs;
            vs.push_back(Find(info[1]));
            vs.push_back(Find(info[3]));
            AddNode(new MultipleOperator<T>(info[0],vs));
        }
        else if(info[2]=="/")
        {
            //Div(info[0], info[1], info[3]);
            std::vector<Node<T>*> vs;
            vs.push_back(Find(info[1]));
            vs.push_back(Find(info[3]));
            AddNode(new DivisionOperator(info[0],vs));
        }
        else if(info[2]=="<")
        {
            std::vector<Node<T>*> vs;
            vs.push_back(Find(info[1]));
            vs.push_back(Find(info[3]));
            AddNode(new LessOperator(info[0],vs));
        }
        else if(info[2]=="<=")
        {
            std::vector<Node<T>*> vs;
            vs.push_back(Find(info[1]));
            vs.push_back(Find(info[3]));
            AddNode(new LessEqualOperator(info[0],vs));
        }
        else if(info[2]==">")
        {
            std::vector<Node<T>*> vs;
            vs.push_back(Find(info[1]));
            vs.push_back(Find(info[3]));
            AddNode(new GreaterOperator(info[0],vs));
        }
        else if(info[2]==">=")
        {
            std::vector<Node<T>*> vs;
            vs.push_back(Find(info[1]));
            vs.push_back(Find(info[3]));
            AddNode(new GreaterEqualOperator(info[0],vs));
        }
        else if(info[2]=="==")
        {
            std::vector<Node<T>*> vs;
            vs.push_back(Find(info[1]));
            vs.push_back(Find(info[3]));
            AddNode(new EqualOperator(info[0],vs));
        }
        else if (info[1]=="BIND")
        {
            std::vector<Node<T>*> vs;
            vs.push_back(Find(info[2]));
            vs.push_back(Find(info[3]));
            AddNode(new BindOperator(info[0],vs));
        }
        else if (info[2]=="AT")
        {
            std::vector<Node<T>*> vs;
            vs.push_back(Find(info[1]));
            vs.push_back(Find(info[3]));
            AddNode(new AtOperator(info[0],vs));
        }
        else if(info[1]=="ASSIGN")
        {
            std::vector<Node<T>*> vs;
            vs.push_back(Find(info[2]));
            vs.push_back(Find(info[3]));
            AddNode(new AssignOperator<T>(info[0],vs,&Manager));
        }
        else if(info[1]=="SIN")
        {
            std::vector<Node<T>*> vs;
            vs.push_back(Find(info[2]));
            AddNode(new SinOperator<T>(info[0],vs));
        }
        else if(info[1]=="LOG")
        {
            std::vector<Node<T>*> vs;
            vs.push_back(Find(info[2]));
            AddNode(new LogOperator<T>(info[0],vs));
        }
        else if(info[1]=="TANH")
        {
            std::vector<Node<T>*> vs;
            vs.push_back(Find(info[2]));
            AddNode(new TanhOperator<T>(info[0],vs));
        }
        else if(info[1]=="EXP")
        {
            std::vector<Node<T>*> vs;
            vs.push_back(Find(info[2]));
            AddNode(new ExpOperator<T>(info[0],vs));
        }
        else if(info[1]=="SIGMOID")
        {
            std::vector<Node<T>*> vs;
            vs.push_back(Find(info[2]));
            AddNode(new SigmoidOperator<T>(info[0],vs));
        }
        else if(info[1]=="PRINT" || info[1] == "Print")
        {
            std::vector<Node<T>*> vs;
            vs.push_back(Find(info[2]));
            AddNode(new PrintOperator<T>(info[0],vs,std::cout));
        }
        else if (info[1]=="ASSERT")
        {
            std::vector<Node<T>*> vs;
            vs.push_back(Find(info[2]));
            AddNode(new AssertOperator(info[0],vs));
        }
        else if (info[1]=="GRAD")
        {
            std::vector<Node<T>*> vs;
            vs.push_back(Find(info[2]));
            AddNode(new GradOperator(info[0],vs,&Order_of_Derive));
        }
        else if(info[1]=="COND")
        {
            std::vector<Node<T>*> vs;
            vs.push_back(Find(info[2]));
            vs.push_back(Find(info[3]));
            vs.push_back(Find(info[4]));
            AddNode(new CondOperator(info[0],vs));
        }
    }
}

#endif
