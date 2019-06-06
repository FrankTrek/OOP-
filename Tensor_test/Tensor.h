//
//  Tensor.h
//  Tensor_Test
//
//  Created by 王一诺 on 2019/5/26.
//  Copyright © 2019 王一诺. All rights reserved.
//

#ifndef Tensor_h
#define Tensor_h
#include <vector>
#include <initializer_list>
#include <iostream>
#include <cmath>


class Tensor{
    
    int dim;
    std::vector<int> index;  //索引
    std::vector<int> shapes; //形状;
    std::vector<float> values;//存储数据；
public:
    Tensor ();
    Tensor (const std::initializer_list<int>& a);
    Tensor (const std::vector<int>& a, int b);
    Tensor (float a);
    Tensor (const std::vector<int>& a);
    Tensor (const std::vector<std::vector<int> >& a);
    Tensor (const Tensor& a);
    Tensor (Tensor&& a);
    //以上为构造函数
    std::vector<int> num_to_address(int n);
    //辅助转换函数
    Tensor& operator = (const Tensor& a);
    Tensor& operator = (Tensor&& a);
    float& operator () (const std::vector<int>& a);
    float show_values() const;
    float show_values(const std::vector<int>& a) const;
    float&  operator () ();
    Tensor operator + (const Tensor& a);
    Tensor operator - (const Tensor& a);
    Tensor operator * (float a);
    friend Tensor operator *(float a, const Tensor& t);
    Tensor operator * (const Tensor& a);
    //重载运算符
    //以下为重载数学函数
    friend Tensor sin(const Tensor& a);
    friend Tensor log(const Tensor& a);
    friend Tensor sigmoid(const Tensor& a);
    friend Tensor tanh(const Tensor& a);
    friend Tensor exp(const Tensor& a);
    //以上为重载的数学函数
    //以下为对张量的操作
    Tensor transposition();   //转置
    std::vector<int> shape() const; //返回形状
    std::vector<int> indexs() const; //返回索引
    void show_shapes() ;       //输出形状
    int dimention() const;
    
    void Print();             //打印矩阵
    Tensor reshape(const std::vector<int>& a) const;         //改变形状
    //
    void revalue (const std::vector<float>& val);
    //
    ~Tensor() {}
};
Tensor stack(const std::vector<Tensor>& list, int dim);


#endif /* Tensor_h */
