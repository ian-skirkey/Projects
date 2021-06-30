/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */
 
 /* This program simulates the game of life given an array of chosen dimensions filled with values 0 and 1 where 0 represents a dead cell and 1 represents a living cell. The program looks at the values of a cell's neighbors (perimeter including corners) to see how many living neighbors a given cell has. If the cell is alive and has 2 or 3 living neighbors, then it remains alive, otherwise the cell dies. If a cell is dead and it has three living neigbors, then it returns to life, otherwise it remains dead. */

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){

int live = 0;		//Initialize variables
int i, j ;

for(i = row - 1 ; i <= row + 1; i++) {			//Iterate through 3x3 block of cells with cell of interest at the center
	if( i >= 0 && i < boardRowSize) {		//Make sure that we do not look outside the bounds of the array (corners and edges)
		for(j = col - 1 ; j <= col + 1; j++) {
			if( j >= 0 && j < boardColSize) {
				if(!(i == row && j == col)) {			//Skip over the cell of interest (not neighbor to itself)
					if(board[i*boardColSize + j] == 1) {	//If a neighbor is alive, increment living neighbor count
						live++ ;
					}
				}
			}
		}
	}
}

return live ;
}
/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {
 
int size = boardRowSize * boardColSize ;	//Initialize variables and empty array to hold next step in the game so the board does not change while it is being checked
int j, i, k;
int next[size] ;

for(j = 0 ; j < boardRowSize ; j++) {		//Iterate through whole board
	for(i = 0 ; i < boardColSize ; i++) {
		if (board[j*boardColSize + i] == 1) {	//If current cell is live and has 2 or 3 live neighbors, then set same cell in next array to 1 and move to next column
		
		if(countLiveNeighbor(board, boardRowSize, boardColSize, j, i) == 2 || countLiveNeighbor(board, boardRowSize, boardColSize, j, i) == 3) {
		next[j*boardColSize + i] = 1 ;
		continue ;
		
		}
		next[j*boardColSize + i] = 0 ; //If live cell does not have 2 or 3 live neigbors then set same cell in next array to 0 and move to next column
		continue ;
	}
	
	
	if (countLiveNeighbor(board, boardRowSize, boardColSize, j, i) == 3) {	//If current cell is dead and has 3 live neigbors then set same cell in next array to 1 and move to next column
		next[j*boardColSize + i] = 1 ;
		continue ;	
	}
	next[j*boardColSize + i] = 0 ; //If dead cell does not have 3 living neigbors then set same cell in next array to 0
	}
}
for(k = 0 ; k < size ; k++) {	//Overwrite current board with the next board
	board[k] = next[k] ;	
} 
}

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with 
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */ 
int aliveStable(int* board, int boardRowSize, int boardColSize){

int size = boardRowSize * boardColSize ; //Initialize variables and temporary array to hold next board for comparison
int temp[size];
int count = 0 ;
int k, j, p ;

for(k = 0 ; k < size ; k++) {  //Copy current board into temporary board
	temp[k] = board[k] ;	
} 

updateBoard(temp, boardRowSize, boardColSize) ;	//Update the temporary board to the next step

for(j = 0 ; j < size ; j++) { //Check if there are any live cells in the next step
	if(temp[j] == 1) {
		count++ ;
	}	
}

if(count == 0) {	//If no live cells in next step, return 1
	return 1 ;
}

for(p = 0 ; p < size ; p++) {		//Compare current board with next step, and if they are not identical, return 0, and if they are identical return 1
	if(temp[p] != board[p]) {
		return 0 ;
	}
	
}

return 1 ;

}
