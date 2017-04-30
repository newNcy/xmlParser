
test:test.cc ./lib/libxml.a
	g++ test.cc -o test  -L./lib -lxml
./lib/libxml.a:./temp/xml.o ./temp/node.o
	ar cr ./lib/libxml.a ./temp/node.o ./temp/xml.o
./temp/xml.o:./src/xml.cc  ./include/xml.h
	g++ -c ./src/xml.cc  -std=c++14 -o ./temp/xml.o
./temp/node.o:./src/node.cc ./include/node.h
	g++ -c ./src/node.cc  -o ./temp/node.o
clean:
	rm -f ./temp/* ./lib/* test
