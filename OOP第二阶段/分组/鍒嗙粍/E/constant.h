// 这个文件声明了constant类，它是data类的派生类

#pragma once

#include "data.h"
#include <string>

class constant: public data
{
public:
    explicit constant(std::string n_input, double x_input): data(std::move(n_input), x_input) {result="ok";}; // constant是有初值结点
    ~constant() override = default;
    void set_value(double input) override
    {
        result="ERROR: Constants cannot be reset values";
    } // 覆盖了基类中的set_value(input)
    void flush() override
    {
        result="ok";
    	flushed=true;
        valued=true;
    }
};
