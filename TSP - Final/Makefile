all: compile run

compile:
	g++ main.cpp -o main.out -O3

run:
	time ./main.out 1 51 100 1000 100 1 2 0.9 0.000167 10 0.1 > ex_detail4.txt

test:
	g++ test.cpp -o test.out -O3
	./test.out > test.txt

clean:
	rm *.out *.o *.txt