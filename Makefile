run: compile
	./main
raw: compile
	rm -f raw/*
	./main r
test: compile
	./main t
benchmark: compile
	rm -f raw/*
	./main b
compile: src/main.cpp
	g++ -O2 -Wall -std=c++11 src/main.cpp -o main
