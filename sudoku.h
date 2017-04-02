#ifndef SUDOKU_H
#define SUDOKU_H

#include <cmath>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <memory>
#include <set>

using namespace std;

class SudokuBoard {
 public:
  SudokuBoard(SudokuBoard *b);
  SudokuBoard();
  bool solve();
  bool SmartSolve();
  void Print();
  void PrintPossibilities();
  bool isLegal();
  int GetFirstOpenSquare();
  void SetSquare(int s, int val);
  int GetSquare(int row, int col);
  bool Read(ifstream &inp);
  void CopyFrom(SudokuBoard *b);
  // Keeps track of how many times the recursive solver needed to be called
  // If SmartSolve() is perfect, this will be zero
  static int depth;
 private:
  int board[9][9];   // This is the Board itself
  // For each square on the board we maintain a Set of possible
  // values for that square.  The "smart solver" (SmartSolve()) uses
  // several techniques to scan the board and prune the possible
  // values for each square.
  static set<int> possible[9][9];

  bool isPossible(int square, int inttotry);
  void PrintPossible(int square);
  void AssignOnlyPossible();
  int square_to_row(int sq) { return (sq - 1) / 9; };
  int square_to_col(int sq) { return (sq - 1)  % 9; };
  // Private test functions for SmartSolve()
  bool at_most_one_per_row();
  bool at_most_one_per_col();
  bool at_most_one_per_3x3();
  bool at_least_one_per_row();
  bool at_least_one_per_col();
  bool at_least_one_per_3x3();
};


#endif
