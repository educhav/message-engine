run: compile
	./main
compile: src/main.cpp
	g++ -Wall -std=c++11 src/main.cpp -o main
