#include <iostream>
#include "Operator.h"
#include "Scalar.h"
#include "Newton.h"

int main() {

	int nn;
	std::cin >> nn;
	Newton a(nn);
	a.Construct_Stage1();
	a.Construct_Stage2();
	a.Construct_Stage3();
	a.Construct_Stage4();
	a.Method();
}
