// 这个文件声明了placeholder类，它是data类的派生类

#pragma once

#include "data.h"
#include <string>

class placeholder: public data
{
protected:
public:
    explicit placeholder(std::string n_input): data(std::move(n_input)) {result="ERROR: Placeholder missing";}; // placeholder是无初值结点
    ~placeholder() override = default;
    void set_value(double input) override
    {
    	result="ok";
    	x=input;
    	flushed=false;
    	valued=true;
    }
    void flush() override
    {
    	result="ERROR: Placeholder missing";
    	flushed=true;
        valued=false;
    }
};
