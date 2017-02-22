CC=g++
CFLAGS= -std=c++11 -Wall
EXEC=prog.out
SRC=prog.cpp

all: clean compexec affichage

clean:
	rm -rf *.out

compexec:
	$(CC) $(CFLAGS) $(SRC) -o $(EXEC)
	./$(EXEC)

affichage:
	python3 affichage.py

affichage_temp:
	python3 affichage_temp.py

affichage_variables_physiques:
	python3 affichage_variables_physiques.py