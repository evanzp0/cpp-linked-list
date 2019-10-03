CXX=g++
CXX_FLAGS=-Wall -Werror -std=c++17 -g

all: LinkedList.h.gch Node.h.gch
	$(CXX) $(CXX_FLAGS) -o linked-list *.cpp

LinkedList.h.gch: LinkedList.h Node.h
	$(CXX) $(CXX_FLAGS) -c LinkedList.h

Node.h.gch: Node.h
	$(CXX) $(CXX_FLAGS) -c Node.h

test: LinkedList.h.gch Node.h.gch catch-runner.o LinkedList_test.o Node_test.o
	$(CXX) $(CXX_FLAGS) -o test-runner *.o
	./test-runner

test-coverage: clean coverage-flags test
	gcov LinkedList_test.cpp Node_test.cpp 

coverage-flags:
	$(eval CXX_FLAGS+=--coverage -Og)

catch-runner.o: test/catch/catch-runner.cpp test/catch/catch.hpp
	$(CXX) $(CXX_FLAGS) -c test/catch/catch-runner.cpp

LinkedList_test.o: test/LinkedList_test.cpp test/catch/catch.hpp LinkedList.h
	$(CXX) $(CXX_FLAGS) -c test/LinkedList_test.cpp

Node_test.o: test/Node_test.cpp test/catch/catch.hpp Node.h
	$(CXX) $(CXX_FLAGS) -c test/Node_test.cpp

clean:
	rm -f linked-list test-runner *.h.gch *.o *.gcno *.gcda *.gcov
