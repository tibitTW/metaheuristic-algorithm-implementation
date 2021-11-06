all: compile run

compile:
	g++ main.cpp -o main.exe
#	g++ main.cpp -o main.exe -O3

run:
	main.exe 2 	   -100  100   1       1   result.txt > out.txt
#	main.exe x_dim x_min x_max fun_num run output_file

debug:
	g++ main.cpp -o debug.exe -g3
	gdb --args debug.exe 10 -100 100 1 51 result.txt

test:
	g++ test.cpp -o test.exe -O3
	test.exe > out.txt

clean:
	del *.o *.exe
