//
//  Tensor.h
//  计算图_第二阶段
//
//  Created by 王一诺 on 2019/6/11.
//  Copyright © 2019 王一诺. All rights reserved.
//

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
template <typename T>
T sigmoid (const T& a)
{
    return 1/ (1+std::exp(-a));
}

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
    Tensor (const std::vector<float>& a);
    Tensor (const std::vector<std::vector<float> >& a);
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
    friend Tensor sigmoid<Tensor>(const Tensor& a);
    friend Tensor tanh(const Tensor& a);
    friend Tensor exp(const Tensor& a);
    friend float Distance(const Tensor& a, const Tensor& b);   //损失函数
    //以上为重载的数学函数
    //以下为各种函数的导数
    friend Tensor I_Matrix(int size1, int size2);
    bool Match(std::vector<int>& a,std::vector<int>& b);
    friend Tensor Derive_Mutiply_left(const Tensor& result, const Tensor& left, const Tensor& right);
    friend Tensor Derive_Mutiply_right(const Tensor& result, const Tensor& left, const Tensor& right);
    friend Tensor Derive_sin(const Tensor& result, const Tensor& input);
    friend Tensor Derive_log(const Tensor& result, const Tensor& input);
    friend Tensor Derive_sigmoid(const Tensor& result, const Tensor& input);
    friend Tensor Derive_tanh(const Tensor& result, const Tensor& input);
    friend Tensor Derive_exp(const Tensor& result, const Tensor& input);
    friend Tensor Derive_Distance(const Tensor& input1, const Tensor& input2);
    //以上为各种函数的导数
    //以下为对张量的操作
    void slim(int i );
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
Tensor concat(const std::vector<Tensor>& list, int dim);

Tensor I_Matrix(int size1, int size2);
Tensor sin(const Tensor& a);
Tensor log(const Tensor& a);
Tensor sigmoid(const Tensor& a);
Tensor tanh(const Tensor& a);
Tensor exp(const Tensor& a);
float Distance(const Tensor& a, const Tensor& b);   //损失函数
Tensor operator *(float a, const Tensor& t);

//求导
Tensor Derive_Mutiply_left(const Tensor& result, const Tensor& left, const Tensor& right);
Tensor Derive_Mutiply_right(const Tensor& result, const Tensor& left, const Tensor& right);
Tensor Derive_sin(const Tensor& result, const Tensor& input);
Tensor Derive_log(const Tensor& result, const Tensor& input);
Tensor Derive_sigmoid(const Tensor& result, const Tensor& input);
Tensor Derive_tanh(const Tensor& result, const Tensor& input);
Tensor Derive_exp(const Tensor& result, const Tensor& input);
Tensor Derive_Distance(const Tensor& input1, const Tensor& input2);

#endif /* Tensor_h */
