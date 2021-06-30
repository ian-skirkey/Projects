  /* This program implements a game where the user attepts to guess a four digit number which the computer generates using a user input seed value. The user has twelve guesses before the program halts and they lose the game. On each valid guess attempt, the computer displays the number of perfect matches and the number of misplaced matches which were in that guess. */



#include <stdio.h>
#include <stdlib.h>

#include "prog5.h"


/*
 * You will need to keep track of the solution code using file scope
 * variables as well as the guess number.
 */

static int guess_number;
static int solution1;
static int solution2;
static int solution3;
static int solution4;


/*
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types.
 * The input entered by the user is already stored in the string seed_str by the code in main.c.
 * This function should use the function sscanf to find the integer seed value from the 
 * string seed_str, then initialize the random number generator by calling srand with the integer
 * seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid. 
 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (string contains anything
 *               other than a single integer), or 1 if string is valid (contains one integer)
 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
 *               if string is invalid. Prints nothing if it is valid.
 */
int
set_seed (const char seed_str[])
{
//    Example of how to use sscanf to read a single integer and check for anything other than the integer
//    "int seed" will contain the number typed by the user (if any) and the string "post" will contain anything after the integer
//    The user should enter only an integer, and nothing else, so we will check that only "seed" is read. 
//    We declare
//    int seed;
//    char post[2];
//    The sscanf statement below reads the integer into seed. 
//    sscanf (seed_str, "%d%1s", &seed, post)
//    If there is no integer, seed will not be set. If something else is read after the integer, it will go into "post".
//    The return value of sscanf indicates the number of items read succesfully.
//    When the user has typed in only an integer, only 1 item should be read sucessfully. 
//    Check that the return value is 1 to ensure the user enters only an integer. 
//    Feel free to uncomment these statements, modify them, or delete these comments as necessary. 
//    You may need to change the return statement below

int seed;
char post[2] = { 0 };

if (sscanf (seed_str, "%d%1s", &seed, post) != 1) {	// Check that only one input is read from the user 
	printf("set_seed: invalid seed\n") ;		// If not return error
	return 0;
}
if (post[0] != 0) {					//Check that the input included only integers
	printf("set_seed: invalid seed\n") ;		// If not return error
	return 0;			
}
srand(seed);				//If the input is what we want, call srand() with the user input seed value to set the seet and return 1

       return 1;
}


/*
 * start_game -- This function is called by main.c after set_seed but before the user makes guesses.
 *               This function creates the four solution numbers using the approach
 *               described in the wiki specification (using rand())
 *               The four solution numbers should be stored in the static variables defined above. 
 *               The values at the pointers should also be set to the solution numbers.
 *               The guess_number should be initialized to 1 (to indicate the first guess)
 * INPUTS: none
 * OUTPUTS: *one -- the first solution value (between 1 and 8)
 *          *two -- the second solution value (between 1 and 8)
 *          *three -- the third solution value (between 1 and 8)
 *          *four -- the fourth solution value (between 1 and 8)
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
 */
void
start_game (int* one, int* two, int* three, int* four)
{
    //your code here
    int a = rand();		//Get random numbers for solution
    int b = rand();
    int c = rand();
    int d = rand();
   
    solution1 = (a % 8) + 1 ;	//Convert them all down to numbers between 1 and 8
    solution2 = (b % 8) + 1 ;
    solution3 = (c % 8) + 1 ;
    solution4 = (d % 8) + 1 ;
    
    *one = solution1;		//Store the solution numbers at required addresses
    *two = solution2;
    *three = solution3;
    *four = solution4;
    
    guess_number = 1;		//Initialize to first guess
}

