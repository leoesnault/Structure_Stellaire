CC=g++
CFLAGS= -std=c++11 -Wall
PY=python
EXEC=prog.out
SRC=prog.cpp

all: clean compexec affichage

clean:
	rm -f *.out
	rm -f *.dat

compexec:
	$(CC) $(CFLAGS) $(SRC) -o $(EXEC)
	./$(EXEC)

affichage:
	$(PY) affichage.py

affichage_temp:
	$(PY) affichage_temp.py

affichage_variables_physiques:
	$(PY) affichage_variables_physiques.py
