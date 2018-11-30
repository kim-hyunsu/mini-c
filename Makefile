all: src/main.cpp src/prompt.cpp
	g++ src/main.cpp src/prompt.cpp -o bin/minic
	./bin/minic

clean:
	rm bin/* -rf
