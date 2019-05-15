// 这个文件声明了data类，data对象代表着计算树中的每个结点
// data类是一个基类，由它会派生出共四种不同的派生类

#pragma once

#include <string>

class data
{
protected:
    std::string name; // 结点的变量名
    std::string result; // 结点的状态，或者是无法计算的原因
    double x; // 结点的浮点数值
    bool valued; // 在计算过程中标识结点是否已被计算过，有可用值的布尔型
    bool flushed; // 是否处于初始状态的布尔型
public:
    explicit data(std::string n_input): name(std::move(n_input)), x(0), valued(false), flushed(true) {}; // 对于无需初始化浮点数值的派生类型使用的构造函数
    explicit data(std::string n_input, double x_input): name(std::move(n_input)), x(x_input), valued(true), flushed(true) {}; // 对于需要初始化浮点数值的派生类型使用的构造函数
    // 构造函数中，n_input表示名字的输入，x_input表示浮点数值的输入
    virtual ~data() = default; // 析构函数
    virtual void set_value(double input)
    {
    	x=input;
    	flushed=true;
    	valued=true;
    } //对结点赋值的函数，经过赋值后该结点valued置True
    // 注意到constant是不能在初始化后重新赋值的，我们在constant类中对这个函数进行了覆盖处理，对constant调用set_value(input)会输出错误
    // 注意到resultant的赋值方法具有特殊性，我们在resultant类中对这个函数进行了覆盖处理，对resultant只能调用set_value()来赋值
    double get_value() {return x;} // 返回结点的浮点数值
    std::string get_name() {return name;} // 返回结点的变量名
    bool check_valued() {return valued;} // 返回结点是否有可用值
    virtual void flush() = 0; // 在每次计算过程后，将结点返回到初始状态，对于没有初始值的结点需要将它们valued置False
    std::string get_result() {return result;} //返回结点的状态
    bool check_flushed() {return flushed;} // 返回结点是否处于初始状态
};
