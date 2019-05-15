all: main
	
main: main.o Scalar.o Operator.o ComputationalGraph.o Node.o
	g++ main.o Scalar.o Operator.o ComputationalGraph.o Node.o -o main -std=c++11

main.o:
	g++ -c main.cpp -o main.o -std=c++11

Node.o: Node.cpp Node.h
	g++ -c Node.cpp -o Node.o -std=c++11

Scalar.o: Scalar.cpp Scalar.h
	g++ -c Scalar.cpp -o Scalar.o -std=c++11

Operator.o: Operator.cpp Operator.h
	g++ -c Operator.cpp -o Operator.o -std=c++11

ComputationalGraph.o: ComputationalGraph.cpp ComputationalGraph.h
	g++ -c ComputationalGraph.cpp -o ComputationalGraph.o -std=c++11

clean:
	-rm *.o
	-rm main