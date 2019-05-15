
// class Opt:
// ����
// �������������(����PlaceHolder��)����̳� Opt ��
// ��ʵ������� 1.���캯�� 2.run_self()��ʾ�ýڵ�ļ������ 

class Opt {
public:
	string type;      // Opt ���� �� "Add" "Cond" 
	string name;      // Opt ���� 
	vector<Opt*> pre; // ��¼������ Opt�����������ڸ� Opt ����� Opt 
	vector<Opt*> suc; // ��¼�� Opt ֱ��Ӱ�쵽����Щ�ڵ�, ��run()�лᶯ̬�ı� 
	Graph* graph;     // ��¼�� Opt ��������ͼ 
	
	int time_cnt;     // ʱ��� 
	float data;       // �������� 
	
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
	virtual float run_self() {  //  Opt ���಻Ӧ����ֵ 
		graph -> Error("Run NoneType opt");
	}
	void run();
};

// ˫Ŀ����� ���� 

#define BinaryOptClass(OptType)\
class OptType: public Opt {\
public:\
	OptType(Graph*, Opt*, Opt*);\
	float run_self();\
}

// ʹ�ú궨��������
// �Լ򻯴������ǿ�ɶ���
// BinaryOptClass(Add) �ȼ��� 
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

// ��Ŀ����� ���� 

UnaryOptClass(Sin);
UnaryOptClass(Log);
UnaryOptClass(Exp);
UnaryOptClass(Tanh);
UnaryOptClass(Sigmoid);
UnaryOptClass(Print);
UnaryOptClass(Assign);

// Cond ���� 

class Cond: public Opt {
public:
	Cond(Graph*, Opt*, Opt*, Opt*);
	float run_self();
};

// ������������ ���� 

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
	// Variable Ӧ���ּ���ͼ�Ķ�̬����
	// ����ʹ Varible ������һ���ɸ��ĵ� Opt* ������һ���ɸ��ĵ���Ҫ����һЩ 
	float run_self();
};

