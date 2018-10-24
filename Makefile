all:pythoncpp

pythoncpp:pythoncpp.o
	g++ -w -o pythoncpp pythoncpp.o -lpython2.7
pythoncpp.o: pythoncpp.cpp
	g++ -w -c pythoncpp.cpp -I /usr/include/python2.7
clean:
	rm -f *.o pythoncpp
