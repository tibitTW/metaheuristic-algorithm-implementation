all: compile run

compile:
	g++ main.cpp -o main.exe

run:
	main.exe 100 1000 120 0.8 0.1 51 result.csv

test:
	g++ test.cpp -o test.exe
	test.exe > out.txt
	
clean:
	del *.o *.exe