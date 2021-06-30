#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

/* This program solves specifically formatted mazes in text files using a depth
first searching recursion technique. Memory is first allocated for the maze structure
to include details about the maze as well as the maze layout itself, then the maze layout
is passed to the recursive function which searches through all possible paths in the maze to
ultimately find the solution path, marking it along the way */


/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    // Your code here. Make sure to replace following line with your own code.
    int i, j ;
    char cur ;
    FILE *infile = fopen(fileName, "r") ;				//Open maze file, allocate memory for the maze structure, and read maze width and height
    maze_t* maze = (maze_t*)malloc(6*sizeof(maze_t)) ;
    fscanf(infile, "%d" "%d", &(maze->width), &(maze->height)) ;
    maze->cells = (char**)malloc((maze->height) * sizeof(char*)) ;

    for (i = 0; i < maze->height; i++) {				//Read the maze file to fill the cell values for the maze in the structure
    	maze->cells[i] = (char*)malloc((maze->width) * sizeof(char)) ;
    }
    for (i = 0; i < maze->height; i++) {
    	for (j = 0; j < maze->width;  j++) {
		
		cur = fgetc(infile) ;
		if (cur == '\n') {	//If the file read char is new line, then skip to next read
		cur = fgetc(infile) ;		
		}
		maze->cells[i][j] = cur ;
		
		if (cur == 'S') {		//If we encounter the starting position, store its index in the structure
			maze->startRow = i ;
			maze->startColumn = j ;
		}
		if (cur == 'E') {		//If we encounter the ending position, store its index in the structure
			maze->endRow = i ;
			maze->endColumn = j ;
		}
	}
    }
    fclose(infile) ;	//Close the maze file
    
    return maze;	//return pointer to maze structure
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    // Your code here.
int k ;
for(k = 0; k < maze->height; k++) {	//Free all of the memory associated with the maze in the reverse order from which it was allocated
	free(maze->cells[k]) ;
}
free(maze->cells) ;
free(maze) ;
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    // Your code here.
int i, j ;
for (i = 0; i < maze->height; i++) {			//Iterate through the maze struct cells array and print each cell
	for ( j = 0; j < maze->width; j++) {
		printf("%c", maze->cells[i][j]) ;
	}
	printf("\n") ;	//print new line at the end of each row
}
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeDFS(maze_t * maze, int col, int row)
{
    // Your code here. Make sure to replace following line with your own code.
    
    if (row >= maze->height || row < 0 || col < 0 || col >= maze->width) {	//If current cell is out of bounds return false
    	return 0 ;
    }
    
    if (maze->cells[row][col] == 'E') {
    	maze->cells[maze->startRow][maze->startColumn] = 'S' ;		//If end of maze reached, restore the starting cell to its original value and return true
    	return 1 ;
    }
    
    if (maze->cells[row][col] != ' ' && maze->cells[row][col] != 'S') {		//If current cell is not empty and it is not the starting cell, then return false
    	return 0 ;
    }

    maze->cells[row][col] = '*' ;			//Mark the current cell as a part of the solution path
    
    if (solveMazeDFS(maze, col - 1, row) == 1) {	//Recursively call function for cells above, below, left, and right of current cell, and if they return true, then return true
    	return 1 ;
    }
    if (solveMazeDFS(maze, col + 1, row) == 1) {
    	return 1 ;
    }
    if (solveMazeDFS(maze, col, row - 1) == 1) {
    	return 1 ;
    }
    if (solveMazeDFS(maze, col, row + 1) == 1) {
    	return 1 ;
    }

    maze->cells[row][col] = '~' ;	//Mark current cell as visited, but not part of the solution path
    
    return 0;	//return false
}
