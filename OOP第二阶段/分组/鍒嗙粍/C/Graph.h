#ifndef GRAPH
#define GRAPH

#include "Node.h"

struct Temp
{
    string arr[N];//Temp�ṹ����洢�д洢��ÿһ���ַ�������ַ�������
};

class Graph
{
private:
    map<string, Node> relation; //�����˽ڵ����ƺͽڵ�֮��Ĺ��� 
    
	bool error1;//ռλ��δ��ֵ���� 
    bool error2;//��0���� 
    bool error3;//LOG����������0���� 
    
	int index;
    int index2;
    
    float answers[5 * N]; //�洢�˼����� 
public:
    Graph();
    void NodeConstruct(string type, string _name, float v); //�����ڵ�ĺ��� 
    void eval(Temp &src, int);  //��ֵ������� 
    float calculate(Node &now); //�ݹ���㺯�� 
    float Cal(float ans1, float ans2, string option); //ֻ��Զ�Ԫ����ļ��㺯�� 
    void buildgraph(Temp &src); //��ͼ���� 
    void reset();               //ÿһ�������Ϻ�ĸ�ԭ���� 
    void setconstant(Temp &src);//�û������ĺ�����SETCONSTANT�� 
    void setanswer(Temp &src);  //�û������ĺ��� (SETANSWER)
    void constructnewrelation(string a, string b, string c, string d); //�����µĶ������ĺ��� 
    ~Graph();
};

#endif
