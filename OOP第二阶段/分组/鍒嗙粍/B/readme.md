###环境

`g++ -std=c++11`

---
```shell
>_ make
# 生成可执行文件 main
>_ make debug
# debug 模式，生成可执行文件 main，调试信息会输出到 log.txt
```
---
##tt.h
包含了各种**.h**文件，在使用时只需要
```c++
#include "tt.h"
```
---
###Oph
**include/Opt.h**
**src/Opt.cpp**
定义实现了各种运算符，其中**Opt**类是所有运算符的基类，所有其它运算符需要继承**Opt**类，并实现构造函数和`run_self()`

```c++
Opt* Opt::rename(string name)
	// 更改 Opt 名称为 name，返回自身指针

float Opt::calc(Opt* opt)
	// 计算某个依赖节点 opt 的值，如果 opt 已经被计算过则不重复计算，同时判断是否有Error

void Opt::feed(float data)
	// 给一个 PlaceHolder 赋值为 data

float Opt::run_self()
	// 虚函数，由子类实现，描述子类自身的计算过程
	// 如 Add 类的 run_self() 类似于 { return a + b; } Cond 类则类似于 { if(c) return a; else return b; }

void Opt::run()
    // 计算所有依赖节点，然后计算自身，并将结果储存
```
-----------------------------------
###Graph
**include/Graph.h**
**src/Graph.cpp**

定义实现了计算图**Graph**类，用于新建、维护和计算各类运算符，每个运算符都属于一个计算图

```c++
void Graph::new_Binary(string name, string type, string a, string b)
	// 新建名为 name 的双目运算符 如 type = "+" 或者 "=="

void Graph::new_Unary(string name, string type, string a)
	// 新建名为 name 的单目运算符 如 type = "Sin" 或者 type =  "Print"

void Graph::new_Cond(string condition, string a, string b)
	// 新建名为 name 的条件判断运算符

void Graph::new_PlaceHolder(string name)
	// 新建名为 name 的 PlaceHolder

void Graph::new_Constant(string name, float data)
	// 新建名为 name 初值为 data 的 Constant

void Graph::new_Variable(string name, float data)
	// 新建名为 name 初值为 data 的 Varible

void Graph::clean()
	// 将所有节点标记为未计算过，每次 EVAL 前需要执行

void Graph::Error(string)
	// 报错
```
-----------------------------------
###Session
**include/Session.h**
**src/Session.cpp**
每个Session含有一个Graph计算图，用于运行计算图，保存计算结果
```c++
void Session::declare(string)
	// 一阶段，描述变量

void Session::code(string)
	// 二阶段，定义运算节点

void Session::run(string)
	// 三阶段，计算操作
```