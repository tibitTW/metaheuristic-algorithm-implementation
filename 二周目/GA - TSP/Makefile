all: compile run

compile:
	g++ main.cpp -o main.exe

run:
#	main.exe CITY_DIM ITERATION POP C_RATE M_RATE RUN
	main.exe 51 1000 100 0.8 0.1 51

test:
	g++ test.cpp -o test.exe
	test.exe

clean:
	del *.o *.exe