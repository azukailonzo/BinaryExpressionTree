in2post.x: in2post.o
	g++ -o in2post.x in2post.o
in2post.o: stack.h stack.hpp in2post.cpp
	g++ -std=c++11 -c in2post.cpp
clean:
	rm -f *.o in2post.x
