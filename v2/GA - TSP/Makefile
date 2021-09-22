all: compile run

compile:
	g++ main.cpp -o main.exe

run:
	main.exe

test:
	g++ test.cpp -o test.exe
	test.exe
debug:
	g++ -o debug.exe main.cpp -g
	gdb debug.exe
	
clean:
	del *.o *.exe