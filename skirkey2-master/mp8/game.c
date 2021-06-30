#include "game.h"

/* This program implements the basic fuctions of the "2048" game which are
 shifting the elements of a 2D array either up, down, left, or right. The 
 program cycles through the whole array and looks at the cells in the same rows
 and columns and and determines where to shift or merge the cells based on the
 rules of the game. */


game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure) 
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/
{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));

    //YOUR CODE STARTS HERE:  Initialize all other variables in game struct
	
	mygame->cols = cols ;	//Initialize number of rows and columns on the board
	mygame->rows = rows ;
	mygame->score = 0 ;	//Set score to zero
	
	int i;
	
	for(i = 0; i < rows*cols; i++) {	//Fill the board with empty (-1) values
		mygame->cells[i] = -1 ;
	}

    return mygame;
}

void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
	game structure to have the given number of rows and columns. Initialize
	the score and all elements in the cells to -1. Make sure that any 
	memory previously allocated is not lost in this function.	
*/
{
	/*Frees dynamically allocated memory used by cells in previous game,
	 then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
	free((*_cur_game_ptr)->cells);
	(*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));

	 //YOUR CODE STARTS HERE:  Re-initialize all other variables in game struct
	 
	 (*_cur_game_ptr)->cols = new_cols ;	//Reset number of columns and rows
	(*_cur_game_ptr)->rows = new_rows ;
	(*_cur_game_ptr)->score = 0 ;		//Reset score
	
	int i;
	
	for(i = 0; i < new_rows*new_cols; i++) {	//Fill new board with -1's
		(*_cur_game_ptr)->cells[i] = -1 ;
	}

	return;	
}

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells);
    free(cur_game);
    cur_game = NULL;
    return;
}

cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
	if the row and col coordinates do not exist.
*/
{
    //YOUR CODE STARTS HERE
    
    int ind ;
    
    if( 0 <= col && col < cur_game->cols ) {	//Make sure the row and col values for requested cell are within the bounds of the current game board
    	if( 0 <= row && row < cur_game->rows ) {
		ind = row * cur_game->cols + col ;	//If so, convert row and col value to its 1D array index
		return &cur_game->cells[ind] ;		//Return the address of the cell requested
	}
    } 

    return NULL; //If invalid row or col return null
}

int move_w(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the 
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can 
   not merge twice in one turn. If sliding the tiles up does not cause any 
   cell to change value, w is an invalid move and return 0. Otherwise, return 1. 
*/
{
    //YOUR CODE STARTS HERE
int modified = 0 ;	//Initialize variables and pointers
int current = 0 ;
int count = 0 ;
int j, i, k, next ;
int *nxt_ptr, *cur_ptr ;

for(j = 0; j < cur_game->cols; j++) {			//Iterate through the whole board except for the bottom row because there is nothing below it
	for(i = 0; i < (cur_game->rows - 1); i++) {
		
		cur_ptr = get_cell(cur_game, i, j) ;	//Get a pointer to the current cell
		count = 0 ;				//Initialize do while count to zero
		do {
		current = *cur_ptr ;	//Get value stored in the current cell
		
		for(k = i + 1; k < cur_game->rows; k++) {	//Iterate through rows indices starting with the cell below the current cell
			
			nxt_ptr = get_cell(cur_game, k, j) ;	//Get a pointer to the below cell as well as the value in that cell
			next = *nxt_ptr ;
			if(next == -1) {	//If below cell is empty, check the next below cell
				continue ;
			}
			
			if (next == current) {			//If there is a cell below the current cell with the same value, then merge the two
				*cur_ptr = current + next ;
				*nxt_ptr = -1 ;
				cur_game->score += (current + next) ;	//Add the sum of the two cells to the game score
				modified = 1 ;		//Flag that the game board has been modified
			}
			
			if (current == -1) {		//If the current cell is empty and there is a cell below with a value in it, then move the below cell into the current cell
				*cur_ptr = next ;
				*nxt_ptr = -1 ;
				modified = 1 ;		//Flag that the game board has been modified
			}
			break;		//Once a move has been made in the column, break so that cells do not jump over one another or make two merges in one move
		}
		count++ ;	//Increment do while count
		}while (current == -1 && count < cur_game->rows) ;	//If the first current cell was empty, then we can still potentially make a merge with the new value shifted into this cell, so go back into the loop with the new current value
		 
	}
}

    return modified; 	//Return whether or not the board has been modified
};

int move_s(game * cur_game) //slide down
{
    //YOUR CODE STARTS HERE
int modified = 0 ;	//Initialize variables and pointers
int current = 0 ;
int count = 0 ;
int j, i, k, next ;
int *nxt_ptr, *cur_ptr ;

for(j = (cur_game->cols - 1); j >= 0; j--) {		//Iterate through the whole board except for the top row because there is nothing above it
	for(i = (cur_game->rows - 1); i > 0; i--) {
		
		cur_ptr = get_cell(cur_game, i, j) ;	//Get a pointer to the current cell
		count = 0 ;				//Initialize do while count to zero
		do {
		current = *cur_ptr ;		//Get value stored in the current cell
		
		for(k = i - 1; k >= 0; k--) {	//Iterate through rows indices starting with the cell above the current cell
			
			nxt_ptr = get_cell(cur_game, i, k) ;	//Get pointer to next cell
			next = *nxt_ptr ;			//Get value stored in next cell
			if(next == -1) {	//If above cell is empty, check the next above cell
				continue ;
			}
			
			if (next == current) {			//If there is a cell above the current cell with the same value, then merge the two
				*cur_ptr = current + next ;
				*nxt_ptr = -1 ;
				cur_game->score += (current + next) ;	//Add the sum of the two cells to the game score
				modified = 1 ;	//Flag that the game board has been modified
			}
			
			if (current == -1) {		//If the current cell is empty and there is a cell above with a value in it, then move the below cell into the current cell
				*cur_ptr = next ;
				*nxt_ptr = -1 ;
				modified = 1 ;		//Flag that the game board has been modified
			}
			break;	//Once a move has been made in the column, break so that cells do not jump over one another or make two merges in one move
		}
		count++ ; //Increment the do while counter
		}while (current == -1 && count < cur_game->rows) ;	//If the first current cell was empty, then we can still potentially make a merge with the new value shifted into this cell, so go back into the loop with the new current value
		 
	}
}

    return modified;	//Return whether or not the game board has been modified
};

int move_a(game * cur_game) //slide left
{
    //YOUR CODE STARTS HERE
int modified = 0 ;	//Initialize variables and pointers
int current = 0 ;
int count = 0 ;
int j, i, k, next ;
int *nxt_ptr, *cur_ptr ;

for(i = 0; i < (cur_game->rows); i++) {			//Iterate through the whole board except for the rightmost column because there is nothing to the right of it
	for(j = 0; j < (cur_game->cols-1); j++) {
		
		cur_ptr = get_cell(cur_game, i, j) ;	//Get a pointer to the current cell
		count = 0 ;				//Initialize do while count to zero
		do {
		current = *cur_ptr ;			//Get the value stored in the current cell
		
		for(k = j + 1; k < cur_game->cols; k++) {	//Iterate through column indices starting with the cell beside the current cell
			
			nxt_ptr = get_cell(cur_game, i, k) ;	//Get pointer to next cell
			next = *nxt_ptr ;			//Get value stored in next cell
			if(next == -1) {	//If cell to right is empty, check the next right cell	
				continue ;
			}
			
			if (next == current) {			//If there is a cell to the right of the current cell with the same value, then merge the two
				*cur_ptr = current + next ;
				*nxt_ptr = -1 ;
				cur_game->score += (current + next) ;	//Add the sum of the two cells to the game score
				modified = 1 ;		//Flag that the game board has been modified
			}
			
			if (current == -1) {		//If the current cell is empty and there is a cell to the right with a value in it, then move the new cell into the current cell
				*cur_ptr = next ;
				*nxt_ptr = -1 ;
				modified = 1 ;		//Flag that the game board has been modified
			}
			break;		//Once a move has been made in the column, break so that cells do not jump over one another or make two merges in one move
		}
		count++ ;	//Increment do while loop counter
		}while (current == -1 && count < cur_game->cols) ; //If the first current cell was empty, then we can still potentially make a merge with the new value shifted into this cell, so go back into the loop with the new current value
		 
	}
}

    return modified;	//Return whether or not the gam board has been modified
};

int move_d(game * cur_game){ //slide to the right
    //YOUR CODE STARTS HERE
int modified = 0 ;	//Initialize variables and pointers
int current = 0 ;
int count = 0 ;
int j, i, k, next ;
int *nxt_ptr, *cur_ptr ;

for(i = (cur_game->rows - 1); i >= 0; i--) {		//Iterate through the whole board except for the leftmost column because there is nothing to the left of it
	for(j = (cur_game->cols - 1); j > 0; j--) {
		
		cur_ptr = get_cell(cur_game, i, j) ;	//Get pointer to current cell
		count = 0 ;				//Initialize do while count to zero
		do {
		current = *cur_ptr ;		//Get value stored in current cell
		
		for(k = j - 1; k >= 0; k--) {		//Iterate through column indices starting with the cell beside the current cell
			
			nxt_ptr = get_cell(cur_game, i, k) ;	//Get pointer to next cell
			next = *nxt_ptr ;			//Get value stored in next cell
			if(next == -1) {		//If cell to left is empty, check the next left cell
				continue ;
			}
			
			if (next == current) {			//If there is a cell to the left of the current cell with the same value, then merge the two
				*cur_ptr = current + next ;
				*nxt_ptr = -1 ;
				cur_game->score += (current + next) ;	//Add the sum of the two cells to the game score
				modified = 1 ;	//Flag that the game board has been modified
			}
			
			if (current == -1) {		//If the current cell is empty and there is a cell to the left with a value in it, then move the new cell into the current cell
				*cur_ptr = next ;
				*nxt_ptr = -1 ;
				modified = 1 ;	//Flag that the game board has been modified
			}
			break;	//Once a move has been made in the column, break so that cells do not jump over one another or make two merges in one move
		}
		count++ ; //Increment do while counter
		}while (current == -1 && count < cur_game->cols) ;//If the first current cell was empty, then we can still potentially make a merge with the new value shifted into this cell, so go back into the loop with the new current value
		 
	}
}

    return modified;
};

int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
	Return 1 if there are possible legal moves, 0 if there are none.
 */
{
    //YOUR CODE STARTS HERE
int i, j, current, adj1, adj2 ;		//Initialize variables and pointers
int *cur_ptr, *adj1_ptr, *adj2_ptr ;

for(i = 0; i < cur_game->rows; i++) {		//Iterate through the entire game board
	for(j = 0; j < cur_game->cols; j++) {
		
		cur_ptr = get_cell(cur_game, i, j) ;	//Get pointer to and value in current cell
		current = *cur_ptr ;
		if(current == -1) {	//If a cell is empty then return that there can still be moves made
		return 1 ;
		}
		
		adj1_ptr = get_cell(cur_game, i + 1, j) ;	//Get pointers to and values in cells directly to the right of and below the current cell
		adj2_ptr = get_cell(cur_game, i, j + 1) ;
		adj1 = *adj1_ptr ;
		adj2 = *adj2_ptr ;
		
		if(current == adj1 || current == adj2) {	//If current cell has same value as one of its adjacent cells then return that moves may still be made
			return 1 ;
		}
	}
}
    return 0;	//return that no moves can be made
}


/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{
	
	cell * cell_ptr;
    cell_ptr = 	cur_game->cells;
	
    if (cell_ptr == NULL){ 	
        printf("Bad Cell Pointer.\n");
        exit(0);
    }
	
	
	//check for an empty cell
	int emptycheck = 0;
	int i;
	
	for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
		if ((*cell_ptr) == -1){
				emptycheck = 1;
				break;
		}		
        cell_ptr += 1;
	}
	if (emptycheck == 0){
		printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
		exit(0);
	}
	
    int ind,row,col;
	int num;
    do{
		ind = rand()%((cur_game->rows)*(cur_game->cols));
		col = ind%(cur_game->cols);
		row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
	num = rand()%20;
	if(num <= 1){
		*get_cell(cur_game, row, col) = 4; // 1/10th chance
	}
	else{
		*get_cell(cur_game, row, col) = 2;// 9/10th chance
	}
}

int print_game(game * cur_game) 
{
    cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;
	
	printf("\n\n\nscore:%d\n",cur_game->score); 
	
	
	printf("\u2554"); // topleft box char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // top box char
	printf("\u2557\n"); //top right char 
	
	
    for(i = 0; i < rows; i++){
		printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  "); 
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
					default:
						printf("  X  ");

                }

            }
            cell_ptr++;
        }
	printf("\u2551\n"); //print right wall and newline
    }
	
	printf("\u255A"); // print bottom left char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // bottom char
	printf("\u255D\n"); //bottom right char
	
    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{ 
	int rows,cols;
	char buf[200];
	char garbage[2];
    int move_success = 0;
	
    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
	case 'n':
		//get row and col input for new game
		dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
		while (NULL == fgets(buf,200,stdin)) {
			printf("\nProgram Terminated.\n");
			return 0;
		}
		
		if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
		rows < 0 || cols < 0){
			printf("Invalid dimensions.\n");
			goto dim_prompt;
		} 
		
		remake_game(&cur_game,rows,cols);
		
		move_success = 1;
		
    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }

	
	
	
    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game); 
		 print_game(cur_game);
    } 

    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}
