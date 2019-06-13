#include "ComputationalGraph.h"
#include "Operator.h"
#include <iomanip>
#include <string>
#include <utility>
#include <sstream>
#include <iostream>



template <typename T>
void ComputationalGraph<T>::ErrorPrint(std::ostream& OutStream)
{
    OutStream << "ERROR: " << ErrorSignal << std::endl;
}

//  º∆À„Ω·µ„÷µ≤¢ ‰≥ˆ£®ªÚ ‰≥ˆ¥ÌŒÛ–≈œ¢£©
template <typename T>
void ComputationalGraph<T>::Calc(const std::string& NodeName, const std::vector< std::pair<std::string, T> >& InitNode, std::ostream& OutStream)
{
    TimeTag++;                            //    ∏¸–¬ ±º‰±Íº«
    for (auto it : InitNode)
    {
        NodeMap[it.first]->SetValue(it.second, TimeTag);
    }
    Manager.Assign_Values(TimeTag);             //更新varible的值
    ErrorSignal.clear();
    Order_of_Derive.clear();
    T tmpans = NodeMap[NodeName]->Calc(TimeTag, ErrorSignal);
    if (ErrorSignal.size() != 0)
    {
        PreAnswer.push_back(0);            //    µ±ƒ≥∏ˆ≤Ÿ◊˜ πErrorSignal∑«ø’£¨Œﬁ¥∞∏£¨”√0’ºŒª;
        this->ErrorPrint(OutStream);    //    ≤¢ ‰≥ˆ¥ÌŒÛ–≈œ¢;
        return ;
        //return 0;                        //    ∑µªÿ
    }
    PreAnswer.push_back(tmpans);
    OutStream.setf(std::ios::fixed);
    OutStream << std::setprecision(4) << tmpans << std::endl;
    //return tmpans;
}

//    º«¬º SETCONSTANT ∫Õ SETANSWER ≤Ÿ◊˜
template <typename T>
void ComputationalGraph<T>::EmptyCall()
{
    PreAnswer.push_back(0);                //    µ±ƒ≥∏ˆ≤Ÿ◊˜Œ™SET≤Ÿ◊˜ ±£¨Œﬁ ‰≥ˆ£®¥∞∏£©£¨”√0’ºŒª
    TimeTag++;
}

//    Œˆππº∆À„Õº

//




//Add by Cai on 5.22


