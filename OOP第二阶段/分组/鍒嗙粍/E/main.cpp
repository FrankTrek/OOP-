// 这是计算图项目的主程序

#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include "data.h"
#include "constant.h"
#include "calculation.h"
#include "placeholder.h"
#include "resultant.h"
#include "variable.h"

std::map<std::string, data*> data_map; // 这是一个map，在结点名称和对应对象的指针见建立联系，对于同名结点后者会覆盖前者

void primary_data_input(); // 这是输入原始数据的输入函数，即无需计算的初始结点
void secondary_data_input(); // 这是输入高级数据的输入函数，即新增加的结点
void instruction_input(); // 这是输入计算请求的输入函数

int main()
{
    primary_data_input();
    secondary_data_input();
    instruction_input();
    return 0;
}

void primary_data_input()
{
    int n;
    std::string name_input, type_input;
    double value_input;

    std::cin >> n;
    data_map.clear();
    for(int i=1; i<=n; i++)
    {
        std::cin >> name_input >> type_input;
        if(type_input=="P")
            data_map[name_input]=new placeholder(name_input); // 新建placeholder
        if(type_input=="C")
        {
            std::cin >> value_input;
            data_map[name_input]=new constant(name_input, value_input); // 新建constant
        }
        if(type_input=="V")
        {
            std::cin >> value_input;
            data_map[name_input]=new variable(name_input, value_input); // 新建variable
        }
    }
}

void secondary_data_input()
{
    int m;
    std::string formula_input;
    std::stringstream formula_buffer;
    std::vector <std::string> formula_bit;
    // 这里用stringstream进行辅助读入，_input后缀的string是整行读入的数据，_buffer后缀的stringstream用于缓冲，_bit后缀的vector是按空格分开后拆成的单个数据
    // 在instruction_input函数中运用了同样的操作
    data** son_data_buffer; // 存储计算所需要的结点的指针构成的数组

    std::cin >> m;
    getline(std::cin, formula_input);
    for(int i=1; i<=m; i++)
    {
        getline(std::cin, formula_input);
        formula_buffer.str("");
        formula_buffer.clear();
        formula_buffer << formula_input;
        formula_bit.clear();
        while(formula_buffer >> formula_input)
            formula_bit.push_back(formula_input);
        if ((formula_bit[3]=="+") || (formula_bit[3]=="-") || (formula_bit[3]=="*") || (formula_bit[3]=="/")) // 中缀2元运算符
        {
            son_data_buffer=new data*[2]{data_map[formula_bit[2]], data_map[formula_bit[4]]};
            data_map[formula_bit[0]]=new resultant(formula_bit[0], formula_bit[3], 2, son_data_buffer);
        }
        else if ((formula_bit[2]=="SIN") || (formula_bit[2]=="LOG") || (formula_bit[2]=="EXP") || (formula_bit[2]=="TANH") || (formula_bit[2]=="SIGMOID")) // 前缀1元运算符
        {
            son_data_buffer=new data*[1]{data_map[formula_bit[3]]};
            data_map[formula_bit[0]]=new resultant(formula_bit[0], formula_bit[2], 1, son_data_buffer);
        }
        if (formula_bit[2]=="PRINT") // print符
        {
            son_data_buffer=new data*[1]{data_map[formula_bit[3]]};
            data_map[formula_bit[0]]=new resultant(formula_bit[0], formula_bit[2], 1, son_data_buffer);
        }
        if ((formula_bit[3]==">") || (formula_bit[3]=="<") || (formula_bit[3]==">=") || (formula_bit[3]=="<=") || (formula_bit[3]=="==")) // 中缀2元比较运算符（其实可以和中缀2元运算符合并）
        {
            son_data_buffer=new data*[2]{data_map[formula_bit[2]], data_map[formula_bit[4]]};
            data_map[formula_bit[0]]=new resultant(formula_bit[0], formula_bit[3], 2, son_data_buffer);
        }
        if (formula_bit[2]=="COND") // 前缀3元条件运算符
        {
            son_data_buffer=new data*[3]{data_map[formula_bit[3]], data_map[formula_bit[4]], data_map[formula_bit[5]]};
            data_map[formula_bit[0]]=new resultant{formula_bit[0], formula_bit[2], 3, son_data_buffer};
        }
    }
}

void instruction_input()
{
    int q, k;
    std::string inquiry_input, inquiry_type, evaluatee_input, p_name_input; // _type后缀的string表示指令的类型，evaluatee是所求的结点，p_name是被赋值的placeholder的名字
    double value_input;
    std::vector <double> answer; // 这是一个vector，保存每一次操作的输出结果，如果没有输出盖茨操作的结果在answer中记为0
    std::stringstream inquiry_buffer;
    std::vector <std::string> inquiry_bit;

    std::cin >> q;
    getline(std::cin, inquiry_input);
    answer.clear();
    for (int i=1; i<=q; i++)
    {
        getline(std::cin, inquiry_input);
        inquiry_buffer.str("");
        inquiry_buffer.clear();
        inquiry_buffer << inquiry_input;
        answer.push_back(0);
        inquiry_buffer >> inquiry_type;
        if(inquiry_type=="EVAL")
        {
            inquiry_buffer >> evaluatee_input;
            inquiry_bit.clear();
            if (inquiry_buffer >> k)
            {
                for (int j=1; j<=k; j++)
                {
                    inquiry_buffer >> p_name_input >> value_input;
                    inquiry_bit.push_back(p_name_input);
                    data_map[p_name_input]->set_value(value_input);
                }
            }
            if (dynamic_cast <resultant*> (data_map[evaluatee_input])) // 如果所求的结点是一个高级数据，需要计算
                dynamic_cast <resultant*> (data_map[evaluatee_input])->set_value(); // 调用resultant特有的set_value()进行计算
            if(data_map[evaluatee_input]->get_result()=="ok") // 如果成功获得结果
            {
                answer[answer.size()-1]=data_map[evaluatee_input]->get_value();
                std::cout << std::fixed << std::setprecision(4) << answer.back() << std::endl; // 输出计算结果
            }
            else // 否则计算有错误
                std::cout << data_map[evaluatee_input]->get_result() << std::endl; // 输出无法计算的原因
            data_map[evaluatee_input]->flush(); // 对所求结点初始化
            for (int j=0; j<inquiry_bit.size(); j++)
                data_map[inquiry_bit[j]]->flush(); // 对所有赋值过的结点初始化
        }
        if(inquiry_type=="SETCONSTANT")
        {
            inquiry_buffer >> evaluatee_input >> value_input;
            data_map[evaluatee_input]->set_value(value_input);
        }
        if(inquiry_type=="SETANSWER")
        {
            inquiry_buffer >> evaluatee_input >> k;
            data_map[evaluatee_input]->set_value(answer[k-1]);
        }
    }
}