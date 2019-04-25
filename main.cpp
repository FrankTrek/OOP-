#include <iostream>
#include <sstream>
#include "Set_Graph.h"
using namespace Computational_Graph ;
using std::stringstream ;
using std::cin ;  
using std::cout ; 
int N1,N2,N3;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
	
	//Stage 1;
	string s0 ;
	getline(cin,s0) ;
	std::stringstream ss0(s0) ;
	ss0 >> N1; 
	ss0.str("") ;
	ss0.clear() ;

	Set_Graph GRAPH ;
	
	//STAGE1 
	for(int i = 1; i <= N1 ; i++ ){
			string s ;
			vector<string>Input1 ;
			getline(cin,s) ;
			std::stringstream ss(s) ;
			string x ;
			while(ss >> x){
				Input1.push_back(x) ;
//				cout << x ;
			}
			ss.str("") ;
			ss.clear() ; 
		GRAPH.Input_info(std::move(Input1));
//		GRAPH.print_debug() ;
		GRAPH.Initalize_PVC() ;
			
	}
	
	//STAGE2
	
	getline(cin,s0) ;
	ss0.str(s0) ;
	ss0 >> N2; 
	ss0.str("") ;
	ss0.clear() ;
	for(int i = 1; i <= N2 ; i++ ){
			string s ;
			vector<string>Input1 ;
			getline(std::cin,s) ;
			std::stringstream ss(s) ;
			string x ;
			while(ss >> x){
				if( x == "=") continue ;
				Input1.push_back(x) ;
//				cout << x ;
			}	
			GRAPH.Input_info(std::move(Input1));
//			GRAPH.print_debug() ;
			GRAPH.Initalize_Op() ;
//			cout << GRAPH.getres() << "\n" ;
		}	
		
	//STAGE3
	getline(cin,s0) ;
	ss0.str(s0) ;
	ss0 >> N3; 
	ss0.str("") ;
	ss0.clear() ;
	for(int i = 1; i <= N3 ;i++ ) {
			string s ;
			vector<string>Input1 ;
			getline(std::cin,s) ;
			std::stringstream ss(s) ;
			string x ;
			while(ss >> x){
				Input1.push_back(x) ;
//				cout << x ;
			}	
			GRAPH.Input_info(std::move(Input1));
//			GRAPH.print_debug() ;
			GRAPH.processing_Stage3();
	}

	return 0;
}
