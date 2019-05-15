// 这个文件声明了resultant类，它是data类的派生类，表示计算图中经过计算得到的中间结点
// 其中负责进行计算的operate函数集中在Calculation头文件中进行实现

#pragma once

#include "data.h"
#include "placeholder.h"

#include <string>
#include <vector>

class resultant: public data
{
protected:
    std::string operation; // 结点赋值所使用的计算方式
    std::vector <data*> son; // 结点赋值所使用的其他结点
public:
    explicit resultant(std::string n_input, std::string op_input, int v_cnt, data** v_input):
    data(std::move(n_input)), operation(std::move(op_input))
    {
        son.clear();
        for (int i=0; i<v_cnt; i++)
            son.push_back(v_input[i]);
    }; // resultant是无初值结点
    // 在构造resultant时还需要额外输入表示计算方式的字符串，需要其他结点的数量和一个包含它们的指针的数组
    ~resultant() override = default;
    void set_value()
    {
    	flushed=false;
        bool all_valued=true; // 表示所有需要的结点是否都被可用值的布尔型
        for (int i=0; i<son.size(); i++)
        {
            if(son[i]->check_flushed()) // 如果有结点还没有被遍历过
            {
                if (dynamic_cast<resultant *> (son[i])) // 如果结点是resultant且没有可用值
                    dynamic_cast<resultant *> (son[i])->set_value(); //递归调用set_value()为其赋值
            }
            if (!son[i]->check_valued()){
            	result=son[i]->get_result();
            	all_valued=false;
            } //再次检查，如果仍然没有可用值则all_valued置false,并传递无法计算的原因
        }
        if (!all_valued) // 如果有结点没有可用值
        {
            valued=false; // 无法完成计算
            return;
        }
        else //所有结点都有可用值
        {
        	result="ok"; // 可以计算
            this->operate(); // 调用计算函数
            if(result=="ok") // 如果计算步骤没有数学错误
                valued=true; //valued置True，有可用值
            else valued=false; // 在计算过程中的数学错误已经传递给result，无可用值
        }
    }; // 隐藏了基类中的set_value(input)
    void flush() override
    {
    	if (flushed) return;
    	flushed=true;
        valued=false; // 结点本身初始化
        for (int i=0; i<son.size(); i++)
            son[i]->flush(); // 对其所有曾使用过的结点初始化
    }
    void operate();
};
