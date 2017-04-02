#include "sudoku.h"

bool SudokuBoard::SmartSolve() {
  bool changed;

  do {
    changed = false;
    //
    changed = at_most_one_per_row();
    changed = at_most_one_per_col();
    changed = at_most_one_per_3x3();
    //
    changed = at_least_one_per_row();
    changed = at_least_one_per_col();
    changed = at_least_one_per_3x3();
    //
    if(changed) {
      AssignOnlyPossible(); // If only one value is possible for that square, make it the value
    }
  } while (changed);
  return changed;
}

void SudokuBoard::AssignOnlyPossible() {
  int row, col;
  for(int i = 1; i <= 81; i++) {
    row = square_to_row(i); col = square_to_col(i);
    if(possible[row][col].size() == 1) {
      board[row][col] = *(possible[row][col].begin());
    }
  }
}

bool SudokuBoard::at_most_one_per_row() {
  bool globalchanged, loopchanged;

  globalchanged = false;
  do {
    loopchanged = false;
    for(int row = 0; row < 9; row++) {
      for(int col = 0; col < 9; col++) {
	if(board[row][col] != 0) {
	  for(int col2 = 0; col2 < 9; col2++) {
	    if(col2 != col) {
	      if(possible[row][col2].find(board[row][col]) != possible[row][col2].end()) {
		possible[row][col2].erase(board[row][col]);
		//		cout << "Removing " << board[row][col] << " from list of possibilities for ["
		//		     << row << "," << col2 << "]\n";
		loopchanged = true;
		globalchanged = true;
	      }
	    }
	  }
	}
      }
    }
  } while (loopchanged);
  
  return globalchanged;
}

bool SudokuBoard::at_most_one_per_col() {
  bool globalchanged, loopchanged;

  globalchanged = false;
  do {
    loopchanged = false;
    for(int col = 0; col < 9; col++) {
      for(int row = 0; row < 9; row++) {
	if(board[row][col] != 0) {
	  for(int row2 = 0; row2 < 9; row2++) {
	    if(row2 != row) {
	      if(possible[row2][col].find(board[row][col]) != possible[row2][col].end()) {
		possible[row2][col].erase(board[row][col]);
		//		cout << "Removing " << board[row][col] << " from list of possibilities for ["
		//		     << row2 << "," << col << "]\n";
		loopchanged = true;
		globalchanged = true;
	      }
	    }
	  }
	}
      }
    }
  } while (loopchanged);
  
  return globalchanged;
}

bool SudokuBoard::at_most_one_per_3x3() {
  bool globalchanged, loopchanged;

  globalchanged = false;
  do {
    loopchanged = false;
    for(int sqr = 0; sqr < 3; sqr++) {
      for(int sqc = 0; sqc < 3; sqc++) {
	for(int row = 3*sqr; row < 3*sqr+3; row++) {
	  for(int col = 3*sqc; col < 3*sqc+3; col++) {
	    if(board[row][col] != 0) {
	      for(int row2 = 3*sqr; row2 < 3*sqr+3; row2++) {
		for(int col2 = 3*sqc; col2 < 3*sqc+3; col2++) {
		  if((row2 != row) && (col2 != col)) {
		    if(possible[row2][col2].find(board[row][col]) != possible[row2][col2].end()) {
		      // Do stuff here
		      possible[row2][col2].erase(board[row][col]);
		      loopchanged = true;
		      globalchanged = true;
		    }
		  }
		}
	      }
	    }
	  }
	}
      }
    }
  } while (loopchanged);

  return globalchanged;
}

bool SudokuBoard::at_least_one_per_row() {
  bool globalchanged, loopchanged, found;
  int foundrow, foundcol;

  globalchanged = false;
  do {
    loopchanged = false;
    for(int row = 0; row < 9; row++) {
      for(int tryint = 1; tryint <= 9; tryint++) {
	found = false;
	for(int col = 0; col < 9; col++) {
	  if(possible[row][col].find(tryint) != possible[row][col].end()) {
	    if (found) {
	      // Found twice
	      found = false;
	      break;
	    } else {
	      found = true;
	      foundrow = row;
	      foundcol = col;
	    }
	  }
	}
	if (found) {
	  // Found the tryint exactly once in the row
	  if(board[foundrow][foundcol] == 0) {
	    possible[foundrow][foundcol].clear();
	    possible[foundrow][foundcol].insert(tryint);
	    board[foundrow][foundcol] = tryint;
	    loopchanged = true;
	    globalchanged = true;
	  }
	}
      }
    }
  } while (loopchanged);
  
  return globalchanged;
}

bool SudokuBoard::at_least_one_per_col() {
  bool globalchanged, loopchanged, found;
  int foundrow, foundcol;

  globalchanged = false;
  do {
    loopchanged = false;
    for(int col = 0; col < 9; col++) {
      for(int tryint = 1; tryint <= 9; tryint++) {
	found = false;
	for(int row = 0; row < 9; row++) {
	  if(possible[row][col].find(tryint) != possible[row][col].end()) {
	    if (found) {
	      // Found twice
	      found = false;
	      break;
	    } else {
	      found = true;
	      foundrow = row;
	      foundcol = col;
	    }
	  }
	}
	if (found) {
	  // Found the tryint exactly once in the column
	  if(board[foundrow][foundcol] == 0) {
	    possible[foundrow][foundcol].clear();
	    possible[foundrow][foundcol].insert(tryint);
	    board[foundrow][foundcol] = tryint;
	    loopchanged = true;
	    globalchanged = true;
	  }
	}
      }
    }
  } while (loopchanged);
  
  return globalchanged;
}

bool SudokuBoard::at_least_one_per_3x3() {
  bool globalchanged, loopchanged, found;
  int foundrow, foundcol, tryint;

  globalchanged = false;
  do {
    loopchanged = false;
    for(int sqr = 0; sqr < 3; sqr++) {
      for(int sqc = 0; sqc < 3; sqc++) {
	for(tryint = 1; tryint <= 9; tryint++) {
	  found = false;
	  for(int row = 3*sqr; row < 3*sqr+3; row++) {
	    for(int col = 3*sqc; col < 3*sqc+3; col++) {
	      if(possible[row][col].find(tryint) != possible[row][col].end()) {
		if(found) {
		  // found twice
		  found = false;
		  goto try_next_integer;
		} else {
		  found = true;
		  foundrow = row;
		  foundcol = col;
		}
	      }
	    }
	  }
	  try_next_integer:
	  if (found) {
	    // Found the tryint exactly once in the 3x3 block
	    if(board[foundrow][foundcol] == 0) {
	      possible[foundrow][foundcol].clear();
	      possible[foundrow][foundcol].insert(tryint);
	      board[foundrow][foundcol] = tryint;
	      loopchanged = true;
	      globalchanged = true;
	    }
	  }
	}
      }
    }
  } while (loopchanged);
  
  return globalchanged;
}
