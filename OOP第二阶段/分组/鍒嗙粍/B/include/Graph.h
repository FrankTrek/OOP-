
class Graph {
public:
	int time_cnt;            // 用于保证 opt不重复计算 
	bool err;                // 记录是否产生 Error 
	vector<Opt*> opts;       // 记录所有 opt 用于构析时释放内存 
	map<string, Opt*> dict;  // 记录 opt 对应的 名称
	#ifdef LOG
	ofstream log;            // 调试 
	#endif
	
	virtual ~Graph();
	Graph() {
		time_cnt = 0;
		#ifdef LOG
		log.open("log.txt");
		#endif
	}
	
	// 新建 Opt
	
	Opt* creat_BinaryOpt(string, string, string);
	Opt* creat_UnaryOpt(string, string);
	Opt* creat_CondOpt(string, string, string);
	
	Opt* creat_PlaceHolderOpt();
	Opt* creat_ConstantOpt(float);
	Opt* creat_VariableOpt(float);
	
	// 新建名为 name 的 Opt, 并添加进 dict 
	
	void new_Binary(string, string, string, string);
	void new_Unary(string, string, string);
	void new_Cond(string, string, string, string);
	
	void new_PlaceHolder(string);
	void new_Constant(string, float);
	void new_Variable(string, float);
	
	void set_Variable(string, float);
	
	void clean();
	void Error(string);
};

