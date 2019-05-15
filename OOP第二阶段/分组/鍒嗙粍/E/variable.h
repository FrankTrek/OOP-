// 这个文件声明了constant类，它是data类的派生类
#pragma once

#include "data.h"
#include <string>

class variable: public data
{
public:
    explicit variable(std::string n_input, double x_input): data(std::move(n_input), x_input) {result="ok";}; // variable是有初值结点
    ~variable() override = default;
    void flush() override
    {
        result="ok";
    	flushed=true;
        valued=true;
    }
};
