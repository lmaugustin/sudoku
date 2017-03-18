#ifndef SUDOKU_H
#define SUDOKU_H

#include <cmath>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <memory>

using namespace std;

class SudokuBoard {
 public:
  SudokuBoard(SudokuBoard *b);
  SudokuBoard();
  bool solve();
  void Print();
  bool isLegal();
  int GetFirstOpenSquare();
  void SetSquare(int s, int val);
  int GetSquare(int row, int col);
  bool Read(ifstream &inp);
  void CopyFrom(SudokuBoard *b);
 private:
  int board[9][9];
};


#endif
