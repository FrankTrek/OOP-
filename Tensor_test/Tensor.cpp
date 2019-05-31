//
//  Tensor.cpp
//  Tensor_Test
//
//  Created by 王一诺 on 2019/5/26.
//  Copyright © 2019 王一诺. All rights reserved.
//

#include <stdio.h>
#include "Tensor.h"

Tensor::Tensor ()
{
    dim = 0;
    index.push_back(1);
    shapes.push_back(1);
    values.push_back(0);
}
Tensor::Tensor(const std::initializer_list<int>& a)
{
    for(auto i = a.begin(); i!=a.end(); i++)
    {
        shapes.push_back(*i);
    }
    dim = static_cast<int>(a.size());
    for(int i = 0; i<dim; i++)
    {
        index.push_back(1);
    }
    for(int i = dim-2; i>=0; i--)
    {
        index[i] = index[i+1]*shapes[i+1];
    }
    int totol = index[0]*shapes[0];
    for(int i = 0; i<totol; i++)
    {
        values.push_back(0);
    }
}
Tensor::Tensor (const std::vector<int>& a, int b)
{
    for(auto i = a.begin(); i!=a.end(); i++)
    {
        shapes.push_back(*i);
    }
    dim = static_cast<int>(a.size());
    for(int i = 0; i<dim; i++)
    {
        index.push_back(1);
    }
    for(int i = dim-2; i>=0; i--)
    {
        index[i] = index[i+1]*shapes[i+1];
    }
    int totol = index[0]*shapes[0];
    for(int i = 0; i<totol; i++)
    {
        values.push_back(0);
    }
}
Tensor::Tensor (float a)
{
    dim = 0;
    index.push_back(1);
    shapes.push_back(1);
    values.push_back(a);
}
Tensor::Tensor (const std::vector<int>& a)
{
    dim = 1;
    index.push_back(1);
    shapes.push_back(static_cast<int>( a.size() ));
    for(int i = 0; i<a.size(); i++)
    {
        values.push_back(a[i]);
    }
}
Tensor::Tensor (const std::vector<std::vector<int> >& a)
{
    dim = 2;
    int m = static_cast<int> (a.size() );
    int n = static_cast<int> (a[0].size());
    shapes.push_back(m);
    shapes.push_back(n);
    for(int i = 0; i<dim; i++)
    {
        index.push_back(1);
    }
    for(int i = dim-2; i>=0; i--)
    {
        index[i] = index[i+1]*shapes[i+1];
    }
    int totol = index[0]*shapes[0];
    for(int i = 0; i<totol; i++)
    {
        values.push_back(0);
    }
    for(int i = 0; i<m; i++)
    {
        for(int j = 0; j<n; j++)
        {
            int place = i*index[0]+j*index[1];
            values[place] = a[i][j];
        }
    }
    
}
Tensor:: Tensor (const Tensor& a)
{
    dim = a.dim;
    index = a.index;
    shapes = a.shapes;
    values = a.values;
}
Tensor:: Tensor (Tensor&& a)
{
    dim = a.dim;
    index = std::move(a.index);
    shapes = std::move(a.shapes);
    values = std::move(a.values);
}
//以上为构造函数
Tensor& Tensor:: operator = (const Tensor& a)
{
    dim = a.dim;
    index = a.index;
    shapes = a.shapes;
    values = a.values;
    return *this;
}
Tensor& Tensor::operator = (Tensor&& a)
{
    dim = a.dim;
    index = std::move(a.index);
    shapes = std::move(a.shapes);
    values = std::move(a.values);
    return *this;
}
//以上为重载等于号
float& Tensor::operator () (const std::vector<int>& a)
{
    if(a.size()!=dim)
    {
        std::cerr<<"Error: Unmatch Size\n";
        return values[0];
    }
    for(int i = 0; i<dim; i++)
    {
        if(a[i]>shapes[i])
        {
            std::cerr<<"Error: Data Overflow\n";
            return values[0];
        }
    }
    int place = 0;
    for(int i = 0; i<dim; i++)
    {
        place += index[i]*(a[i]-1);
    }
    return values[place];
}
float& Tensor::operator() ()
{
    if(dim!=0)
    {
        std::cerr<<"Error: Invalid Operation\n";
    }
    return values[0];
}
float Tensor::show_values() const
{
    if(dim!=0)
    {
        std::cerr<<"Error: Invalid Operation\n";
    }
    return values[0];
}
float Tensor::show_values(const std::vector<int> &a) const
{
    if(a.size()!=dim)
    {
        std::cerr<<"Error: Unmatch Size\n";
        return values[0];
    }
    for(int i = 0; i<dim; i++)
    {
        if(a[i]>shapes[i])
        {
            std::cerr<<"Error: Data Overflow\n";
            return values[0];
        }
    }
    int place = 0;
    for(int i = 0; i<dim; i++)
    {
        place += index[i]*(a[i]-1);
    }
    return values[place];
}

