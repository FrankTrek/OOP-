//
//  Tensor_2.cpp
//  计算图_第二阶段
//
//  Created by 王一诺 on 2019/6/11.
//  Copyright © 2019 王一诺. All rights reserved.
//

#include <stdio.h>
#include "Tensor.h"

float Distance(const Tensor& a, const Tensor& b)
{
    if(a.values.size()!=b.values.size())
    {
        std::cerr<<"Unmatch Size for Match Distance\n";
        return 0.0;
    }
    float sum = 0;
    for(int i = 0; i<a.values.size(); i++)
    {
        sum+=(a.values[i]-b.values[i])*(a.values[i]-b.values[i]);
    }
    return sum;
}

Tensor I_Matrix(int size1, int size2)
{
    Tensor temp({size1,size2});
    for(int i = 1; i<=size1; i++)
    {
        for(int j = 1; j<=size2; j++)
        {
            if(i==j)
            {
                temp({i,j})=1;
            }
        }
    }
    return temp;
}

Tensor Derive_Mutiply_left(const Tensor& result, const Tensor& left, const Tensor& right)
{
    std::vector<int> size = result.shape();
    size.insert(size.end(), left.shapes.begin(), left.shapes.end());
    Tensor derive(size,1);
    for(int i = 0; i<derive.values.size();i++)
    {
        std::vector<int> index = derive.num_to_address(i);
        std::vector<int> index2;
        index2.push_back(index[index.size()-1]);
        for(int i = left.dim-1; i<result.dim;i++)
        {
            index2.push_back(index[i]);
        }
        bool match = true;
        for(int i = 0; i<left.dim-1;i++)
        {
            if(index[i]!=index[result.dim+i])
            {
                match = false;
                break;
            }
        }
        if(match) derive(index) = right.show_values(index2);
        else derive(index) = 0;
    }
    for(int i = 0 ;i<result.dim-1; i++)
    {
        if(result.shapes[i]==1)
        {
            derive.slim(i);
        }
    }
    return derive;
}

Tensor Derive_Mutiply_right(const Tensor& result, const Tensor& left, const Tensor& right)
{
    return left;
}

Tensor Derive_sin(const Tensor& result, const Tensor& input)
{
    if(input.dimention()==2&&input.shape()[1]==1)
    {
        int size = input.shapes[0];
        std::vector<int> a{size,size};
        Tensor derive(a,1);
        for(int i = 1; i<=size; i++)
        {
            for(int j = 1; j<=size; j++)
            {
                if(i==j)
                {
                   
                    derive({i,j}) = cos(input.show_values({i,1}));
                }
            }
        }
        return derive;
    }
    std::cerr<<"Could not derive\n";
    return Tensor();
}
Tensor Derive_log(const Tensor& result, const Tensor& input)
{
    if(input.dimention()==2&&input.shape()[1]==1)
    {
        int size = input.shapes[0];
        std::vector<int> a{size,size};
        Tensor derive(a,1);
        for(int i = 1; i<=size; i++)
        {
            for(int j = 1; j<=size; j++)
            {
                if(i==j)
                {
                    
                    derive({i,j}) = 1/input.show_values({i,1});
                }
            }
        }
        return derive;
    }
    std::cerr<<"Could not derive\n";
    return Tensor();
}
Tensor Derive_sigmoid(const Tensor& result, const Tensor& input)
{
    if(input.dimention()==2&&input.shape()[1]==1)
    {
        int size = input.shapes[0];
        std::vector<int> a{size,size};
        Tensor derive(a,1);
        for(int i = 1; i<=size; i++)
        {
            for(int j = 1; j<=size; j++)
            {
                if(i==j)
                {
                    float a = input.show_values({i,1});
                    derive({i,j}) = (exp(-a))/((1+exp(-a))*(1+exp(-a)));
                }
            }
        }
        return derive;
    }
    std::cerr<<"Could not derive\n";
    return Tensor();
}
Tensor Derive_tanh(const Tensor& result, const Tensor& input)
{
    if(input.dimention()==2&&input.shape()[1]==1)
    {
        int size = input.shapes[0];
        std::vector<int> a{size,size};
        Tensor derive(a,1);
        for(int i = 1; i<=size; i++)
        {
            for(int j = 1; j<=size; j++)
            {
                if(i==j)
                {
                    float value = input.show_values({i,1});
                    derive({i,j}) = (1-value*value);
                }
            }
        }
        return derive;
    }
    std::cerr<<"Could not derive\n";
    return Tensor();
}
Tensor Derive_exp(const Tensor& result, const Tensor& input)
{
    if(input.dimention()==2&&input.shape()[1]==1)
    {
        int size = input.shapes[0];
        std::vector<int> a{size,size};
        Tensor derive(a,1);
        for(int i = 1; i<=size; i++)
        {
            for(int j = 1; j<=size; j++)
            {
                if(i==j)
                {
                    float value = input.show_values({i,1});
                    derive({i,j}) = exp(value);
                }
            }
        }
        return derive;
    }
    std::cerr<<"Could not derive\n";
    return Tensor();
}
Tensor Derive_Distance(const Tensor& input1, const Tensor& input2)
{
    if(input1.dimention()==2&&input1.shape()[1]==1)
    {
        Tensor derive({static_cast<int>(input1.values.size())});
        for(int i = 0; i<input1.values.size(); i++)
        {
            float y1 = input1.values[i];
            float y2 = input2.values[i];
            derive.values[i] = -2*(y1-y2);
        }
        return derive;
    }
    std::cerr<<"Could not derive\n";
    return Tensor();
}
