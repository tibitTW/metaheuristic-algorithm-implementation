all: compile run

compile:
	g++ main.cpp -o main.exe

run:
	main.exe 100 1000 51 300 0.95 0 0 0 onemax-B2D-result.csv
	main.exe 100 1000 51 300 0.95 1 0 0 onemax-bit-flip-nb-result.csv
	main.exe 4 1000 51 1000 0.95 0 1 4 deception-B2D-nb-4n-result.csv
	main.exe 4 1000 51 300 0.95 1 1 4 deception-bit-flip-4n-result.csv
	main.exe 10 1000 51 300 0.95 0 1 10 deception-B2D-nb-10n-result.csv
	main.exe 10 1000 51 300 0.95 1 1 10 deception-bit-flip-10n-result.csv
#	main.exe BIT_SIZE ITERATION RUN INIT_TEMP TEMP_COOLDOWN_RATE NB_TYPE F_TYPE N RESULT_PATH
#	neighbor type => 0: B2D neighbor / 1: onebit-flip neighbor
#	fitness type => 0: one max problem / 1: deception problem

test:
	g++ test.cpp -o test.exe
	./test.exe

debug:
	g++ main.cpp -o main.exe -g
	gdb main.exe 100 100 51 300 0.95 0 0 4 result.csv

clean:
	del *.o *.exe
