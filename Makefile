all: src/*.cpp
	g++ -Iinclude src/*.cpp -o bin/minic
	./bin/minic

clean:
	rm bin/* -rf
