
test:test.cc 
	g++ test.cc node.o xml.o -o test
libxml.a:xml.o node.o
	ar cr libxml.a node.o xml.o
xml.o:xml.cc  xml.h
	g++ -c xml.cc  -std=c++14
node.o:node.cc node.h
	g++ -c node.cc
clean:
	rm -f node.o  xml.o libxml.a test
