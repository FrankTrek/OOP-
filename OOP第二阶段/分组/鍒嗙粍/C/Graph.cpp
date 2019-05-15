#include "Graph.h"

Graph::Graph()
{
	//建立图，初始化各个参数 
    error1 = false;
    error2 = false;
    error3 = false;
    index = 0;
    index2 = 0;
}

void Graph::NodeConstruct(string type, string _name, float v) //分情况建立节点 
{
    Node buf;
    
    if(type == "Constant")
        buf = move(Constant(_name, v));
    else if(type == "Placeholder")
        buf = move(Placeholder(_name, v));
    else if(type == "Variable")
        buf = move(Variable(_name, v));
    
	relation[_name] = buf; //将字符串与节点的对应关系存入map中 
}

void Graph::eval(Temp &src,int len)
{
    index++;
    
    if(src.arr[0] == "SETCONSTANT")
	{
        setconstant(src);
        return;
    }
    if(src.arr[0] == "SETANSWER")
	{
        setanswer(src);
        return;
    }
    
    string dst = src.arr[1]; //这是最终要得出结果的对象（数组从0开始） 
    
    float answer;
    
    if(relation[dst].ty == "C") //常量，直接输出 
	{
        cout << setprecision(4) << fixed << relation[dst].value << endl;
        return;
    }
    if(len == 1) //即为不需要任何其他变量，直接赋值 
	{
        answer = calculate(relation[dst]);
    }
    else {
        int count = stoi(src.arr[2]); //赋值对的数目 
        int idx = 3; //开始遍历时的位置 
        for(int i = 0; i < count; i++) //开始给需要的未赋值节点赋值 
		{
            relation[src.arr[idx]].value = stof(src.arr[idx+1]);
            idx += 2;
        }
        answer = calculate(relation[dst]);
    }
    
    //若有错误，报错；否则输出 
    if(error1)
        cout << "ERROR: Placeholder missing" << endl;
    else if(error2)
        cout << "ERROR: Division by zero" << endl;
    else if(error3)
        cout <<"ERROR: LOG operator's input must be positive" << endl;
    else {
        cout << setprecision(4) << fixed << answer << endl;
        answers[index] = answer;
    }
    
	reset(); //每个语句过后重新给中间节点赋值 
}

void Graph::reset()
{
    error1 = false;
    error2 = false;
    error3 = false;
    
    for(auto iter = relation.begin(); iter != relation.end(); iter++)
	{
        if(iter->second.ty != "C" && iter->second.ty != "V")
		{
            if(iter->second.ty == "PRINTED") //已经输出过的改回原样 
                iter->second.ty = "PRINT";
            iter->second.value = MAX; //value复原 
        }
    }
}

void Graph::setconstant(Temp &src)
{
    relation[src.arr[1]].value = stof(src.arr[2]);
}

void Graph::setanswer(Temp &src)
{
    relation[src.arr[1]].value = answers[stoi(src.arr[2])];
}

float Graph::Cal(float ans1, float ans2, string option) //只针对二元计算的计算函数（包括比较） 
{
    if(option == "/")
	{
        if(ans2 == 0)
		{
            error2 = true;
            return 0.0;
        }
        return ans1 / ans2;
    }
    else if(option == "+")
	{
        return ans1 + ans2;
    }
    else if(option == "-")
	{
        return ans1 - ans2;
    }
    else if(option == "*")
	{
        return ans1 * ans2;
    }
    else if(option == "<")
	{
        if(ans1 < ans2) return 1.0;
        return 0.0;
    }
    else if(option == "<=")
	{
        if(ans1 <= ans2) return 1.0;
        return 0.0;
    }
    else if(option == ">")
	{
        if(ans1 > ans2) return 1.0;
        return 0.0;
    }
    else if(option == ">=")
	{
        if(ans1 >= ans2) return 1.0;
        return 0.0;
    }
    else if(option == "==")
	{
        if(ans1 == ans2) return 1.0;
        return 0.0;
    }
    return 0.0;
}

