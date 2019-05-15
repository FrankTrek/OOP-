
class Session {
public:
	Graph* graph;      // 计算图 
	vector<float> ans; // 保存运算结果 
	
	virtual ~Session() { delete graph; }
	Session() { graph = new Graph; }
	
	void declare(const string&);
	void code(const string&);
	void run(const string&);
};

