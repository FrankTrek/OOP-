
class Session {
public:
	Graph* graph;      // ����ͼ 
	vector<float> ans; // ���������� 
	
	virtual ~Session() { delete graph; }
	Session() { graph = new Graph; }
	
	void declare(const string&);
	void code(const string&);
	void run(const string&);
};

