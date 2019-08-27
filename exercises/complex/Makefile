CXXFLAGS = --std=c++11 -I../include

test : complex.o test.o
	$(CXX) $^ -o $@

run : test
	./test

clean :
	rm -rf *.o test
