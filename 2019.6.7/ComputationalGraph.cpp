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
    T tmpans = NodeMap[NodeName]->Calc(TimeTag, ErrorSignal);
    if (ErrorSignal.size() != 0)
    {
        PreAnswer.push_back(0);            //    µ±ƒ≥∏ˆ≤Ÿ◊˜ πErrorSignal∑«ø’£¨Œﬁ¥∞∏£¨”√0’ºŒª;
        this->ErrorPrint(OutStream);    //    ≤¢ ‰≥ˆ¥ÌŒÛ–≈œ¢;
        return ;                        //    ∑µªÿ
    }
    PreAnswer.push_back(tmpans);
    OutStream.setf(std::ios::fixed);
    OutStream << std::setprecision(4) << tmpans << std::endl;
    return ;
}

//    º«¬º SETCONSTANT ∫Õ SETANSWER ≤Ÿ◊˜
template <typename T>
void ComputationalGraph<T>::EmptyCall()
{
    PreAnswer.push_back(0);                //    µ±ƒ≥∏ˆ≤Ÿ◊˜Œ™SET≤Ÿ◊˜ ±£¨Œﬁ ‰≥ˆ£®¥∞∏£©£¨”√0’ºŒª
    TimeTag++;
}


Tensor ToTensor(std::vector<std::string>& a, int& start)
{
    int temp_dim;
    temp_dim = std::stoi(a[start]);
    
    
    if (temp_dim == 1) {
        int temp_shape = std::stoi(a[++start]);
        std::vector<float> temp_value;
        for (int i = 1; i <= temp_shape; i++) {
            temp_value.push_back(std::stof(a[++start]));
        }
        return Tensor(temp_value);//合法？
    }
    else if (temp_dim == 2) {
        int tempm = std::stoi(a[++start]);
        int tempn = std::stoi(a[++start]);
        
        std::vector<std::vector<float>> A;
        for (int i = 1; i <= tempm; i++) {
            std::vector<float> temp_A;
            for (int i = 1; i <= tempn; i++) {
                temp_A.push_back(std::stof(a[++start]));
            }
            A.push_back(temp_A);
        }
        return Tensor(A);
    }
    else {
        std::cerr << "Error:Dim >=3" << std::endl;
        return Tensor(0);
    }
    
}





//    Œˆππº∆À„Õº

//



//Add by Cai on 5.22

