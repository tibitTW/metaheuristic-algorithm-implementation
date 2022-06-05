CC := g++
EXEC := main.out
FLAGS := -O3

all: $(EXEC)

main.out:
	$(CC) main.cpp -o $@ $(FLAGS)

debug:
	$(CC) main.cpp -o debug.out -g3
	gdb degub.out

.PHONY: test run clean

test:
	./main.out DE 1 1 2 -600 600 30 0.9 0.6 20000 >./de_griewank_2d_1r.txt

run:
	./ex.sh

clean:
	rm *.out *.o