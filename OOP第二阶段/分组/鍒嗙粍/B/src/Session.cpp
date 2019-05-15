#include "../tt.h"


void Session::declare(const string& input) {
	istringstream in(input);
	string name;
	char type;
	float data = 0.0;
	
	in >> name >> type;
	
	if(type == 'C' or type == 'V') {
		in >> data;
	}
	if(type == 'P') graph -> new_PlaceHolder(name);    // �½� PlaceHolder 
	if(type == 'C') graph -> new_Constant(name, data); // �½� Constant 
	if(type == 'V') graph -> new_Variable(name, data); // �½� Variable 
}

void Session::code(const string& input) {
	istringstream in(input);
	string name, opt, a, b, c;
	char eq;
	
	in >> name >> eq;
	in >> opt;
	
	if(opt == "COND") {
		in >> a >> b >> c;
		graph -> new_Cond(name, a, b, c);  // �½� Cond ����� 
	}
	else if(opt == "SIN" or opt == "LOG" or opt == "TANH" or
			opt == "EXP" or opt == "SIGMOID" or opt == "PRINT") {
		in >> a;
		graph -> new_Unary(name, opt, a);  // �½���Ŀ����� 
	}
	else {
		a = opt;
		in >> opt >> b;
		graph -> new_Binary(name, opt, a, b);  //  �½�˫Ŀ����� 
	}
}

void Session::run(const string& input) {
	graph -> clean();
	graph -> err = false;
	
	istringstream in(input);
	string opt, name;
	in >> opt >> name;
	if(opt == "EVAL") {
		int feed_dict_num = 0;
		string feed_name;
		float feed_data;
		in >> feed_dict_num;
		for(int i = 0; i < feed_dict_num; i ++) {
			in >> feed_name >> feed_data;
			graph -> dict[feed_name] -> feed(feed_data);
		}
		Opt* target = graph -> dict[name];
		target -> run();  // ����Ŀ�� Opt 
		if(not graph -> err)
			printf("%.4f\n", target -> data);
		ans.push_back(target -> data);  // �洢������ 
	}
	if(opt == "SETCONSTANT") {
		float data;
		in >> data;
		graph -> set_Variable(name, data);
		ans.push_back(0.0);
	}
	if(opt == "SETANSWER") {
		int idx;
		in >> idx;
		float data = ans[idx - 1];
		graph -> set_Variable(name, data);
		ans.push_back(0.0);
	}
}

