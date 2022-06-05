CC := g++
EXEC := main.out
FLAGS := -O3

all: $(EXEC)

main.out:
	$(CC) main.cpp -o $@ $(FLAGS)

debug:
	$(CC) main.cpp -o debug.out -g3
	gdb degub.out

test:
	$(CC) test.cpp -o test.out -O3
	./test.out

.PHONY: run clean

run:
	./ex.sh

clean:
	rm *.out *.o