template <>
void ComputationalGraph<float>::workstage1() {
    std::string ini;
    std::getline(std::cin,ini);
    int times= std::stoi(ini);
    
    while (times--) {
        incision();
        if(info[1]=="P") {
            AddNode(new Placeholder<float>(info[0]));
        }
        else if (info[1]=="C") {
            AddNode(new Constant<float>(info[0],std::stof(info[2])));
        }
        else if (info[1]=="V") {
            auto i = new Variable<float>(info[0],std::stof(info[2]));
            Manager.Add_Varible(i);
            AddNode(i);
        }
        else {
            std::cout << "ERROR: Unaccepted Input" << std::endl;
        }
    }
}
template <>
void ComputationalGraph<float>::workstage2() {
    std::string ini;
    getline(std::cin, ini);
    int times= std::stoi(ini);
    
    while (times--) {
        incision();
        if(info[2]=="+")                 //为加法;
        {
            std::vector<Node<float>*> vs;
            vs.push_back(Find(info[1]));
            vs.push_back(Find(info[3]));
            AddNode(new PlusOperator<float>(info[0],vs));
        }
        else if(info[2]=="-")                 //为乘法
        {
            std::vector<Node<float>*> vs;
            vs.push_back(Find(info[1]));
            vs.push_back(Find(info[3]));
            AddNode(new MinusOperator<float>(info[0],vs));
        }
        else if(info[2]=="*")            //为减法
        {
            std::vector<Node<float>*> vs;
            vs.push_back(Find(info[1]));
            vs.push_back(Find(info[3]));
            AddNode(new MultipleOperator<float>(info[0],vs));
        }
        else if(info[2]=="/")
        {
            //Div(info[0], info[1], info[3]);
            std::vector<Node<float>*> vs;
            vs.push_back(Find(info[1]));
            vs.push_back(Find(info[3]));
            AddNode(new DivisionOperator(info[0],vs));
        }
        else if(info[2]=="<")
        {
            std::vector<Node<float>*> vs;
            vs.push_back(Find(info[1]));
            vs.push_back(Find(info[3]));
            AddNode(new LessOperator(info[0],vs));
        }
        else if(info[2]=="<=")
        {
            std::vector<Node<float>*> vs;
            vs.push_back(Find(info[1]));
            vs.push_back(Find(info[3]));
            AddNode(new LessEqualOperator(info[0],vs));
        }
        else if(info[2]==">")
        {
            std::vector<Node<float>*> vs;
            vs.push_back(Find(info[1]));
            vs.push_back(Find(info[3]));
            AddNode(new GreaterOperator(info[0],vs));
        }
        else if(info[2]==">=")
        {
            std::vector<Node<float>*> vs;
            vs.push_back(Find(info[1]));
            vs.push_back(Find(info[3]));
            AddNode(new GreaterEqualOperator(info[0],vs));
        }
        else if(info[2]=="==")
        {
            std::vector<Node<float>*> vs;
            vs.push_back(Find(info[1]));
            vs.push_back(Find(info[3]));
            AddNode(new EqualOperator(info[0],vs));
        }
        else if (info[1]=="BIND")
        {
            std::vector<Node<float>*> vs;
            vs.push_back(Find(info[2]));
            vs.push_back(Find(info[3]));
            AddNode(new BindOperator(info[0],vs));
        }
        else if (info[2]=="AT")
        {
            std::vector<Node<float>*> vs;
            vs.push_back(Find(info[1]));
            vs.push_back(Find(info[3]));
            AddNode(new AtOperator(info[0],vs));
        }
        else if(info[1]=="ASSIGN")
        {
            std::vector<Node<float>*> vs;
            vs.push_back(Find(info[2]));
            vs.push_back(Find(info[3]));
            AddNode(new AssignOperator(info[0],vs,&Manager));
        }
        else if(info[1]=="SIN")
        {
            std::vector<Node<float>*> vs;
            vs.push_back(Find(info[2]));
            AddNode(new SinOperator<float>(info[0],vs));
        }
        else if(info[1]=="LOG")
        {
            std::vector<Node<float>*> vs;
            vs.push_back(Find(info[2]));
            AddNode(new LogOperator<float>(info[0],vs));
        }
        else if(info[1]=="TANH")
        {
            std::vector<Node<float>*> vs;
            vs.push_back(Find(info[2]));
            AddNode(new TanhOperator<float>(info[0],vs));
        }
        else if(info[1]=="EXP")
        {
            std::vector<Node<float>*> vs;
            vs.push_back(Find(info[2]));
            AddNode(new ExpOperator<float>(info[0],vs));
        }
        else if(info[1]=="SIGMOID")
        {
            std::vector<Node<float>*> vs;
            vs.push_back(Find(info[2]));
            AddNode(new SigmoidOperator<float>(info[0],vs));
        }
        else if(info[1]=="PRINT" || info[1] == "Print")
        {
            std::vector<Node<float>*> vs;
            vs.push_back(Find(info[2]));
            AddNode(new PrintOperator<float>(info[0],vs,std::cout));
        }
        else if (info[1]=="ASSERT")
        {
            std::vector<Node<float>*> vs;
            vs.push_back(Find(info[2]));
            AddNode(new AssertOperator(info[0],vs));
        }
        else if (info[1]=="GRAD")
        {
            std::vector<Node<float>*> vs;
            vs.push_back(Find(info[2]));
            AddNode(new GradOperator(info[0],vs,&Order_of_Derive));
        }
        else if(info[1]=="COND")
        {
            std::vector<Node<float>*> vs;
            vs.push_back(Find(info[2]));
            vs.push_back(Find(info[3]));
            vs.push_back(Find(info[4]));
            AddNode(new CondOperator(info[0],vs));
        }
    }
}

