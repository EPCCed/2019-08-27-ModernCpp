CXXFLAGS = --std=c++17
CC = $(CXX)

exes = dyn1 dyn2 dyn3 shared file
all : $(exes)

clean :
	rm -rf *.o $(exes)
dyn1 : dyn1.o
dyn2 : dyn2.o
dyn3 : dyn3.o
shared : shared.o
file : file.o