float Graph::calculate(Node &now) //基本计算函数 
{
	
    if(error1 || error2 || error3) //如果有错误，直接返回 
        return 0.0;
        
    else if(now.value != MAX) //若值不为MAX，说明已经计算过，直接返回值即可 
        return now.value;
    else {
        float ans1,ans2 =0;
        
        if( now.ty == "PRINT")
		{
            now.ty = "PRINTED"; //状态修改为“已经打印过” 
            ans1 = calculate(*now.left);
            now.value = ans1;
            cout << "PRINT operator: " << now.left->name << " = " << setprecision(4) << fixed << ans1 << endl;
            return ans1;
        }
        else if(now.ty == "COND")
		{
            float ans = calculate(*now.left); //计算用于判断的参数 
            ans1 = calculate(relation[now.output1]); //计算输出值1 
            ans2 = calculate(relation[now.output2]); //计算输出值2 
            if(ans > 0)
                return ans1;
            return ans2;
        }
        else if( now.ty == "P")
		{
            if(now.value == MAX) //若未赋值，则报错 
			{
                error1 = true;
                return 0.0;
            }
        }
        //分别实现一元运算 
        else if(now.ty == "SIN")
		{
            ans1 = calculate(*now.left);
            now.value = sin(ans1);
            return sin(ans1);
        }
        else if(now.ty == "LOG")
		{
            ans1 = calculate(*now.left);
            if(ans1 > 0){
                now.value = log(ans1);
                return log(ans1);
            }
            else {
                error3 = true;
                return 0.0;
            }
        }
        else if(now.ty == "EXP")
		{
            ans1 = calculate(*now.left);
            now.value = exp(ans1);
            return exp(ans1);
        }
        else if(now.ty == "TANH")
		{
            ans1 = calculate(*now.left);
            now.value = (float)(exp(ans1) - exp(-ans1)) / (exp(ans1) + exp(-ans1));
            return now.value;
        }
        else if(now.ty == "SIGMOID")
		{
            ans1 = calculate(*now.left);
            float x = 1;
            now.value = (x / (x + exp(-ans1)));
            return now.value;
        }
        else if(now.left != nullptr && now.right != nullptr) //此时调用二元运算函数 
		{
            ans1 = calculate(*now.left);
            ans2 = calculate(*now.right);
            now.value = Cal(ans1, ans2, now.ty);
            return now.value;
        }
    }
    return 0.0;
}

void Graph::constructnewrelation(string a, string b, string c, string d) //建立节点之间新关系的函数 
{//a是要赋左右儿子的节点，b是节点类型（计算符号） 
    relation[a] = move(Node(a, b));
    relation[a].left = &relation[c];
    relation[a].right= &relation[d];
}

