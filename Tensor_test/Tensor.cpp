//
//  Tensor_1.cpp
//  计算图_第二阶段
//
//  Created by 王一诺 on 2019/6/11.
//  Copyright © 2019 王一诺. All rights reserved.
//
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
Tensor::Tensor (const std::vector<float >& a)
{
    dim = 1;
    index.push_back(1);
    shapes.push_back(static_cast<int>( a.size() ));
    for(int i = 0; i<a.size(); i++)
    {
        values.push_back(a[i]);
    }
}
Tensor::Tensor (const std::vector<std::vector<float> >& a)
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
        if(abs(dim-a.dim)!=1)
        {
            std::cerr<<"Error: Unmatch Size for Addition\n";
            return Tensor();
        }
        else {
            Tensor big,small;
            if(dim>a.dim) {
                big = *this;
                small = a;
            }
            else {
                small = *this;
                big =a;
            }
            std::vector<int > bigshape=big.shape();
            std::vector<int > smallshape= small.shape();
            for(int i = 0; i< small.dim;i++) {
                if(bigshape[i+1]!=smallshape[i])
                {
                    std::cerr<<"Error: Unmatch Size for Addition\n";
                    return Tensor();
                }
            }
            std::cout<<"default broadcast!\n";
            std::vector<Tensor> list;
            for(int i=0;i<bigshape[0];i++) {
                list.push_back(small);
            }
            small= stack(list, 0);
            return big+small;
        }
    }
    bool chk=true;
    int select = 0;
    for(int i = 0 ; i<dim; i++)
    {
        if(shapes[i]!=a.shapes[i])
        {
            if(chk == true&& (shapes[i]==1||a.shapes[i]==1))
            {
                chk = false;
                select = i;
            }
            else {
                std::cerr<<"Error: Unmatch Size for Addition\n";
                return Tensor();
            }
        }
    }
    //
    if(!chk) {
        std::cout<<"broadcast!"<<std::endl;
        Tensor big;Tensor small;
        if(shapes[select]==1)
        {
            big = a;
            small = *this;
        }
        else {
            big = *this;
            small = a;
        }
        std::vector<Tensor> list;
        for(int i = 0; i< big.shapes[select];i++)
            list.push_back(small);
        
        return big+concat(list, select);
        
    }
    //
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
        if(abs(dim-a.dim)!=1)
        {
            std::cerr<<"Error: Unmatch Size for Addition\n";
            return Tensor();
        }
        else {
            Tensor big,small;
            if(dim>a.dim) {
                big = *this;
                small = a;
            }
            else {
                small = *this;
                big =a;
            }
            std::vector<int > bigshape=big.shape();
            std::vector<int > smallshape= small.shape();
            for(int i = 0; i< small.dim;i++) {
                if(bigshape[i+1]!=smallshape[i])
                {
                    std::cerr<<"Error: Unmatch Size for Addition\n";
                    return Tensor();
                }
            }
            std::cout<<"default broadcast!\n";
            std::vector<Tensor> list;
            for(int i=0;i<bigshape[0];i++) {
                list.push_back(small);
            }
            small= stack(list, 0);
            return big-small;
        }
    }
    bool chk=true;
    int select = 0;
    for(int i = 0 ; i<dim; i++)
    {
        if(shapes[i]!=a.shapes[i])
        {
            if(chk == true&& (shapes[i]==1||a.shapes[i]==1))
            {
                chk = false;
                select = i;
            }
            else {
                std::cerr<<"Error: Unmatch Size for Addition\n";
                return Tensor();
            }
        }
    }
    //
    if(!chk) {
        std::cout<<"broadcast!"<<std::endl;
        Tensor big;Tensor small;
        if(shapes[select]==1)
        {
            big = a;
            small = *this;
        }
        else {
            big = *this;
            small = a;
        }
        std::vector<Tensor> list;
        for(int i = 0; i< big.shapes[select];i++)
            list.push_back(small);
        
        return big-concat(list, select);
        
    }
    //
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
    if(dim==0||values.size()==1)
    {
        Tensor temp(a);
        float para = values[0];
        return temp * para;
    }
    if(a.dim==0||a.values.size()==1)
    {
        Tensor temp(*this);
        float para = a.values[0];
        return temp * para;
    }
    if(a.dim==1)
    {
        return *this * a.reshape({1,a.shape()[0]});
    }
    if(shapes[dim-1]!=a.shapes[0])
    {
        if(shapes[dim-1]==1) {
            std::vector<int >vc;
            vc.push_back(1);
            for(int i=0;i<a.shapes.size();i++) {
                vc.push_back(a.shapes[i]);
            }
            return operator *(a.reshape(vc));
        }
        else {
            std::cerr<<"Error Unmatch Size for Mutiply\n";
            return Tensor();
        }
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
void Tensor::slim(int i)
{
    if(dim>=1&&shapes[i]==1)
    {
        std::vector<int> a = shapes;
        a.erase(a.begin()+i);
        *this = reshape(a);
    }
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
std::vector<int> Tensor::shape ()const
{
    return shapes;
}
std::vector<int> Tensor::indexs ()const
{
    return index;
}
void Tensor::show_shapes()
{
    for(int i = 0; i<shapes.size();i++)
    {
        std::cout<<shapes[i]<<" ";
    }
    std::cout<<std::endl;
}

int Tensor::dimention() const{
    return dim;
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
Tensor Tensor::reshape(const std::vector<int> &a) const
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

void Tensor::revalue(const std::vector<float> &val)
{
    if(val.size()==values.size())
        values = val;
}

Tensor stack(const std::vector<Tensor> &list, int dim)
{
    int num = list.size();
    std::vector<int> Index = list [0].indexs();
    std::vector<int> element = list[0].shape();
    if(dim>element.size()){
        
        std::cerr<<"The dimention is too large" <<std::endl;
    }
    for(int i=1;i<num;i++) {
        if(list[i].shape()!=element) {
            std::cerr<<"The tensor's sizes do not equal with each other"<<std::endl;
            return Tensor(0);
        }
    }
    std::vector<int> newshape ;
    for(int i=0;i<dim;i++) {
        newshape.push_back(element[i]);
    }
    newshape.push_back(num);
    for(int i=dim;i<element.size();i++) {
        newshape.push_back(element[i]);
    }
    if(list[0].dimention()==0)
        newshape.pop_back();
    Tensor newtensor (newshape, 1);
    
    int size = newtensor.shape()[0]*newtensor.indexs()[0];
    
    std::vector<float > newvalues ;
    for(int i=0;i<size;i++) {
        std::vector<int > temp = newtensor.num_to_address(i);
        int select = temp[dim];
        temp.erase(temp.begin()+dim);
        
        newvalues.push_back(list[select-1].show_values(temp));
    }
    newtensor.revalue(newvalues);
    return newtensor;
    
}

Tensor concat(const std::vector<Tensor>& list, int dim)
{
    if(list[0].dimention()==0){
        std::vector<float > newvalue;
        for(int i =0;i< list.size();i++)
        {
            newvalue.push_back(list[i].show_values());
        }
        return Tensor(newvalue);
    }
    else if (list[0].dimention()<=dim)
    {
        std::cerr<<"The dimention is too large"<<std::endl;
        return 0;
    }
    else {
        std::vector<int > newshape = list[0].shape();
        int newlength=0;
        for(int i = 0; i<list.size();i++) {
            newlength+=list[i].shape()[dim];
        }
        newshape[dim]=newlength;
        Tensor newtensor (newshape, 1);
        std::vector<float> newvalues;
        int size = newtensor.shape()[0]*newtensor.indexs()[0];
        for(int i = 0; i<size;i++) {
            
            std::vector<int > temp = newtensor.num_to_address(i);
            int j;
            for(j = 0; j< list.size();j++) {
                if(temp[dim]<=list[j].shape()[dim])
                    break;
                temp[dim]-=list[j].shape()[dim];
            }
            newvalues.push_back(list[j].show_values(temp));
        }
        newtensor.revalue(newvalues);
        return newtensor;
    }
}
