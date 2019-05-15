// 这个文件实现了resultant类中的operate函数

#pragma once

#include "resultant.h"
#include <cmath>
#include <iostream>
#include <iomanip>

const double ep=0.00001; // 辅助判断在保留四位小数情况下是否相等

void resultant::operate()
{
    double temp;
    long long v_cnt=this->son.size(); // 需要结点的数量
    auto* v=new double [this->son.size()];
    for (int i=0; i<v_cnt; i++) v[i]=this->son[i]->get_value(); // 需要结点的浮点数值组成的数组

    // 以下每一个判断语句表示一种运算，operation保存的字符串与题目输入的运算符保持一致

    if (this->operation == "+")
        this->x=v[0]+v[1];
    else if (this->operation == "-")
        this->x=v[0]-v[1];
    else if (this->operation == "*")
        this->x=v[0]*v[1];
    else if (this->operation == "/")
    {
        if(fabs(v[1]-0)<ep) // 表示在保留四位小数下其是否为0，下同
            result="ERROR: Division by zero";
        else
            this->x=v[0]/v[1];
    }
    else if (this->operation == "SIN")
        this->x=sin(v[0]);
    else if (this->operation == "LOG")
    {
        if (!((v[0]>0) && (fabs(v[0]-0)>ep))) // 表示是否不大于0
        	result="ERROR: LOG operator's input must be positive";
        else
            this->x=log(v[0]);
    }
    else if (this->operation == "EXP")
        this->x=exp(v[0]);
    else if (this->operation == "SIGMOID")
    {
        temp=exp(v[0]);
        this->x=temp/(1+temp);
    }
    else if (this->operation == "TANH")
    {
        temp=exp(v[0]);
        this->x=(temp-1/temp)/(temp+1/temp);
    }
    else if (this->operation == "PRINT")
    {
        this->x=v[0];
        std::cout << "PRINT operator: " << this->son[0]->get_name() << " = " << std::fixed << std::setprecision(4) << this->x << std::endl;
    }
    else if (this->operation == ">")
    {
        if((v[0]>v[1]) && (fabs(v[0]-v[1])>ep))
            this->x=1.0;
        else
            this->x=0.0;
    }
    else if (this->operation == "<")
    {
        if((v[0]<v[1]) && (fabs(v[0]-v[1])>ep))
            this->x=1.0;
        else
            this->x=0.0;
    }
    else if (this->operation == "==")
    {
        if(fabs(v[0]-v[1])<ep)
            this->x=1.0;
        else
            this->x=0.0;
    }
    else if (this->operation == ">=")
    {
        if((v[0]<v[1]) && (fabs(v[0]-v[1])>ep))
            this->x=0.0;
        else
            this->x=1.0;
    }
    else if (this->operation == "<=")
    {
        if((v[0]>v[1]) && (fabs(v[0]-v[1])>ep))
            this->x=0.0;
        else
            this->x=1.0;
    }
    else if (this->operation == "COND")
    {
        if ((v[0]>0) && (fabs(v[0]-0)>ep))
            this->x=v[1];
        else
            this->x=v[2];
    }
    delete[] v;
}