//以上为重载小括号
Tensor Tensor:: operator + (const Tensor& a)
{
    if(dim!= a.dim)
    {
        std::cerr<<"Error: Unmatch Size for Addition\n";
        return Tensor();
    }
    for(int i = 0 ; i<dim; i++)
    {
        if(shapes[i]!=a.shapes[i])
        {
            std::cerr<<"Error: Unmatch Size for Addition\n";
            return Tensor();
        }
    }
    Tensor temp(*this);
    for(int i = 0; i<values.size();i++)
    {
        temp.values[i] += a.values[i];
    }
    return temp;
}
Tensor Tensor:: operator - (const Tensor& a)
{
    if(dim!= a.dim)
    {
        std::cerr<<"Error: Unmatch Size for Addition\n";
        return Tensor();
    }
    for(int i = 0 ; i<dim; i++)
    {
        if(shapes[i]!=a.shapes[i])
        {
            std::cerr<<"Error: Unmatch Size for Addition\n";
            return Tensor();
        }
    }
    Tensor temp(*this);
    for(int i = 0; i<values.size();i++)
    {
        temp.values[i] -= a.values[i];
    }
    return temp;
}
Tensor Tensor::operator * (float a)
{
    Tensor temp(*this);
    for(int i = 0; i<values.size();i++)
    {
        temp.values[i] *= a;
    }
    return temp;
}
Tensor operator *(float a, const Tensor& t)
{
    Tensor temp(t);
    for(int i = 0; i<t.values.size();i++)
    {
        temp.values[i] *= a;
    }
    return temp;
}


std::vector<int> Tensor::num_to_address(int n)
{
    std::vector<int> temp(dim);
    int sum = 0;
    for(int i = 0; i<dim; i++)
    {
        int k =  n/index[i];
        sum *= shapes[i];
        int _add = k - sum ;
        sum = k;
        temp[i] = _add + 1;
    }
    return temp;
}


Tensor Tensor::operator*(const Tensor &a)
{
    if(dim==0)
    {
        Tensor temp(a);
        float para = values[0];
        return temp * para;
    }
    if(a.dim==0)
    {
        Tensor temp(*this);
        float para = a.values[0];
        return temp * para;
    }
    if(shapes[dim-1]!=a.shapes[0])
    {
        std::cerr<<"Error Unmatch Size for Mutiply\n";
        return Tensor();
    }
    std::vector<int> sizes;
    for(int i = 0; i<dim-1; i++)
    {
        sizes.push_back(shapes[i]);
    }
    for(int i = 1; i<a.dim; i++)
    {
        sizes.push_back(a.shapes[i]);
    }
    Tensor temp(sizes,1);
    int times = shapes[dim-1];
    for(int i = 0; i<temp.values.size(); i++)
    {
        std::vector<int> add_for_ans = temp.num_to_address(i);
        for(int j = 1;j<=times;j++)
        {
            
            std::vector<int> place1(dim);
            std::vector<int> place2(a.dim);
            place1[dim-1] = j;
            place2[0] = j;
            for(int k = 0 ; k<dim-1;k++)
            {
                place1[k] = add_for_ans[k];
            }
            for(int k = dim-1; k<temp.dim; k++)
            {
                int mark = k - dim+2;
                place2[mark] = add_for_ans[k];
            }
            temp.values[i] += this->operator()(place1)*a.show_values(place2);
            
        }
        
    }
    
    
    return temp;
}

