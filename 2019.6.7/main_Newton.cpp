#include "Newton.h"
#include "Operator.h"
#include "NewtonWrapper.h"
#include "Scalar.h"
#include "Node.h"

int main() {
	int nn;
	std::cin >> nn;
	NewtonWrapper a(nn);
	a.NewtonMathod();
	return 0;

}