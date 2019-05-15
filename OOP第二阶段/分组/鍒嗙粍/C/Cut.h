#ifndef CUT
#define CUT

#include "Graph.h"

void func_cut(Temp& temp0, int& count_num0, string buffer0) //将数组切块的函数 
{
	getline(cin, buffer0);
	int count_pos = 0; //记录原来数组中遍历到的位置 
	while(count_pos < buffer0.size())
 	{
		string buf_w; //暂时存储某一块数组块 
		for(int i = count_pos; ; i++)
		{
			if((buffer0[i] != ' ')&&(buffer0[i] != '\0'))
			{
				buf_w += buffer0[i];
   			}
   			if(buffer0[i] == ' '){
    			count_pos = i + 1;
    			count_num0 += 1;
    			break;
   			}
   			if(buffer0[i] == '\0'){
    			count_pos = i;
   				count_num0 += 1;
    			break;
    		}
  		}
  		temp0.arr[count_num0] = buf_w;
	}
}

#endif
