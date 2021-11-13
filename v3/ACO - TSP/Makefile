all: compile run

compile:
	g++ main.cpp -o main.exe -O3

run:
	main.exe 51	      100     1000      51                2                 1                    0.9                0.000167         1  > res.txt
#	main.exe 51	      100     1000      51                2                 1                    0.9                0.000167         51  > res.txt
#	main.exe CITY_DIM ANT_POP ITERATION PHERO_ANT_CARRIED PHERO_CTRL_FACTOR DISTANCE_CTRL_FACTOR EVAPORATION_FACTOR MIN_PHERO_AMOUNT RUN
test:
	g++ test.cpp -o test.exe
	test.exe
	
clean:
#	rm *.o *.exe
	del *.o *.exe