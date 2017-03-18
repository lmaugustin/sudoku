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
  
  while(SB->Read(inp) == true) {
    cout << "Starting Board:" << endl;
    SB->Print();
    if(SB->solve() == true) {
      cout << endl << "Solution:" << endl;
      SB->Print();
    } else {
      cout << endl << "No Solution." << endl;
    }
  }

  exit(0);
}

bool SudokuBoard::solve() {
  SudokuBoard *SB2;
  int FirstOpenSquare;
  
  FirstOpenSquare = this->GetFirstOpenSquare();
  if(FirstOpenSquare == 82) {
    // Board is complete. All squares have been assigned and the solution is legal.
    return true;
  } else {
    for(int tryint = 1; tryint <= 9; tryint++) {
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
  int row = s / 9;
  int col = (s % 9) - 1;
  board[row][col] = val;
}

bool SudokuBoard::Read(ifstream &inp) {
  int j;
  
  for(int r = 0; r < 9; r++) {
    for(int c = 0; c < 9; c++) {
      if(!inp.eof()) {
	inp >> board[r][c];
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
