run: compile
	./main
raw: compile
	./main r
compile: src/main.cpp
	g++ -Wall -std=c++11 src/main.cpp -o main
