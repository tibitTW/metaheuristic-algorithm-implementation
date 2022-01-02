all: compile run

CC = g++
target = main.cpp
test_target = test.cpp
cflags = -O3
exe = main.exe
debug_exe = debug.exe
test_exe = test.exe
result_file = result.txt

NP = 30
CR = 0.9
F = 0.6
MAX_FES = 200000
X_DIM = 2
X_MIN = -20
X_MAX = 20
RUN = 51

compile:
	$(CC) $(target) -o $(exe)

run:
	$(exe) $(NP) $(CR) $(F) $(MAX_FES) $(X_DIM) $(X_MIN) $(X_MAX) $(RUN) > $(result_file)

test:
	$(CC) $(test_target) -o $(test_exe) 
	$(test_exe) > out.txt
debug:
	$(CC) $(target) -o $(debug_exe) -g
	gdb $(debug_exe)
	