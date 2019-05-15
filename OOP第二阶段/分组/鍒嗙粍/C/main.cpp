#include "Graph.h"
#include "Node.h"
#include "Cut.h"

int main(){
	Graph graph;
	
	int n; //������ 
	int m; //�ڵ��� 
	int q; //������ 

	string buffer; //�ݴ�ÿһ���ַ��� 
	string blank;  //�����ų��س��� 
	
	//��һ���֣����볣����������ռλ�� 
	cin >> n;
	getline(cin, blank);
 	
	for(int i = 0; i < n; i++)
	{
  		Temp temp1; //Temp�ṹ����洢�д洢��ÿһ���ַ�������ַ������� 
  		int count_num = 0; //��¼ÿһ���ַ��������Ŀ���˴�count_num��������Ŀ��������count_num+1������Ŀ�� 
  
  		func_cut(temp1, count_num, buffer); //�п��洢 
		//���������ڵ� 
  		if(temp1.arr[2] == "P")
  		{
   			graph.NodeConstruct("Placeholder", temp1.arr[1], MAX);
  		}
  		if(temp1.arr[2] == "C")
  		{
   			graph.NodeConstruct("Constant", temp1.arr[1], stof(temp1.arr[3]));
		}
		if(temp1.arr[2] == "V")
		{
			graph.NodeConstruct("Variable", temp1.arr[1], stof(temp1.arr[3]));
		}
	}
	
	//�ڶ����֣���������ڵ�͹����½ڵ� 
	cin >> m;
	getline(cin, blank);
	
	for(int i = 0; i < m; i++)
	{
  		Temp temp2; //Temp�ṹ����洢�д洢��ÿһ���ַ�������ַ�������
		int count_num = -1; //count_num+1������ʾ�������һλ��λ��
  
		func_cut(temp2, count_num, buffer); //�п��洢 
		
		graph.buildgraph(temp2); //���ý�ͼ���� 
 	}

 	//�������֣���ֵ����� 
	cin >> q;
	getline(cin, blank);
	
	for(int i = 0; i < q; i++)
	{
		Temp temp3; //Temp�ṹ����洢�д洢��ÿһ���ַ�������ַ�������
  		int count_num = -1; //count_num+1������ʾ�������һλ��λ��
  
  		func_cut(temp3, count_num, buffer); //�п��洢 
		
		graph.eval(temp3,count_num); //���ø�ֵ������� 
 	}
 	return 0;
}
