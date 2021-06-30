#include "sudoku.h"

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

// You are free to declare any private functions if needed.


/* This program takes any given legal 9x9 sudoku board and solves all of the missing
numbers using a recursive algorithm which looks through the 2D array representation of the board
and upon finding open spots, tries every number between 1 and 9, checking if any of those numbers already exist
in the same row, column, or 3x3 box for the given index, and if not, the program backtracks until the board is completely solved
*/

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  // BEG TODO
int j;

for(j = 0; j < 9; j++) {		//Iterate through indices in same row as target to see if val is already in the row
	if (sudoku[i][j] == val) {
		return 1;		//If val is in row, return 1, if not, return 0
	}
}
  
  return 0;
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  // BEG TODO
  
  int i;

for(i = 0; i < 9; i++) {
	if (sudoku[i][j] == val) {	//Look through column to see if val already exists
		return 1;		//If val already exists in column, return 1, if not, return 0
	}
}
  
  return 0;
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9);
  
  // BEG TODO
int row = i - i%3;	//Get the index of the upper leftmost spot of the 3x3 block which the index of interest occupies
int col = j - j%3;
int k, t;
for(k = row; k < row + 3; k++) {		//Iterate through 3 row indices and their 3 respective column indices each
	for(t = col; t < col +3; t++) {
		if (sudoku[k][t] == val) {	
			return 1;		//If val already exists in box, return 1, if not, return 0
		}
	}
}
  return 0;
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  // BEG TODO
if(is_val_in_3x3_zone(val, i, j, sudoku) == 0 && is_val_in_col(val, j, sudoku) == 0 && is_val_in_row(val, i, sudoku) == 0) {	//If val is not in box, row, or column, return 1, if not, return 0
	return 1;
}

return 0;
  
  // END TODO
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

  // BEG TODO.
int i, j, num;

for (i = 0; i < 9; i++) {
	for(j = 0; j < 9; j++) {
		if(sudoku[i][j] == 0) {				//Look through entire board for empty indices
			for(num = 1 ; num <= 9; num++) {
				if(is_val_valid(num, i, j, sudoku) == 1) {	//For a given empty spot check if any number 1-9 is allowed to go there
					sudoku[i][j] = num ;
					if (solve_sudoku(sudoku) == 1) {	//If number is allowed, store it at that index and recurse until array is full of numbers (return value = 1)
						return 1 ;
					}
					sudoku[i][j] = 0 ;	//If sudoku can't be solved further with new number, set the given index back to zero and try another number	
				}
			}
			return 0;	
		}
	}
}

  return 1;
  // END TODO.
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}





