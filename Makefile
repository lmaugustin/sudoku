# Makefile for the Scrabble Game
# play.cpp is the main program

# GFLAGS=-g -c -std=c++11 -DDEBUG
GFLAGS=-g -std=c++11

sudoku: sudoku.cpp sudoku.h
	g++ ${GFLAGS} sudoku.cpp -o sudoku

clean:
	rm -f *~ sudoku

commit:
	git commit -m "Update" *.h *.cpp Makefile

pull:
	-make commit
	git pull https://github.com/lmaugustin/sudoku

push:
	make pull
	git push
