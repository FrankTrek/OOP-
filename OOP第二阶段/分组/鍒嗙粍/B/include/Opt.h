
// class Opt:
// 基类
// 所有其他运算符(包括PlaceHolder等)都需继承 Opt 类
// 并实现自身的 1.构造函数 2.run_self()表示该节点的计算规则 

class Opt {
public:
	string type;      // Opt 类型 如 "Add" "Cond" 
	string name;      // Opt 名字 
	vector<Opt*> pre; // 记录依赖的 Opt，即必须先于该 Opt 计算的 Opt 
	vector<Opt*> suc; // 记录该 Opt 直接影响到了哪些节点, 在run()中会动态改变 
	Graph* graph;     // 记录该 Opt 属于哪张图 
	
	int time_cnt;     // 时间戳 
	float data;       // 计算数据 
	
	virtual ~Opt() {}
	Opt(Graph* _graph) {
		graph = _graph;
		time_cnt = -1; 
		type = "None";
		name = "None_opt";
	}
	
	Opt* rename(string);
	void feed(float);
	float calc(Opt*);
	virtual float run_self() {  //  Opt 基类不应被求值 
		graph -> Error("Run NoneType opt");
	}
	void run();
};

// 双目运算符 声明 

#define BinaryOptClass(OptType)\
class OptType: public Opt {\
public:\
	OptType(Graph*, Opt*, Opt*);\
	float run_self();\
}

// 使用宏定义声明类
// 以简化代码和增强可读性
// BinaryOptClass(Add) 等价于 
// class Add: public Opt {
// public:
//		Add(Graph*, Opt*, Opt*);
//		float run_self();
// }

BinaryOptClass(Add);      // +
BinaryOptClass(Subtract); // -
BinaryOptClass(Multiply); // *
BinaryOptClass(Divide);   // /
BinaryOptClass(BCmp);     // >
BinaryOptClass(BEQCmp);   // >=
BinaryOptClass(LCmp);     // <
BinaryOptClass(LEQCmp);   // <=
BinaryOptClass(EQCmp);    // ==
BinaryOptClass(NEQCmp);   // !=

#define UnaryOptClass(OptType)\
class OptType: public Opt {\
public:\
	OptType(Graph*, Opt*);\
	float run_self();\
}

// 单目运算符 声明 

UnaryOptClass(Sin);
UnaryOptClass(Log);
UnaryOptClass(Exp);
UnaryOptClass(Tanh);
UnaryOptClass(Sigmoid);
UnaryOptClass(Print);
UnaryOptClass(Assign);

// Cond 声明 

class Cond: public Opt {
public:
	Cond(Graph*, Opt*, Opt*, Opt*);
	float run_self();
};

// 三种数据类型 声明 

class PlaceHolder: public Opt {
public:
	PlaceHolder(Graph*);
	float run_self();
};

class Constant: public Opt {
public:
	Constant(Graph*, float);
	float run_self();
};

class Variable: public Opt {
public:
	Variable(Graph*, Opt*);
	// Variable 应体现计算图的动态特性
	// 所以使 Varible 依赖于一个可更改的 Opt* 而不是一个可更改的数要合理一些 
	float run_self();
};

