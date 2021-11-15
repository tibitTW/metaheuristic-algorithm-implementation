all: compile run

compile:
	g++ main.cpp -o main.exe -O3

run:
	main.exe 51	      50      1000      100               2                 4                    0.85               0.000167         1.2 		  51  > res.txt
#	main.exe CITY_DIM ANT_POP ITERATION PHERO_ANT_CARRIED PHERO_CTRL_FACTOR DISTANCE_CTRL_FACTOR EVAPORATION_FACTOR MIN_PHERO_AMOUNT BONUS_WEIGHT RUN
test:
	g++ test.cpp -o test.exe
	test.exe
	
clean:
#	rm *.o *.exe
	del *.o *.exe
	