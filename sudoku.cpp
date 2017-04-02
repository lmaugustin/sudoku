#include <cmath>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <memory>
#include "sudoku.h"

using namespace std;

int main() {
  ifstream inp;
  SudokuBoard *SB;

  inp.open("sudoku-games.txt");
  SB = new SudokuBoard();
  SudokuBoard::depth = -1;
  
  while(SB->Read(inp) == true) {
    cout << "Starting Board:" << endl;
    SB->Print();
    SB->SmartSolve();  // Use "smart" techniques to solve the puzzle.  No recursion.
    SB->PrintPossibilities();
    if(SB->solve() == true) {  // Use recursion to finish if our smart techniques don't solve all
      cout << endl << "Solution:" << endl;
      SB->Print();
      cout << "Recursion: " << SudokuBoard::depth << endl;
    } else {
      cout << endl << "No Solution." << endl;
    }
  }

  exit(0);
}

int SudokuBoard::depth = -1;

bool SudokuBoard::solve() {
  SudokuBoard *SB2;
  int FirstOpenSquare;

  depth++;
  FirstOpenSquare = this->GetFirstOpenSquare();
  if(FirstOpenSquare == 82) {
    // Board is complete. All squares have been assigned and the solution is legal.
    return true;
  } else {
    for(int tryint = 1; tryint <= 9; tryint++) {
      // Use the set of possible values created by the "smart" search heuristics
      // to prune the recursive search matrix.
      if(this->isPossible(FirstOpenSquare, tryint)) {
	SB2 = new SudokuBoard(this);
	SB2->SetSquare(FirstOpenSquare, tryint);
	if(SB2->isLegal()) {
	  if(SB2->solve() == true) {
	    this->CopyFrom(SB2);
	    return true;
	  }
	} else {
	  delete SB2;
	}
      }
    }
  }
  // No solution
  return false;
}

void SudokuBoard::Print() {
  for(int row = 0; row < 9; row++) {
    for(int col = 0; col < 9; col++) {
      cout << board[row][col] << ' ' ;
    }
    cout << endl;
  }
}

bool SudokuBoard::isLegal() {
  bool s[10];
  
  // Check rows
  for(int r = 0; r < 9; r++) {
    for(int i = 0; i < 10; i++) s[i] = false;
    for(int c = 0; c < 9; c++) {
      if(board[r][c] != 0) {
	if(s[board[r][c]] == true) {
	  return false;
	} else {
	  s[board[r][c]] = true;
	}
      }
    }
  }

  // Check columns
  for(int c = 0; c < 9; c++) {
    for(int i = 0; i < 10; i++) s[i] = false;
    for(int r = 0; r < 9; r++) {
      if(board[r][c] != 0) {
	if(s[board[r][c]] == true) {
	  return false;
	} else {
	  s[board[r][c]] = true;
	}
      }
    }
  }

  // Check squares
  for(int sqr = 0; sqr < 3; sqr++) {
    for(int sqc = 0; sqc < 3; sqc++) {
      for(int i = 0; i < 10; i++) s[i] = false;
      for(int r = 3*sqr; r < 3*sqr+3; r++) {
	for(int c = 3*sqc; c < 3*sqc+3; c++) {
	  if(board[r][c] != 0) {
	    if(s[board[r][c]] == true) {
	      return false;
	    } else {
	      s[board[r][c]] = true;
	    }
	  }
	}
      }
    }
  }

  return true;
  
}

// Squares are numbered 1 thru 81
int SudokuBoard::GetFirstOpenSquare() {
  int sq = 1;
  for(int r = 0; r < 9; r++) {
    for(int c = 0; c < 9; c++) {
      if(board[r][c] == 0) {
	return sq;
      } else {
	sq++;
      }
    }
  }
  return sq;
}

// Squares are numbered 1 thru 81
void SudokuBoard::SetSquare(int s, int val) {
  int row = square_to_row(s);
  int col = square_to_col(s);

  board[row][col] = val;
}

bool SudokuBoard::Read(ifstream &inp) {
  int j;
  
  for(int r = 0; r < 9; r++) {
    for(int c = 0; c < 9; c++) {
      possible[r][c].clear();
      if(!inp.eof()) {
	inp >> board[r][c];
	if(board[r][c] != 0) {
	  possible[r][c].insert(board[r][c]);
	} else {
	  for(int i = 1; i <= 9; i++) {
	    possible[r][c].insert(i);
	  }
	}
      } else {
	return false;
      }
    }
  }
  return true;
}

void SudokuBoard::CopyFrom(SudokuBoard *b) {
  for(int r = 0; r < 9; r++) {
    for(int c = 0; c < 9; c++) {
      board[r][c] = b->GetSquare(r,c);
    }
  }
}

SudokuBoard::SudokuBoard(SudokuBoard *b) {
  this->CopyFrom(b);
}

SudokuBoard::SudokuBoard() {
  for(int r = 0; r < 9; r++) {
    for(int c = 0; c < 9; c++) {
      board[r][c] = 0;
    }
  }
}

int SudokuBoard::GetSquare(int row, int col) {
  return board[row][col];
}

bool SudokuBoard::isPossible(int square, int inttotry) {
  int row = square_to_row(square);
  int col = square_to_col(square);

  if(possible[row][col].find(inttotry) == possible[row][col].end()) {
    // Not possible
    return false;
  } else {
    // possible
    return true;
  }
}

set<int> SudokuBoard::possible[9][9];

void SudokuBoard::PrintPossible(int square) {
  int row = square_to_row(square);
  int col = square_to_col(square);

  cout << "Possibilities for square(" << square << ") [" << row << ","
       << col << "] are { ";
  for(auto it = possible[row][col].begin(); it != possible[row][col].end(); it++) {
    cout << *it << ' ';
  }
  cout << '}' << endl;
}

void SudokuBoard::PrintPossibilities() {
  for(int i = 1; i <= 81; i++) {
    PrintPossible(i);
  }
}
