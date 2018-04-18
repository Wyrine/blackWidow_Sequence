CXX = g++ -std=c++11
CXXFLAGS = -g -Wall
EXECUTABLES = driver
HEADERS = helper.hpp 

all: $(EXECUTABLES)

.PHONY: clean
clean:
	rm -f core $(EXECUTABLES) *.o

.SUFFIXES: .cpp .o
.cpp.o:
	$(CXX) $(CXXFLAGS) -c $*.cpp

driver: *.o $(HEADERS)
	$(CXX) -g -o driver *.o 
