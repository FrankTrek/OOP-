//
//  Session.h
//  计算图_第二阶段
//
//  Created by 王一诺 on 2019/6/6.
//  Copyright © 2019 王一诺. All rights reserved.
//

//
//  Session.hpp
//  Tensor_Test
//
//  Created by 王一诺 on 2019/6/3.
//  Copyright © 2019 王一诺. All rights reserved.
//

#ifndef SESSION_H
#define SESSION_H

#include <stdio.h>
#include "ComputationalGraph.h"
#include "Scalar.h"
#include <map>
#include <vector>
#include <iostream>

class Session{
private:
    friend class Session_Manager;
    
    std::map<std::string, float> Varible_Value;
    
    Session () {};
    Session (const Session& a)
    {
        Varible_Value = a.Varible_Value;
    }
    void Add_Varible(Node* varible)
    {
        
        Varible_Value[varible->GetName()] = varible->GetValue();
    }
    void SetValue(const std::string& name, float value)
    {
        Varible_Value[name] = value;
    }
    void File_in(const std::string& File_name)     //未完成
    {
        ;
    }
    void File_out(const std::string& File_name)     //未完成
    {
        ;
    }
    void Show_Values()
    {
        std::cout<<"VARIBLE"<<"             "<<"VALUES\n";
        for(auto i : Varible_Value)
        {
            std::cout<<i.first<<"             "<<i.second<<std::endl;
        }
    }
    ~Session() {}
};



class Session_Manager
{
    Session* session_on;
    int mark;
    std::vector<Session* > sessions;
    std::map<std::string, Node*> Varible_Pool;
public:
    Session_Manager()
    {
        sessions.push_back(new Session());
        session_on = sessions[0];
        mark = 0;
    }
    int Show_Session_Num()
    {
        return sessions.size();
    }
    void Add_Session()
    {
        sessions.push_back(new Session(*session_on));
    }
    void File_in_New(const std::string& File_name)
    {
        sessions.push_back(new Session(*session_on));
        sessions[sessions.size()-1]->File_in(File_name);
    }
    void Switch(int i)
    {
        if(i<0||i>=sessions.size())
        {
            std::cerr<<"Wrong Size for Swithch\n";
        }
        else
        {
            session_on = sessions[i];
            mark = i;
        }
    }
    void Add_Varible(Node* varible)
    {
        session_on->Add_Varible(varible);
        Varible_Pool[varible->GetName()] = varible;
    }
    void Set_Value(const std::string& name, float value)
    {
        session_on->SetValue(name, value);
    }
    void Assign_Values(int Timetag)
    {
        for(auto i : Varible_Pool)
        {
            std::string name = i.second->GetName();
            float value = session_on->Varible_Value[name];
            i.second->SetValue(value, Timetag);
        }
    }
    void File_in(const std::string& File_name)
    {
        session_on->File_in(File_name);
    }
    void File_out(const std::string& File_name)
    {
        session_on->File_out(File_name);
    }
    void Delete_Session()
    {
        delete session_on;
        sessions.erase(std::begin(sessions)+mark);
    }
    void Show_Values()
    {
        session_on->Show_Values();
    }
    ~Session_Manager()
    {
        for(int i = 0; i<sessions.size();i++)
        {
            sessions[i]->~Session();
            sessions[i] = nullptr;
            session_on = nullptr;
        }
    }
    
};

#endif /* Session_hpp */
