example:
	c++ example.cpp -std=c++11 -o example.o

test:
	c++ test.cpp -std=c++11 -o test.o
	./test.o

clean:
	rm *.o