run: compile
	./main
raw: compile
	rm -f raw/*
	./main r
full: compile
	rm -f raw/FULL.txt
	./main f
test: compile
	./main t
benchmark: compile
	rm -f raw/*
	./main b
compile: src/main.cpp
	g++ -O2 -Wall -std=c++11 src/main.cpp -o main
