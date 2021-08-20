all: compile run

compile:
	g++ main.cpp -o main.exe

run:
	main.exe 51 1000 50 50 2 1 0.6 0.000167 51
#	main.exe CITY_DIM ANT_POP ITERATION PHERO_ANT_CARRIED PHERO_CTRL_FACTOR DISTANCE_CTRL_FACTOR EVAPORATION_FACTOR MIN_PHERO_AMOUNT
test:
	g++ test.cpp -o test.exe
	test.exe 51 1000 50 50 2 1 0.6 0.000167 51
#	test.exe 51 1000 50 50 2 1 0.6 0.000167
	
clean:
#	rm *.o *.exe
	del *.o *.exe