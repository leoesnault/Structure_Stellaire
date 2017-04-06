CC=g++
CFLAGS= -std=c++11 -Wall
PY=python3
EXEC=prog_Lane-Emden.out
SRC=prog_Lane-Emden.cpp

all: clean compexec affichage

clean:
	rm -f *.out
	rm -f *.dat

compexec:
	$(CC) $(CFLAGS) $(SRC) -o $(EXEC)
	./$(EXEC)

affichage:
	$(PY) ../affichages/affichage_Lane-Emden.py

comparaison_methodes:
	$(CC) $(CFLAGS) prog_comparaison_methodes.cpp -o prog_comparaison_methodes.out
	./prog_comparaison_methodes.out
	$(PY) ../affichages/affichage_comparaison_methodes.py