template<>
void ComputationalGraph<float>::workstage3() {
    std::string ini;
    getline(std::cin, ini);
    int times= std::stoi(ini);
    
    while (times--) {
        incision();
        if(info[0]=="EVAL") {
            int m=info.size()-3;
            std::vector< std::pair<std::string, float> >vc;
            for(int i=0;i<m;i+=2) {
                vc.push_back(std::make_pair(info[3+i], std::stof(info[4+i])));
            }
            
            Calc(info[1], vc, std::cout);
            
        }
        else if (info[0]=="SETANSWER") {
            EmptyCall();
            int timetag=GetTime();
            Find(info[1])->SetValue(PreAnswer[std::stoi(info[2])-1], timetag);
            Manager.Set_Value(info[1], PreAnswer[std::stoi(info[2])-1]);   //更新此时的
            
        }
        else if (info[0]=="SETCONSTANT") {
            EmptyCall();
            int timetag=GetTime();
            Find(info[1])->SetValue(std::stof(info[2]), timetag);
            Manager.Set_Value(info[1], std::stof(info[2]));
        }
        //以下为新增的session_manager的功能
        else if(info[0]== " APPLY ")  //session的输入定义如下
        {
            if(info.size()==3)     // APPLY NEW SESSION 添加一个当前session的复制品
            {
                EmptyCall();
                Manager.Add_Session();
            }
            else if(info[4]=="FILE")  // APPLY NEW SESSION THROUGH FILE NAMED XXX 由文件输入新的session
            {
                EmptyCall();
                std::string name = info[6];
                Manager.File_in_New(name);
            }
            
        }
        else if(info[0]=="SWITCH")   //切换session：SWITCH TO SESSION xxx
        {
            EmptyCall();
            int i = atoi(info[3].data());
            Manager.Switch(i);
        }
        else if(info[0]=="FILE")   //输入输出session：FILE IN xxx/FILE OUT xxx
        {
            if(info[1]=="IN")
            {
                EmptyCall();
                Manager.File_in(info[2]);
            }
            else
            {
                EmptyCall();
                Manager.File_out(info[2]);
            }
        }
        else if(info[0]=="DELETE") //DELETE SESSION 删除目前的session
        {
            if(Manager.Show_Session_Num()==0)
            {
                EmptyCall();
                std::cerr<<"NO SESSIONS NOW\n";
            }
            else
            {
                EmptyCall();
                Manager.Delete_Session();
            }
        }
        else if(info[0]=="SHOW") //SHOW SESSION 显示目前的session值
        {
            EmptyCall();
            Manager.Show_Values();
        }
        
    }
}




//End Add




AssignOperator::AssignOperator(const std::string & InitName, const std::vector<Node*>& InitPre, Session_Manager* Manager1) : Node(InitName,0,0), Manager(Manager1)
{
    Pre = InitPre;
}
float AssignOperator::Solve(std::string &ErrorSignal,std::vector<Node<float>*>*  Order_of_Derive )
{
    if (ErrorSignal.size() != 0)  return 0;
    Pre[1]->Calc(this->GetTime(), ErrorSignal);
    if (ErrorSignal.size() != 0)  return 0;
    float Value_receive = Pre[1]->GetValue();
    Manager->Set_Value(Pre[0]->GetName(), Value_receive);
    return Pre[0]->Calc(this->GetTime(), ErrorSignal);
}

void AssignOperator::Backward(float, std::string &ErrorSignal)
{
    ErrorSignal= "Not defined Grad for LessEqualOperator yet!";
}
