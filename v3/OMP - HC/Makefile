all: compile run

compile:
	g++ main.cpp -o main.exe -O3
	
run:
	main.exe 100 1000 30 out.txt

test:
	g++ test.cpp -o test.exe -O3
	test.exe > t.txt

debug:
	g++ main.cpp -o main.exe -O3 -g

clean:
	del *.o *.exe