CC = g++
CFLAGS = -std=c++11 -Wall
EXEC = prog.out
SRC = prog.cpp

all: $(EXEC)
	$(CC) $(CFLAGS) $(SRC) -o $(EXEC)
	./$(EXEC)

clean:
	rm -rf *.out
