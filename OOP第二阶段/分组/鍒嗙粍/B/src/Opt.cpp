#include "../tt.h"
#include <cmath>

#define CHECK_ERROR_FLOAT if(graph -> err) return 0.0
#define CHECK_ERROR_VOID if(graph -> err) return
#define STR(OptType) #OptType

// CHECK_ERROR_FLOAT && CHECK_ERROR_VOID
// ����ȷ�� Error ����ʱ����ἴʱֹͣ 

// class Opt ʵ�� 

Opt* Opt::rename(string new_name) {
	name = new_name;
	return this;
}

// Opt::feed: Placeholder ��ֵ 

void Opt::feed(float _data) {
	time_cnt = graph -> time_cnt;
	data = _data;
	suc.clear();
}

// Opt::calc: ����ĳһ�������ڵ��ֵ������Ѿ��������ֱ�ӷ���

float Opt::calc(Opt* opt) {
	CHECK_ERROR_FLOAT;
	if(opt -> time_cnt != graph -> time_cnt) {
		opt -> run();
	}
	CHECK_ERROR_FLOAT;
	opt -> suc.push_back(this);
	
	if(type == "Divide") {
		if(opt -> data == 0.0 and opt == pre[1])
			graph -> Error("Division by zero");
	}
	else if(type == "Log") {
		if(opt -> data <= 0.0)
			graph -> Error("LOG operator's input must be positive");
	}
	
	CHECK_ERROR_FLOAT;
	return opt -> data;
}

// Opt::run: ����ýڵ������������ڵ� 

void Opt::run() {
	if(time_cnt == graph -> time_cnt) return;
	CHECK_ERROR_VOID;
	suc.clear();
	data = run_self();
	CHECK_ERROR_VOID;
	time_cnt = graph -> time_cnt;
	#ifdef LOG
	graph -> log << type << endl;
	#endif
}

// ˫Ŀ����� ʵ�� 

#define BinaryOptClassImpl(OptType, _opt_)\
OptType::OptType(Graph* _graph, Opt* a, Opt* b): Opt(_graph) {\
	type = STR(OptType);\
	name = "_" + type;\
	pre.push_back(a);\
	pre.push_back(b);\
}\
float OptType::run_self() {\
	float a = calc(pre[0]);\
	CHECK_ERROR_FLOAT;\
	float b = calc(pre[1]);\
	CHECK_ERROR_FLOAT;\
	return a _opt_ b;\
}

// ʹ�ú궨��ʵ���� 
// �Լ򻯴������ǿ�ɶ���
// BinaryOptClassImpl(Add, +) �ȼ���
// Add::OptType(Graph* _graph, Opt* a, Opt* b): Opt(_graph) {
//	type = "Add";
//	name = "_" + type;
//	pre.push_back(a);
//	pre.push_back(b);
// }
// float Add::run_self() {
//	float a = calc(pre[0]);
//	CHECK_ERROR_FLOAT;
//	float b = calc(pre[1]);
//	CHECK_ERROR_FLOAT;
//	return a + b;
// }

BinaryOptClassImpl(Add,      +);
BinaryOptClassImpl(Subtract, -);
BinaryOptClassImpl(Multiply, *);
BinaryOptClassImpl(Divide,   /);
BinaryOptClassImpl(BCmp,     >);
BinaryOptClassImpl(BEQCmp,   >=);
BinaryOptClassImpl(LCmp,     <);
BinaryOptClassImpl(LEQCmp,   <=);
BinaryOptClassImpl(EQCmp,    ==);
BinaryOptClassImpl(NEQCmp,   !=);


// ��Ŀ����� ʵ�� 

#define UnaryOptClassImpl(OptType, _func_)\
OptType::OptType(Graph* _graph, Opt* a): Opt(_graph) {\
	type = STR(OptType);\
	name = "_" + type;\
	pre.push_back(a);\
}\
float OptType::run_self() {\
	float a = calc(pre[0]);\
	CHECK_ERROR_FLOAT;\
	return _func_;\
}

UnaryOptClassImpl(Sin,  sin(a));
UnaryOptClassImpl(Log,  log(a));
UnaryOptClassImpl(Exp,  exp(a));
UnaryOptClassImpl(Tanh, tanh(a));
UnaryOptClassImpl(Sigmoid, 1 / (1 + exp(-a)));
UnaryOptClassImpl(Assign, a);
UnaryOptClassImpl(Print, (printf("Print Operator: %s = %.4f\n", name.c_str(), a), a));

// Cond ����� ʵ��
// cond z x y �У���� z > 0�������� x 

Cond::Cond(Graph* _graph, Opt* condition, Opt* a, Opt* b): Opt(_graph) {
	type = "Cond";
	name = "_" + type;
	pre.push_back(condition);
	pre.push_back(a);
	pre.push_back(b);
}
float Cond::run_self() {
	float condition = calc(pre[0]);
	CHECK_ERROR_FLOAT;
	if(condition > 0.0) {
		float a = calc(pre[1]);
		CHECK_ERROR_FLOAT;
		return a;
	}
	else {
		float b = calc(pre[2]);
		CHECK_ERROR_FLOAT;
		return b;
	}
}

// ������������ ʵ��:

PlaceHolder::PlaceHolder(Graph* _graph): Opt(_graph) { type = "PlaceHolder"; }
float PlaceHolder::run_self() {
	graph -> Error("Placeholder missing"); 
	// PlaceHolder Ӧ�ñ���ֵ, ͬʱ��ı�time_cnt, run_self��Ӧ�ñ�ִ�е� 
	CHECK_ERROR_FLOAT;
}

Constant::Constant(Graph* _graph, float _data): Opt(_graph) { type = "Constant"; data = _data; }
float Constant::run_self() {
	return data;
}

Variable::Variable(Graph* _graph, Opt* opt): Opt(_graph) { type = "Variable"; pre.push_back(opt); }
float Variable::run_self() {
	float a = calc(pre[0]);
	CHECK_ERROR_FLOAT;
	return a;
}

