
main: 
	g++ -c src/Opt.cpp -o Opt.o -std=c++11 -O2
	g++ -c src/Graph.cpp -o Graph.o -std=c++11 -O2
	g++ -c src/Session.cpp -o Session.o -std=c++11 -O2
	g++ main.cpp Opt.o Graph.o Session.o -o main -std=c++11 -O2
	rm Opt.o Graph.o Session.o

debug: 
	g++ -c src/Opt.cpp -o Opt.o -std=c++11 -O2 -DLOG
	g++ -c src/Graph.cpp -o Graph.o -std=c++11 -O2 -DLOG
	g++ -c src/Session.cpp -o Session.o -std=c++11 -O2 -DLOG
	g++ main.cpp Opt.o Graph.o Session.o -o main -std=c++11 -O2 -DLOG
	rm Opt.o Graph.o Session.o
