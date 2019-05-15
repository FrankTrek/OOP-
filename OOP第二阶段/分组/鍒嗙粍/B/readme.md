###����

`g++ -std=c++11`

---
```shell
>_ make
# ���ɿ�ִ���ļ� main
>_ make debug
# debug ģʽ�����ɿ�ִ���ļ� main��������Ϣ������� log.txt
```
---
##tt.h
�����˸���**.h**�ļ�����ʹ��ʱֻ��Ҫ
```c++
#include "tt.h"
```
---
###Oph
**include/Opt.h**
**src/Opt.cpp**
����ʵ���˸��������������**Opt**��������������Ļ��࣬���������������Ҫ�̳�**Opt**�࣬��ʵ�ֹ��캯����`run_self()`

```c++
Opt* Opt::rename(string name)
	// ���� Opt ����Ϊ name����������ָ��

float Opt::calc(Opt* opt)
	// ����ĳ�������ڵ� opt ��ֵ����� opt �Ѿ�����������ظ����㣬ͬʱ�ж��Ƿ���Error

void Opt::feed(float data)
	// ��һ�� PlaceHolder ��ֵΪ data

float Opt::run_self()
	// �麯����������ʵ�֣�������������ļ������
	// �� Add ��� run_self() ������ { return a + b; } Cond ���������� { if(c) return a; else return b; }

void Opt::run()
    // �������������ڵ㣬Ȼ��������������������
```
-----------------------------------
###Graph
**include/Graph.h**
**src/Graph.cpp**

����ʵ���˼���ͼ**Graph**�࣬�����½���ά���ͼ�������������ÿ�������������һ������ͼ

```c++
void Graph::new_Binary(string name, string type, string a, string b)
	// �½���Ϊ name ��˫Ŀ����� �� type = "+" ���� "=="

void Graph::new_Unary(string name, string type, string a)
	// �½���Ϊ name �ĵ�Ŀ����� �� type = "Sin" ���� type =  "Print"

void Graph::new_Cond(string condition, string a, string b)
	// �½���Ϊ name �������ж������

void Graph::new_PlaceHolder(string name)
	// �½���Ϊ name �� PlaceHolder

void Graph::new_Constant(string name, float data)
	// �½���Ϊ name ��ֵΪ data �� Constant

void Graph::new_Variable(string name, float data)
	// �½���Ϊ name ��ֵΪ data �� Varible

void Graph::clean()
	// �����нڵ���Ϊδ�������ÿ�� EVAL ǰ��Ҫִ��

void Graph::Error(string)
	// ����
```
-----------------------------------
###Session
**include/Session.h**
**src/Session.cpp**
ÿ��Session����һ��Graph����ͼ���������м���ͼ�����������
```c++
void Session::declare(string)
	// һ�׶Σ���������

void Session::code(string)
	// ���׶Σ���������ڵ�

void Session::run(string)
	// ���׶Σ��������
```