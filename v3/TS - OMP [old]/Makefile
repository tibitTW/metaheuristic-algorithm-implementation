all: compile run

compile:
	g++ main.cpp -o ts.exe

run:
	ts.exe 100 1000 30 1 result.txt
#	te.exe BIT_SIZE ITERATION RUN TRANSITION_TYPE RESULT_PATH
test:
	g++ test.cpp -o test.exe
	test.exe > result.txt
	
clean:
	del *.o *.exe