#include <iostream>
#include <cstring>
#include <sstream>
#include <vector>
#include "tt.h"

using namespace std;

int main() {
	Session sess;
	int n, m, q;
	string input;

	#ifdef LOG
	sess.graph -> log << "DECLARE:" << endl;
	#endif
	
	cin >> n;
	getline(cin, input);
	while(n --) {
		getline(cin, input);
		sess.declare(input);
		#ifdef LOG
		sess.graph -> log << "-----------" << endl;
		#endif
	}

	#ifdef LOG
	sess.graph -> log << "CODE:" << endl;
	#endif
	
	cin >> m;
	getline(cin, input);
	while(m --) {
		getline(cin, input);
		sess.code(input);
		#ifdef LOG
		sess.graph -> log << "-----------" << endl;
		#endif
	}

	#ifdef LOG
	sess.graph -> log << "RUN:" << endl;
	#endif
	
	cin >> q;
	getline(cin, input);
	while(q --) {
		getline(cin, input);
		sess.run(input);
		#ifdef LOG
		sess.graph -> log << "-----------" << endl;
		#endif
	}
	
	return 0;
}

