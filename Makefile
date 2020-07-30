CPP = g++
CFLAGS = -Wall -std=c++17
INCLUDE = ../include/utils.hpp

bin/fppi.exe: src/parser.o src/lexer.o
	$(CPP) $(CFLAGS) -o $@ $^ && make clean

src/%.o: src/%.cpp $(INCLUDE)
	$(CPP) $(CFLAGS) -c $<

.PHONY: clean

clean:
	rm src/*.o