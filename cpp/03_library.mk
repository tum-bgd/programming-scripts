all:
	g++ -c 03_doubled.cpp -o 03_doubled.o
	g++ -c 03_library.cpp -o 03_library.o
	g++ -o 03_library 03_library.o 03_doubled.o
run: 
	./03_library
