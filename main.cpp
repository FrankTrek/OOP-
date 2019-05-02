#include <iostream>
#include <sstream>
#include "Set_Graph.h"
using namespace Computational_Graph ;
using std::stringstream ;
using std::cin ;  
using std::cout ;
// 我认真思考了一下要不要把所有的一切通通打包，在主函数里只留一个简单粗暴的最终版本接口。但后来觉得太粗暴了，那么就是现在这个样子。 
/*更新日志 
	4.30 Z 让主函数变得好看了 
*/ 
int main() {
    Set_Graph work;
    work.Stage1();
    work.Stage2();
    work.Stage3();

	return 0;
}
