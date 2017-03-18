# Makefile for the Scrabble Game
# play.cpp is the main program

# GFLAGS=-g -c -std=c++11 -DDEBUG
GFLAGS=-g -std=c++11

sudoku: sudoku.cpp sudoku.h
	g++ ${GFLAGS} sudoku.cpp -o sudoku

clean:
	rm -f *~ sudoku

commit:
	git commit -m "Update" *.h *.cpp Makefile sudoku-games.txt README.md

pull:
	-make commit
	git pull sudoku master

push:
	-make pull
	git push sudoku
