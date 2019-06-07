#include "NewtonWrapper.h"

NewtonWrapper::NewtonWrapper(int n) :num(n) {}
void NewtonWrapper::NewtonMathod()
{
	for (int i = 1; i <= num; i++) {
		int temp;
		std::cin >> temp;;
		Newton a(temp);
		a.Construct_Stage1();
		a.Construct_Stage2();
		a.Construct_Stage3();
		a.Construct_Stage4();
		a.Method();
	}
}

NewtonWrapper::~NewtonWrapper(){} 