/*
 * make_guess -- This function is called by main.c after the user types in a guess.
 *               The guess is stored in the string guess_str. 
 *               The function must calculate the number of perfect and misplaced matches
 *               for a guess, given the solution recorded earlier by start_game
 *               The guess must be valid (contain only 4 integers, within the range 1-8). If it is valid
 *               the number of correct and incorrect matches should be printed, using the following format
 *               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
 *               If valid, the guess_number should be incremented.
 *               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
 *               For an invalid guess, the guess_number is not incremented.
 * INPUTS: guess_str -- a string consisting of the guess typed by the user
 * OUTPUTS: the following are only valid if the function returns 1 (A valid guess)
 *          *one -- the first guess value (between 1 and 8)
 *          *two -- the second guess value (between 1 and 8)
 *          *three -- the third guess value (between 1 and 8)
 *          *four -- the fourth color value (between 1 and 8)
 * RETURN VALUE: 1 if the guess string is valid (the guess contains exactly four
 *               numbers between 1 and 8), or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess) 
 *               or an error message (invalid guess)
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 */
int
make_guess (const char guess_str[], int* one, int* two, 
	    int* three, int* four)
{
//  One thing you will need to read four integers from the string guess_str, using a process
//  similar to set_seed
//  The statement, given char post[2]; and four integers w,x,y,z,
//  sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post)
//  will read four integers from guess_str into the integers and read anything else present into post
//  The return value of sscanf indicates the number of items sucessfully read from the string.
//  You should check that exactly four integers were sucessfully read.
//  You should then check if the 4 integers are between 1-8. If so, it is a valid guess
//  Otherwise, it is invalid.  
//  Feel free to use this sscanf statement, delete these comments, and modify the return statement as needed

char post[2] = { 0 } ;
int w, x, y, z ;

if (sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post) != 4) { 	//Check that the user guess is only four inputs
	printf("make_guess: invalid guess\n") ;				//If not return error
	return 0;
}

if (post[0] != 0) {					//Check that each of the inputs were strictly integers
	printf("make_guess: invalid guess\n") ;		//If not return error
	return 0;			
}

if ( !( 1 <= w ) || !(w <= 8)) {			//Check that each of the integer inputs are between 1 and 8
	printf("make_guess: invalid guess\n") ;		//If not return error
	return 0;
}

if ( !( 1 <= x ) || !(x <= 8)) {
	printf("make_guess: invalid guess\n") ;
	return 0;
}

if ( !( 1 <= y ) || !(y <= 8)) {
	printf("make_guess: invalid guess\n") ;
	return 0;
}

if ( !( 1 <= z ) || !(z <= 8)) {
	printf("make_guess: invalid guess\n") ;
	return 0;
}

*one = w ;		//Store user guess at required addresses
*two = x ;
*three = y ;
*four = z ;

int guess[4] = {w, x, y, z} ;						//Initialize and fill arrays for the user guess, the solution, and pair indicators for all numbers
int solution[4] = {solution1, solution2, solution3, solution4} ;
int solpairs[4] = {} ;
int guesspairs[4] = {} ;
int match = 0;				//Initialize variables for numbers of matches and mismatches to zero
int mismatch = 0;

for(int k = 0; k <= 3; k++) {		//Iterate through solution and guess arrays to find matches at the same indices
	if (guess[k] == solution[k]) {
		match ++ ;		//If match increment matches variable and set pair indicators for both numbers to 1
		guesspairs[k] = 1 ;
		solpairs[k] = 1 ;
	}
}

for (int j = 0; j <= 3; j++) {			//For each unpaired guess look through the whole solution array to find an unpaired misplaced match
	for (int i = 0; i <=3; i++) {
		if (guesspairs[j] == 1) {
			break ;
		}
		if (guess[j] == solution[i] && solpairs[i] != 1) {
			solpairs[i] = 1 ;				//If an unpaired misplaced match is found increment mismatch, set the solution pair indicator to 1, and move on to next unpaired guess
			mismatch ++ ;
			break ;	
		}
	}
}

printf("With guess %d, you got %d perfect matches and %d misplaced matches.\n", guess_number, match, mismatch) ; 	//Display guess number, number of matches, and number of misplaced matches

guess_number++ ;		//Increment guess number


    return 1;
}


