#include "Graph.h"
#include "Node.h"
#include "Cut.h"

int main(){
	Graph graph;
	
	int n; //变量数 
	int m; //节点数 
	int q; //操作数 

	string buffer; //暂存每一行字符串 
	string blank;  //用于排除回车符 
	
	//第一部分，输入常量、变量和占位符 
	cin >> n;
	getline(cin, blank);
 	
	for(int i = 0; i < n; i++)
	{
  		Temp temp1; //Temp结构体里存储有存储着每一行字符串块的字符串数组 
  		int count_num = 0; //记录每一行字符串块的数目（此处count_num最后就是数目，下两栏count_num+1代表数目） 
  
  		func_cut(temp1, count_num, buffer); //切块后存储 
		//构建基础节点 
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
	
	//第二部分，继续计算节点和构造新节点 
	cin >> m;
	getline(cin, blank);
	
	for(int i = 0; i < m; i++)
	{
  		Temp temp2; //Temp结构体里存储有存储着每一行字符串块的字符串数组
		int count_num = -1; //count_num+1在最后表示数组最后一位的位置
  
		func_cut(temp2, count_num, buffer); //切块后存储 
		
		graph.buildgraph(temp2); //调用建图函数 
 	}

 	//第三部分，赋值和输出 
	cin >> q;
	getline(cin, blank);
	
	for(int i = 0; i < q; i++)
	{
		Temp temp3; //Temp结构体里存储有存储着每一行字符串块的字符串数组
  		int count_num = -1; //count_num+1在最后表示数组最后一位的位置
  
  		func_cut(temp3, count_num, buffer); //切块后存储 
		
		graph.eval(temp3,count_num); //调用赋值输出函数 
 	}
 	return 0;
}
