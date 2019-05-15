
class Graph {
public:
	int time_cnt;            // ���ڱ�֤ opt���ظ����� 
	bool err;                // ��¼�Ƿ���� Error 
	vector<Opt*> opts;       // ��¼���� opt ���ڹ���ʱ�ͷ��ڴ� 
	map<string, Opt*> dict;  // ��¼ opt ��Ӧ�� ����
	#ifdef LOG
	ofstream log;            // ���� 
	#endif
	
	virtual ~Graph();
	Graph() {
		time_cnt = 0;
		#ifdef LOG
		log.open("log.txt");
		#endif
	}
	
	// �½� Opt
	
	Opt* creat_BinaryOpt(string, string, string);
	Opt* creat_UnaryOpt(string, string);
	Opt* creat_CondOpt(string, string, string);
	
	Opt* creat_PlaceHolderOpt();
	Opt* creat_ConstantOpt(float);
	Opt* creat_VariableOpt(float);
	
	// �½���Ϊ name �� Opt, ����ӽ� dict 
	
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

