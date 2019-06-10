#include <iostream>
#include "Tensor.h"

int main() {
	char x = 'c';
	while (x != 'e') {
		int m1, n1, m2, n2;
		std::cin >> m1 >> n1 >> m2 >> n2;
		std::vector<std::vector<float>> A;
		std::vector<std::vector<float>> B;
		for (int i = 1; i <= m1; i++) {
			std::vector<float> temp;
			for (int i = 1; i <= n1; i++) {
				float tempint;
				std::cin >> tempint;
				temp.push_back(tempint);
			}
			A.push_back(temp);
			temp.clear();
		}
		for (int i = 1; i <= m2; i++) {
			std::vector<float> temp;
			for (int i = 1; i <= n2; i++) {
				float tempint;
				std::cin >> tempint;
				temp.push_back(tempint);
			}
			B.push_back(temp);
			temp.clear();
		}
		Tensor a(A);
		a.Print();
		Tensor b(B);
		b.Print();
		Tensor c;
		c = a * b;
		c.Print();



		x = getchar();

	}
	return 0;

}