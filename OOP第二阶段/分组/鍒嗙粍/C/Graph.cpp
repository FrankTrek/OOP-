#include "Graph.h"

Graph::Graph()
{
	//����ͼ����ʼ���������� 
    error1 = false;
    error2 = false;
    error3 = false;
    index = 0;
    index2 = 0;
}

void Graph::NodeConstruct(string type, string _name, float v) //����������ڵ� 
{
    Node buf;
    
    if(type == "Constant")
        buf = move(Constant(_name, v));
    else if(type == "Placeholder")
        buf = move(Placeholder(_name, v));
    else if(type == "Variable")
        buf = move(Variable(_name, v));
    
	relation[_name] = buf; //���ַ�����ڵ�Ķ�Ӧ��ϵ����map�� 
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
    
    string dst = src.arr[1]; //��������Ҫ�ó�����Ķ��������0��ʼ�� 
    
    float answer;
    
    if(relation[dst].ty == "C") //������ֱ����� 
	{
        cout << setprecision(4) << fixed << relation[dst].value << endl;
        return;
    }
    if(len == 1) //��Ϊ����Ҫ�κ�����������ֱ�Ӹ�ֵ 
	{
        answer = calculate(relation[dst]);
    }
    else {
        int count = stoi(src.arr[2]); //��ֵ�Ե���Ŀ 
        int idx = 3; //��ʼ����ʱ��λ�� 
        for(int i = 0; i < count; i++) //��ʼ����Ҫ��δ��ֵ�ڵ㸳ֵ 
		{
            relation[src.arr[idx]].value = stof(src.arr[idx+1]);
            idx += 2;
        }
        answer = calculate(relation[dst]);
    }
    
    //���д��󣬱���������� 
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
    
	reset(); //ÿ�����������¸��м�ڵ㸳ֵ 
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
            if(iter->second.ty == "PRINTED") //�Ѿ�������ĸĻ�ԭ�� 
                iter->second.ty = "PRINT";
            iter->second.value = MAX; //value��ԭ 
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

float Graph::Cal(float ans1, float ans2, string option) //ֻ��Զ�Ԫ����ļ��㺯���������Ƚϣ� 
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

float Graph::calculate(Node &now) //�������㺯�� 
{
	
    if(error1 || error2 || error3) //����д���ֱ�ӷ��� 
        return 0.0;
        
    else if(now.value != MAX) //��ֵ��ΪMAX��˵���Ѿ��������ֱ�ӷ���ֵ���� 
        return now.value;
    else {
        float ans1,ans2 =0;
        
        if( now.ty == "PRINT")
		{
            now.ty = "PRINTED"; //״̬�޸�Ϊ���Ѿ���ӡ���� 
            ans1 = calculate(*now.left);
            now.value = ans1;
            cout << "PRINT operator: " << now.left->name << " = " << setprecision(4) << fixed << ans1 << endl;
            return ans1;
        }
        else if(now.ty == "COND")
		{
            float ans = calculate(*now.left); //���������жϵĲ��� 
            ans1 = calculate(relation[now.output1]); //�������ֵ1 
            ans2 = calculate(relation[now.output2]); //�������ֵ2 
            if(ans > 0)
                return ans1;
            return ans2;
        }
        else if( now.ty == "P")
		{
            if(now.value == MAX) //��δ��ֵ���򱨴� 
			{
                error1 = true;
                return 0.0;
            }
        }
        //�ֱ�ʵ��һԪ���� 
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
        else if(now.left != nullptr && now.right != nullptr) //��ʱ���ö�Ԫ���㺯�� 
		{
            ans1 = calculate(*now.left);
            ans2 = calculate(*now.right);
            now.value = Cal(ans1, ans2, now.ty);
            return now.value;
        }
    }
    return 0.0;
}

void Graph::constructnewrelation(string a, string b, string c, string d) //�����ڵ�֮���¹�ϵ�ĺ��� 
{//a��Ҫ�����Ҷ��ӵĽڵ㣬b�ǽڵ����ͣ�������ţ� 
    relation[a] = move(Node(a, b));
    relation[a].left = &relation[c];
    relation[a].right= &relation[d];
}

void Graph::buildgraph(Temp &src)
{
    index2 ++;
    string op = src.arr[2];
    if(op == "SIN" || op == "LOG" || op == "EXP" || op=="SIGMOID" || op=="TANH" || op=="PRINT"){
        if(relation.find(src.arr[0]) != relation.end()) //�����map���Ѿ���������ַ�����Ҫ���ǣ� 
		{
            string old = "OLD" + src.arr[0] + to_string(index2); //��Ҫ�����ǵĽڵ���ȡ������ 
            
			relation[old] = relation[src.arr[0]]; //�Ͻڵ������ֵ�ָ��ָ�򱻸��ǵĽڵ㣨�ڵ���Ȼ���ڣ� 
            for(auto iter = relation.begin(); iter != relation.end(); iter++)
			{
				//ָ��λ�ð�� 
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
            if(src.arr[0] == src.arr[3]) //���һԪ��������ǵĲ��� 
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
        if(relation.find(src.arr[0]) != relation.end()) //�����map���Ѿ���������ַ�����Ҫ���ǣ�
		{
            string old = "OLD" + src.arr[0] + to_string(index2);
            relation[old] = relation[src.arr[0]]; //�Ͻڵ������ֵ�ָ��ָ�򱻸��ǵĽڵ㣨�ڵ���Ȼ���ڣ�
            for(auto iter = relation.begin(); iter != relation.end(); iter++)
			{
				//ָ��λ�ð�� 
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
            
            //ԭ�������ڸ��Ǻ���½ڵ� 
            relation[src.arr[0]] = move(Node(src.arr[0], src.arr[2]));
            if(src.arr[3] == src.arr[0]) //�����жϲ������������ 
			{
                relation[src.arr[0]].left = &relation[old];
            }
            else {
                relation[src.arr[0]].left = &relation[src.arr[3]];
            }
            if(src.arr[4] == src.arr[0]) //���ǵ�һ������������������ 
			{
                relation[src.arr[0]].output1 = old;
            }
            else {
                relation[src.arr[0]].output1 = src.arr[4];
            }
            if(src.arr[5] == src.arr[0]) //���ǵ�һ������������������
			{
                relation[src.arr[0]].output2 = old;
            }
            else {
                relation[src.arr[0]].output2 = src.arr[5];
            }
            if(src.arr[3] != src.arr[0] && src.arr[4] != src.arr[0] && src.arr[5] != src.arr[0]) //δ���ָ��ǵ���� 
			{
                relation[src.arr[0]].left = &relation[src.arr[3]];
                relation[src.arr[0]].output1 = src.arr[4];
                relation[src.arr[0]].output2 = src.arr[5];
            }
        }
        else { //��δ����������֣���ȫ�µĽڵ� 
            relation[src.arr[0]] = move(Node(src.arr[0],src.arr[2]));
            relation[src.arr[0]].left = &relation[src.arr[3]];
            relation[src.arr[0]].output1 = src.arr[4];
            relation[src.arr[0]].output2 = src.arr[5];
        }
    }
    else if(relation.find(src.arr[0]) != relation.end()) //��Զ�Ԫ������������ 
	{
        string old = "OLD" + src.arr[0] + to_string(index2);
        relation[old] = relation[src.arr[0]]; //�Ͻڵ������ֵ�ָ��ָ�򱻸��ǵĽڵ㣨�ڵ���Ȼ���ڣ�
        for(auto iter = relation.begin(); iter != relation.end(); iter++)
		{
			//ָ��λ�ð�� 
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
        if(src.arr[0] == src.arr[2]) //��Ԫ����ĵ�һ���������� 
		{
            relation[src.arr[0]].left = &relation[old];
            relation[src.arr[0]].right = &relation[src.arr[4]];
        }
        else if(src.arr[0] == src.arr[4]) //��Ԫ����ĵڶ����������� 
		{
            relation[src.arr[0]].right = &relation[old];
            relation[src.arr[0]].left = &relation[src.arr[2]];
        }
		else if(src.arr[0] == src.arr[4] && src.arr[0] == src.arr[4]) //���߾����� 
		{
            relation[src.arr[0]].right = &relation[old];
            relation[src.arr[0]].left = &relation[old];
        }
        else { //���߾������� 
            relation[src.arr[0]].left = &relation[src.arr[2]];
            relation[src.arr[0]].right = &relation[src.arr[4]];
        }
    }
    else { //���������븲�ǣ�ֱ�Ӵ����¹�ϵ 
        constructnewrelation(src.arr[0],src.arr[3],src.arr[2],src.arr[4]);
    }
}

Graph::~Graph() //�������� 
{
    relation.clear();
}
