all: src/*.cpp
	rm *.tab.*
	bison -y -d mini_c.y
	g++ -std=c++11 -Iinclude -I./ src/*.cpp ./y.tab.c -o bin/minic
	./bin/minic ./test2.c

clean:
	rm bin/* -rf
