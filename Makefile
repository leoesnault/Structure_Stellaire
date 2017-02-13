CC=g++
CFLAGS=-std=c++11 -Wall
EXEC=prog.out
SRC=prog.cpp

all: clean compexec display

clean:
	rm -rf *.out

compexec:
	$(CC) $(CFLAGS) $(SRC) -o $(EXEC)
	./$(EXEC)

display:
	python3 affichage.py

display_variables_physiques:
	python3 affichage_variables_physiques.py