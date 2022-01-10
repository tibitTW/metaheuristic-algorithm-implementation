all: compile run

compile:
	g++ main.cpp -o main.out -O3
run:
	./main.out 51	      50      1000      100               2                 4                    0.85               0.000167         1.2 		  51  > res.txt
#	main.out CITY_DIM ANT_POP ITERATION PHERO_ANT_CARRIED PHERO_CTRL_FACTOR DISTANCE_CTRL_FACTOR EVAPORATION_FACTOR MIN_PHERO_AMOUNT BONUS_WEIGHT RUN
test:
	g++ test.cpp -o test.out
	test.out
	
clean:
#	rm *.o *.out
	del *.o *.out
	