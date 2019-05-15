#include "../tt.h"

Graph::~Graph() {
	for(Opt* opt: opts) {
		#ifdef LOG 
		log << "Del: " << (opt -> name) << " " << (opt -> type) << endl;
		#endif
		delete opt;  // 释放内存 
	}
}

Opt* Graph::creat_BinaryOpt(string type, string a, string b) {
	Opt* a_opt = dict[a];
	Opt* b_opt = dict[b];
	Opt* Binary_opt = type == "+"  ? new Add(this, a_opt, b_opt)      :
					  type == "-"  ? new Subtract(this, a_opt, b_opt) :
					  type == "*"  ? new Multiply(this, a_opt, b_opt) :
					  type == "/"  ? new Divide(this, a_opt, b_opt)   :
					  type == ">"  ? new BCmp(this, a_opt, b_opt)     :
					  type == ">=" ? new BEQCmp(this, a_opt, b_opt)   :
					  type == "<"  ? new LCmp(this, a_opt, b_opt)     :
					  type == "<=" ? new LEQCmp(this, a_opt, b_opt)   :
					  type == "==" ? new EQCmp(this, a_opt, b_opt)    :
					  type == "!=" ? new NEQCmp(this, a_opt, b_opt)   :
					  new Opt(this);
	opts.push_back(Binary_opt);
	return Binary_opt;
}

Opt* Graph::creat_UnaryOpt(string type, string a) {
	Opt* a_opt = dict[a];
	Opt* Unary_opt = type == "SIN"     ? new Sin(this, a_opt)     :
					 type == "LOG"     ? new Log(this, a_opt)     :
					 type == "EXP"     ? new Exp(this, a_opt)     :
					 type == "TANH"    ? new Tanh(this, a_opt)    :
					 type == "SIGMOID" ? new Sigmoid(this, a_opt) :
					 type == "PRINT"   ? new Print(this, a_opt)   :
					 new Opt(this);
	opts.push_back(Unary_opt);
	return Unary_opt;
}

Opt* Graph::creat_CondOpt(string condition, string a, string b) {
	Opt* a_opt = dict[a];
	Opt* b_opt = dict[b];
	Opt* condition_opt = dict[condition];
	Opt* Cond_opt = new Cond(this, condition_opt, a_opt, b_opt);
	opts.push_back(Cond_opt);
	return Cond_opt;
}

Opt* Graph::creat_PlaceHolderOpt() {
	Opt* PlaceHolder_opt = new PlaceHolder(this);
	opts.push_back(PlaceHolder_opt);
	return PlaceHolder_opt;
}

Opt* Graph::creat_ConstantOpt(float data) {
	Opt* Constant_opt = new Constant(this, data);
	opts.push_back(Constant_opt);
	return Constant_opt;
}

Opt* Graph::creat_VariableOpt(float data) {
	Opt* Constant_opt = creat_ConstantOpt(data); 
	Opt* Variable_opt = new Variable(this, Constant_opt);
	opts.push_back(Variable_opt);
	return Variable_opt;
}

void Graph::new_Binary(string name, string type, string a, string b) {
	#ifdef LOG
	log << "New_Binary: " << name << " " << type << " " << a << " " << b << endl;
	#endif
	dict[name] = creat_BinaryOpt(type, a, b) -> rename(name);
}

void Graph::new_Unary(string name, string type, string a) {
	#ifdef LOG
	log << "New_Unary: " << name << " " << type << " " << a << endl;
	#endif
	dict[name] = creat_UnaryOpt(type, a) -> rename(name);
	if(type == "PRINT")
		dict[name] -> rename(a);
}

void Graph::new_Cond(string name, string condition, string a, string b) {
	#ifdef LOG
	log << "New_Cond: " << name << " (" << condition << ")" << " " << a << " " << b << endl;
	#endif
	dict[name] = creat_CondOpt(condition, a, b) -> rename(name);
}

void Graph::new_PlaceHolder(string name) {
	#ifdef LOG
	log << "New_PlaceHolder" << " " << name << endl;
	#endif
	dict[name] = creat_PlaceHolderOpt() -> rename(name);
}

void Graph::new_Constant(string name, float data) {
	#ifdef LOG
	log << "New_Constant" << " " << name << endl;
	#endif
	dict[name] = creat_ConstantOpt(data) -> rename(name);
}

void Graph::new_Variable(string name, float data) {
	#ifdef LOG
	log << "New_Variable" << " " << name << endl;
	#endif
	dict[name] = creat_VariableOpt(data) -> rename(name);
}

void Graph::set_Variable(string x, float data) {
	Opt* x_opt = dict[x];
	if(x_opt -> type != "Variable") {
		Error("SET input must Variable.");
	}
	Opt* Constant_opt = new Constant(this, data);
	opts.push_back(Constant_opt);
	x_opt -> pre[0] = Constant_opt;
}

// 清空所有节点，实现上只需将时间戳 time_cnt + 1 

void Graph::clean() {
	time_cnt += 1;
}

void Graph::Error(string ErrLog) {
	err = true;
	printf("ERROR: %s\n", ErrLog.c_str());
}

