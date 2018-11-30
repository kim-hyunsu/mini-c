all: src/main.cpp src/prompt.cpp src/parser.cpp
	g++ src/main.cpp src/prompt.cpp src/parser.cpp -o bin/minic
	./bin/minic

clean:
	rm bin/* -rf