void Graph::buildgraph(Temp &src)
{
    index2 ++;
    string op = src.arr[2];
    if(op == "SIN" || op == "LOG" || op == "EXP" || op=="SIGMOID" || op=="TANH" || op=="PRINT"){
        if(relation.find(src.arr[0]) != relation.end()) //如果在map里已经存在这个字符串（要覆盖） 
		{
            string old = "OLD" + src.arr[0] + to_string(index2); //给要被覆盖的节点新取的名字 
            
			relation[old] = relation[src.arr[0]]; //老节点新名字的指针指向被覆盖的节点（节点仍然存在） 
            for(auto iter = relation.begin(); iter != relation.end(); iter++)
			{
				//指针位置搬家 
                if(iter->second.left == &relation[src.arr[0]])
				{
                    iter->second.left = &relation[old];
                }
                if(iter->second.right == &relation[src.arr[0]])
				{
                    iter->second.right = &relation[old];
                }
                if(iter->second.output1 == src.arr[0])
				{
                    iter->second.output1 = old;
                }
                if(iter->second.output2 == src.arr[0])
				{
                    iter->second.output2 = old;
                }
            }
            if(src.arr[0] == src.arr[3]) //针对一元运算符覆盖的操作 
			{
                relation[src.arr[0]] = move(Node(src.arr[0], src.arr[2]));
                relation[src.arr[0]].left = &relation[old];
            }
            else {
                relation[src.arr[0]] = move(Node(src.arr[0], src.arr[2]));
                relation[src.arr[0]].left = &relation[src.arr[3]];
            }
        }
        else {
            relation[src.arr[0]] = move(Node(src.arr[0],src.arr[2]));
            relation[src.arr[0]].left = &relation[src.arr[3]];
        }
    }
    else if(op == "COND")
	{
        if(relation.find(src.arr[0]) != relation.end()) //如果在map里已经存在这个字符串（要覆盖）
		{
            string old = "OLD" + src.arr[0] + to_string(index2);
            relation[old] = relation[src.arr[0]]; //老节点新名字的指针指向被覆盖的节点（节点仍然存在）
            for(auto iter = relation.begin(); iter != relation.end(); iter++)
			{
				//指针位置搬家 
                if(iter->second.left == &relation[src.arr[0]])
				{
                    iter->second.left = &relation[old];
                }
                if(iter->second.right == &relation[src.arr[0]])
				{
                    iter->second.right = &relation[old];
                }
                if(iter->second.output1 == src.arr[0])
				{
                    iter->second.output1 = old;
                }
                if(iter->second.output2 == src.arr[0])
				{
                    iter->second.output2 = old;
                }
            }
            
            //原来名字在覆盖后的新节点 
            relation[src.arr[0]] = move(Node(src.arr[0], src.arr[2]));
            if(src.arr[3] == src.arr[0]) //这是判断参数重名的情况 
			{
                relation[src.arr[0]].left = &relation[old];
            }
            else {
                relation[src.arr[0]].left = &relation[src.arr[3]];
            }
            if(src.arr[4] == src.arr[0]) //这是第一个输出参数重名的情况 
			{
                relation[src.arr[0]].output1 = old;
            }
            else {
                relation[src.arr[0]].output1 = src.arr[4];
            }
            if(src.arr[5] == src.arr[0]) //这是第一个输出参数重名的情况
			{
                relation[src.arr[0]].output2 = old;
            }
            else {
                relation[src.arr[0]].output2 = src.arr[5];
            }
            if(src.arr[3] != src.arr[0] && src.arr[4] != src.arr[0] && src.arr[5] != src.arr[0]) //未出现覆盖的情况 
			{
                relation[src.arr[0]].left = &relation[src.arr[3]];
                relation[src.arr[0]].output1 = src.arr[4];
                relation[src.arr[0]].output2 = src.arr[5];
            }
        }
        else { //若未出现这个名字，即全新的节点 
            relation[src.arr[0]] = move(Node(src.arr[0],src.arr[2]));
            relation[src.arr[0]].left = &relation[src.arr[3]];
            relation[src.arr[0]].output1 = src.arr[4];
            relation[src.arr[0]].output2 = src.arr[5];
        }
    }
    else if(relation.find(src.arr[0]) != relation.end()) //针对二元运算的重名情况 
	{
        string old = "OLD" + src.arr[0] + to_string(index2);
        relation[old] = relation[src.arr[0]]; //老节点新名字的指针指向被覆盖的节点（节点仍然存在）
        for(auto iter = relation.begin(); iter != relation.end(); iter++)
		{
			//指针位置搬家 
            if(iter->second.left == &relation[src.arr[0]])
			{
                iter->second.left = &relation[old];
            }
            if(iter->second.right == &relation[src.arr[0]])
			{
                iter->second.right = &relation[old];
            }
            if(iter->second.output1 == src.arr[0])
			{
                iter->second.output1 = old;
            }
            if(iter->second.output2 == src.arr[0])
			{
                iter->second.output2 = old;
            }
        }
        
        relation[src.arr[0]] = move(Node(src.arr[0],src.arr[3]));
        if(src.arr[0] == src.arr[2]) //二元运算的第一个参数重名 
		{
            relation[src.arr[0]].left = &relation[old];
            relation[src.arr[0]].right = &relation[src.arr[4]];
        }
        else if(src.arr[0] == src.arr[4]) //二元运算的第二个参数重名 
		{
            relation[src.arr[0]].right = &relation[old];
            relation[src.arr[0]].left = &relation[src.arr[2]];
        }
		else if(src.arr[0] == src.arr[4] && src.arr[0] == src.arr[4]) //二者均重名 
		{
            relation[src.arr[0]].right = &relation[old];
            relation[src.arr[0]].left = &relation[old];
        }
        else { //二者均不重名 
            relation[src.arr[0]].left = &relation[src.arr[2]];
            relation[src.arr[0]].right = &relation[src.arr[4]];
        }
    }
    else { //若无重名与覆盖，直接创建新关系 
        constructnewrelation(src.arr[0],src.arr[3],src.arr[2],src.arr[4]);
    }
}

Graph::~Graph() //析构函数 
{
    relation.clear();
}
