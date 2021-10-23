all: compile run

compile:
	g++ main.cpp -o main.exe -O3
	
run:
	main.exe 100 1000 30 out.txt

debug:
	g++ main.cpp -o main.exe -O3 -g
clean:
	del *.o *.exe