Tensor sin(const Tensor& a)
{
    Tensor temp(a);
    for(int i = 0; i<temp.values.size();i++)
    {
        temp.values[i] = sin(temp.values[i]);
    }
    return temp;
}
Tensor log(const Tensor&a )
{
    Tensor temp(a);
    for(int i = 0; i<temp.values.size();i++)
    {
        if( temp.values[i]<=0)
        {
            std::cerr<<"Error Minus Values cannot be applied LOG\n";
            return temp;
        }
    }
    for(int i = 0; i<temp.values.size();i++)
    {
        temp.values[i] = log(temp.values[i]);
    }
    return temp;
}
Tensor exp(const Tensor& a)
{
    Tensor temp(a);
    for(int i = 0; i<temp.values.size();i++)
    {
        temp.values[i] = std::exp(temp.values[i]);
    }
    return temp;
}

Tensor sigmoid(const Tensor& a)
{
    Tensor temp(a);
    for(int i = 0; i<temp.values.size();i++)
    {
        float Temp = temp.values[i];
        float tmpa = std::exp(-Temp);
        float tmpb = 1.0 / (1.0 + tmpa);
        temp.values[i] = tmpb;
    }
    return temp;
}
Tensor tanh(const Tensor& a)
{
    Tensor temp(a);
    for(int i = 0; i<temp.values.size();i++)
    {
        float Temp = temp.values[i];
        float tmpa = std::exp(2.0 * Temp);
        float tmpb = (tmpa - 1.0) / (tmpa + 1.0);
        temp.values[i] = tmpb;
    }
    return temp;
}
Tensor Tensor::transposition()
{
    if(dim==0)
    {
        return *this;
    }
    else if(dim==1)
    {
        Tensor temp(*this);
        temp.dim = 2;
        temp.shapes.push_back(1);
        temp.index.push_back(1);
        return temp;
    }
    else if(dim==2)
    {/*
        Tensor temp(*this);
        int tmp = temp.index[0];
        temp.index[0] = temp.index[1];
        temp.index[1] = tmp;
        tmp = temp.shapes[0];
        temp.shapes[0] = temp.shapes[1];
        temp.shapes[1] = tmp;
        return temp;
      */
        Tensor temp(*this);
        temp.dim=2;
        
        std::swap(temp.shapes[0],temp.shapes[1]);
        temp.index[0]=temp.shapes[1];
        for(int i=0;i<temp.shapes[0];i++) {
            int row = i* temp.index[0];
            for(int j=0;j<temp.shapes[1];j++) {
                temp.values[row+j]=values[j*index[0]+i];
            }
        }
        return temp;
    }
    else
    {
        std::cerr<<"Error InValid Transposition Operation for Tensor whose dim higher than 2\n";
        return *this;
    }
}
std::vector<int> Tensor::shape()
{
    return shapes;
}
void Tensor::show_shapes()
{
    for(int i = 0; i<shapes.size();i++)
    {
        std::cout<<shapes[i]<<" ";
    }
    std::cout<<std::endl;
}
void Tensor::Print()
{
    if(dim==0)
    {
        std::cout<<values[0]<<std::endl;
    }
    else if(dim==1)
    {
        for(int i = 0; i<values.size();i++)
        {
            std::cout<<values[i]<<" ";
        }
        std::cout<<std::endl;
    }
    else if(dim==2)
    {
        for(int i = 1;i<=shapes[0];i++)
        {
            for(int j = 1; j<=shapes[1]; j++)
            {
                int mark = (i-1)*index[0]+(j-1)*index[1];
                std::cout<<values[mark]<<" ";
            }
            std::cout<<std::endl;
        }
    }
    else
    {
        std::cerr<<"Print vector, scale, matrix Only\n";
    }
}
Tensor Tensor::reshape(const std::vector<int> &a)
{
    int total = 1;
    for(int i = 0; i<a.size(); i++)
    {
        total *= a[i];
    }
    if(total!=values.size())
    {
        std::cerr<<"Size unmatch for Operation Reshape\n";
        return *this;
    }
    else
    {
        Tensor temp(a,1);
        temp.values = values;
        return temp;
    }
    
}