template <>
void ComputationalGraph<Tensor>::workstage1() {
    std::string ini;
    std::getline(std::cin, ini);
    int times = std::stoi(ini);
    
    while (times--) {
        incision();
        if (info[1] == "P") {
            AddNode(new Placeholder<Tensor>(info[0]));
        }
        else if (info[1] == "C") {
            int index = 2;
            AddNode(new Constant<Tensor>(info[0], ToTensor(info, index)));
        }
        else if (info[1] == "V") {
            std::vector<float> pa;
            for (int i = 2; i < info.size(); i++ ){
                pa.push_back(std::stof(info[i]));
            }
            int index = 2;
            auto i = new Variable<Tensor>(info[0], ToTensor(info, index));
            Manager.Add_Varible(i);//Manager 模板化
            AddNode(i);
        }
        else {
            std::cout << "ERROR: Unaccepted Input" << std::endl;
        }
    }
}

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
        else if (info[0]=="SETANSWER"){
            EmptyCall();
            int timetag=GetTime();
            Find(info[1])->SetValue(PreAnswer[std::stoi(info[2])-1], timetag);
            Manager.Set_Value(info[1], PreAnswer[std::stoi(info[2])-1]);
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
        else if(info[0]=="FILE")   //输入输出se ssion：FILE IN xxx/FILE OUT xxx
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



template<>
void ComputationalGraph<Tensor>::workstage3() {
    std::string ini;
    getline(std::cin, ini);
    int times = std::stoi(ini);
    
    while (times--) {
        incision();
        if (info[0] == "EVAL") {
            std::vector< std::pair<std::string, Tensor> >vc;
            if (info.size() > 2) {
                int temp_index = 2;
                int temp_n = std::stoi(info[temp_index]);
                for (int i = 1; i <= temp_n; i++) {
                    vc.push_back(std::make_pair(info[++temp_index], ToTensor(info, ++temp_index)));
                }
                
            }
     
            Calc(info[1], vc, std::cout);
            
        }
        else if (info[0] == "SETANSWER") {
            EmptyCall();
            int timetag = GetTime();
            Find(info[1])->SetValue(PreAnswer[std::stoi(info[2]) - 1], timetag);
            Manager.Set_Value(info[1], PreAnswer[std::stoi(info[2]) - 1]);
        }
        
        else if (info[0] == "SETCONSTANT") {
            EmptyCall();
            int timetag = GetTime();
            int temp_index = 2;
            Find(info[1])->SetValue(ToTensor(info,temp_index), timetag);
            Manager.Set_Value(info[1], std::stof(info[2]));
        }
        //以下为新增的session_manager的功能
        else if (info[0] == " APPLY ")  //session的输入定义如下
        {
            if (info.size() == 3)     // APPLY NEW SESSION 添加一个当前session的复制品
            {
                EmptyCall();
                Manager.Add_Session();
            }
            else if (info[4] == "FILE")  // APPLY NEW SESSION THROUGH FILE NAMED XXX 由文件输入新的session
            {
                EmptyCall();
                std::string name = info[6];
                Manager.File_in_New(name);
            }
            
        }
        else if (info[0] == "SWITCH")   //切换session：SWITCH TO SESSION xxx
        {
            EmptyCall();
            int i = atoi(info[3].data());
            Manager.Switch(i);
        }
        else if (info[0] == "FILE")   //输入输出session：FILE IN xxx/FILE OUT xxx
        {
            if (info[1] == "IN")
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
        else if (info[0] == "DELETE") //DELETE SESSION 删除目前的session
        {
            if (Manager.Show_Session_Num() == 0)
            {
                EmptyCall();
                std::cerr << "NO SESSIONS NOW\n";
            }
            else
            {
                EmptyCall();
                Manager.Delete_Session();
            }
        }
        else if (info[0] == "SHOW") //SHOW SESSION 显示目前的session值
        {
            EmptyCall();
            Manager.Show_Values();
        }
        
    }
}


//End Add




template<typename T>
AssignOperator<T>::AssignOperator(const std::string & InitName, const std::vector<Node<T>*>& InitPre, Session_Manager<T>* Manager1) : Node<T>(InitName,0,0), Manager(Manager1)
{
  //  Pre = InitPre;
}
/*
template<>
float AssignOperator<float>::Solve(std::string &ErrorSignal,std::vector<Node<float>*>* Order_of_Derive= 0)
{
    if (ErrorSignal.size() != 0)  return 0;
    Pre[1]->Calc(this->GetTime(), ErrorSignal);
    if (ErrorSignal.size() != 0)  return 0;
    float Value_receive = Pre[1]->GetValue();
    Manager->Set_Value(Pre[0]->GetName(), Value_receive);
    return Pre[0]->Calc(this->GetTime(), ErrorSignal);
}

template<>

Tensor AssignOperator<Tensor>::Solve(std::string& ErrorSignal, std::vector<Node<Tensor>*>* Order_of_Derive= 0)
{
    if (ErrorSignal.size() != 0)  return 0;
    Pre[1]->Calc(this->GetTime(), ErrorSignal);
    if (ErrorSignal.size() != 0)  return 0;
    Tensor Value_receive = Pre[1]->GetValue();
    Manager->Set_Value(Pre[0]->GetName(), Value_receive);
    return Pre[0]->Calc(this->GetTime(), ErrorSignal);
}
*/
template<typename T>
void AssignOperator<T>::Backward(T, std::string &ErrorSignal)
{
    ErrorSignal= "Not defined Grad for LessEqualOperator yet!";
}

