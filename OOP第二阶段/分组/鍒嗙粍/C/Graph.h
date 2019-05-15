#ifndef GRAPH
#define GRAPH

#include "Node.h"

struct Temp
{
    string arr[N];//Temp结构体里存储有存储着每一行字符串块的字符串数组
};

class Graph
{
private:
    map<string, Node> relation; //建立了节点名称和节点之间的关联 
    
	bool error1;//占位符未赋值报错 
    bool error2;//除0报错 
    bool error3;//LOG参数不大于0报错 
    
	int index;
    int index2;
    
    float answers[5 * N]; //存储了计算结果 
public:
    Graph();
    void NodeConstruct(string type, string _name, float v); //建立节点的函数 
    void eval(Temp &src, int);  //赋值输出函数 
    float calculate(Node &now); //递归计算函数 
    float Cal(float ans1, float ans2, string option); //只针对二元运算的计算函数 
    void buildgraph(Temp &src); //建图函数 
    void reset();               //每一句计算完毕后的复原函数 
    void setconstant(Temp &src);//置换变量的函数（SETCONSTANT） 
    void setanswer(Temp &src);  //置换变量的函数 (SETANSWER)
    void constructnewrelation(string a, string b, string c, string d); //创建新的二叉树的函数 
    ~Graph();
};

#endif
