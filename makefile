example:
	c++ example.cpp -std=c++11 -o example.o

.PHONY: test

test: test.cpp hqvec.hpp hqmat.hpp
	c++ test.cpp -std=c++11 -o test.o
	./test.o

clean:
	rm *.o