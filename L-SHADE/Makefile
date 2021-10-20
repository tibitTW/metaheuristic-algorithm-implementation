all: compile run

compile:
	g++ main.cpp -o main.exe -O3

run:
	main.exe

test:
	g++ test.cpp -o test.exe -O3
	test.exe > out.txt

clean:
	del *.o *.exe
