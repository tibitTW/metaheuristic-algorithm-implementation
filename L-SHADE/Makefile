all: compile run

compile:
	g++ main.cpp -o main.exe -O3

run:
	main.exe 10 -100 100 1 51 result.txt
#	main.exe x_dim x_min x_max fun_num run

test:
	g++ test.cpp -o test.exe -O3
	test.exe > out.txt

clean:
	del *.o *.exe
