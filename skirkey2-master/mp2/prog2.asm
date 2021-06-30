
; This program reads a user input postfix mathematical expression and evaluates it using a stack.
; As characters are read, if the character is a number, then it gets pushed to the stack, and if 
; the character is an operator, then two numbers are popped from the stack and the operation signified
; by the operator is performed in a subroutine which then pushes the result to the stack, and when the
; user inputs an equals sign, then the result is popped from the stack, stored in R5, converted to its
; ASCII representation, and then displayed to the screen. 
.ORIG x3000
	
;your code goes here
	
NXTIN GETC ; read and echo character to screen
	OUT ;
	LD R1, EQUALS ;  	If the character is '=' then branch to end
	NOT R1, R1 ;
	ADD R1, R1, #1 ;
	ADD R1, R0, R1 ;
	BRz CHKSTK ;
	LD R1, SPACE ; 		If the character is a space, then check for next charcter
	NOT R1, R1 ;
	ADD R1, R1, #1 ;
	ADD R1, R0, R1 ;
	BRz NXTIN ;
	LD R1, AST ;		Series of tests which check areas of the ASCII table 
	NOT R1, R1 ;		to see if the character being input is valid 
	ADD R1, R1, #1 ;	and if not, branch to printing invalid and halting
	ADD R1, R0, R1 ;
	BRn INVLD ;
	LD R1, APST ;
	NOT R1, R1 ;
	ADD R1, R1, #1 ;
	ADD R1, R0, R1 ;
	BRz INVLD ;
	LD R1, PRD ;
	NOT R1, R1 ;
	ADD R1, R1, #1 ;
	ADD R1, R0, R1 ;
	BRz INVLD ; 
	LD R1, CRT ;		If character is '^' then branch to part of code which
	NOT R1, R1 ;		handles operators
	ADD R1, R1, #1 ;	
	ADD R1, R0, R1 ;
	BRz OPRTR ; 
	LD R1, NINE ;
	NOT R1, R1 ;
	ADD R1, R1, #1 ;
	ADD R1, R0, R1 ;
	BRp INVLD ;
	LD R1, ZERO ;		Last check to see if character is a number, so if not
	NOT R1, R1 ;		then branch to operator part of code
	ADD R1, R1, #1 ;
	ADD R1, R0, R1 ;
	BRn OPRTR ;
	LD R1, OFFNUM ;
	ADD R0, R0, R1 ; 	Convert ASCII to its numerical value and then push the
	JSR PUSH ;			number to the stack
	BRnzp NXTIN ;		Loop back to get next character
OPRTR ST R0, OP ;
	JSR POP ;
	ADD R5, R5, #-1 ;
	BRz INVLD ;
	AND R5, R5, #0 ;
	ST R0, OP1 ;		Pop two numbers from the stack and store them in memory
	JSR POP ;			along with the operator
	ADD R5, R5, #-1 ;
	BRz INVLD ;
	AND R5, R5, #0 ;	
	ST R0, OP2 ;
	LD R2, OP ;
	LD R1, AST ;		Series of checks to determine which operator we have and
	NOT R1, R1 ;		to jump to the correct operator subroutine
	ADD R1, R1, #1 ;
	ADD R1, R2, R1 ;
	BRnp SKIP1 ;
	JSR MUL ;
	BRnzp NXTIN ;
SKIP1 LD R1, DIVI ;
	NOT R1, R1 ;
	ADD R1, R1, #1 ;
	ADD R1, R2, R1 ;
	BRnp SKIP2 ;
	JSR DIV ;
	BRnzp NXTIN ;
SKIP2 LD R1, ADDIT ;
	NOT R1, R1 ;
	ADD R1, R1, #1 ;
	ADD R1, R2, R1 ;
	BRnp SKIP3 ;
	JSR PLUS ;
	BRnzp NXTIN ;
SKIP3 LD R1, MINUS ;
	NOT R1, R1 ;
	ADD R1, R1, #1 ;
	ADD R1, R2, R1 ;
	BRnp SKIP4 ;
	JSR MIN ;
	BRnzp NXTIN ;
SKIP4 JSR EXP ;
	BRnzp NXTIN ;
CHKSTK LD R3, STACK_TOP	; 		Make sure that there is only one value in the stack,if so
	LD R4, STACK_START	;		pop it off and store it in R5 then branch to print hex code
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	ADD R3, R3, #-1 ;
	BRnp INVLD ; 
	JSR POP ;
	AND R5, R5, #0 ;
	ADD R5, R0, R5 ;
	ST R5, RSLT ;
	BRnzp PRINT_HEX ;
INVLD LEA R0, INV ;				Print "Invalid Expression" and then halt the program
	PUTS ;
	HALT ;




SPACE   .FILL x0020
NEW_LINE        .FILL x000A
CHAR_RETURN     .FILL x000D
OFFNUM			.FILL #-48
OP 				.FILL x0000  ; Where operator and numbers are stored
OP1 			.FILL x0000
OP2 			.FILL x0000
EQUALS			.FILL x003D  ; Stores ASCII value referrences
AST				.FILL x002A
APST			.FILL x002C
PRD				.FILL x002E
CRT				.FILL x005E
NINE			.FILL x0039
ZERO			.FILL x0030
DIVI			.FILL x002F
ADDIT			.FILL x002B
MINUS			.FILL x002D
SV_R7			.FILL x0000 ; Saves for R7 when jumping in and out of subroutines
SV_EXP			.FILL x0001
RSLT			.FILL x0000 ; Stores result
OFF1 			.FILL x0030 ; ASCII offset for numbers
OFF2			.FILL x0037 ; ASCII offset for letters
COUNT			.FILL x0003 ; Holds a loop count
TEST 			.FILL x0039 ;
NEG1			.FILL xFFFF ;
PROMPT			.STRINGZ "Enter Postfix Expression: " 
INV				.STRINGZ "Invalid Expression"

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal
PRINT_HEX
	LD R2, RSLT ;     Prints hexadecimal value to screen
NXT AND R1, R1, #0 ;
	AND R3, R3, #0 ;
	AND R4, R4, #0 ;
	AND R5, R5, #0 ; clear registers and set up count
	AND R0, R0, #0 ;
	ADD R1, R1, #3 ;
	ADD R3, R3, #1 ; set up place value holder
CHK	ADD R2, R2, #0 ;
	BRzp SHIFT ;
	ADD R4, R4, R1 ; check if bit is "1" and add appropriate place value
EX  ADD R4, R4, #-1 ; to R5 if so
	BRn ONE ;
    ADD R3, R3, R3 ;
	ADD R4, R4, #0 ;
	BRp EX ;
ONE	ADD R5, R5, R3 ;
SHIFT ADD R2, R2, R2 ; shift occurence count to check next bit
	AND R3, R3, #0 ;
	AND R4, R4, #0 ; reset place value holder and decrement R1 count
	ADD R3, R3, #1 ;
	ADD R1, R1, #-1 ;
	BRzp CHK ;
	ADD R4, R5, #-9 ; if 4 bits checked, check if hex value is a number or a letter
	BRp LTR ;
	LD R0, OFF1 ;
	ADD R0, R0, R5 ;
	BRnzp SKIP ;
LTR LD R0, OFF2 ;    add R5 to appropriate number/letter offset and print character to screen
	ADD R0, R0, R5 ;
SKIP OUT ;
	LD R4, COUNT ;
	ADD R4, R4, #-1 ; decrement count for how many sets of 4 bits have been checked and store in memory
	ST R4, COUNT ;
	ADD R4, R4, #0 ;
	BRzp NXT ;
	LD R5, RSLT ;
	HALT ;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R6 - current numerical output
;
;
EVALUATE

;your code goes here


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
PLUS	
;your code goes here

	LD R3, OP1 ;      Addition subroutine
	LD R4, OP2 ;
	ST R7, SV_R7 ;
	ADD R0, R3, R4 ;
	JSR PUSH ;
	LD R7, SV_R7 ;
	RET
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MIN	
;your code goes here

	AND R0, R0, #0 ;     Subtraction subroutine
	LD R3, OP1 ;
	LD R4, OP2 ;
	ST R7, SV_R7 ;
	NOT R3, R3 ;
	ADD R3, R3, #1 ;
	ADD R0, R3, R4 ;
	JSR PUSH ;
	LD R7, SV_R7 ;
	RET
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MUL	
;your code goes here

	AND R0, R0, #0 ;     Multiplication subroutine
	LD R3, OP1 ;
	LD R4, OP2 ;
	ST R7, SV_R7 ;
REP	ADD R4, R4, #-1 ;
	BRn DONE ;
    ADD R0, R0, R3 ;
	BRnzp REP ;
DONE JSR PUSH ;
	LD R7, SV_R7 ;
	RET
		
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
DIV	
;your code goes here

	AND R0, R0, #0 ;    Division subroutine
	LD R3, OP1 ;
	BRz INVLD ;
	LD R4, OP2 ;
	ST R7, SV_R7 ;
	NOT R3, R3 ;
	ADD R3, R3, #1 ;
NX	ADD R4, R4, R3 ;
	BRn FIN ;
	ADD R0, R0, #1 ;
	BRnzp NX ;
FIN JSR PUSH ;
	LD R7, SV_R7 ;
	RET	
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
EXP
;your code goes here

	AND R0, R0, #0 ;     Exponent subroutine
	LD R3, OP1 ;
	LD R4, OP2 ;
	ST R7, SV_R7 ;
LOOP ADD R3, R3, #-1 ;
	BRnz BACK ; 
	LD R1, OP2 ;
RE	ADD R1, R1, #-1 ;
	BRn OVER ;
    ADD R0, R0, R4 ;
	BRnzp RE ;	
OVER ST R0, SV_EXP ;
	AND R0, R0, #0 ;
	LD R4, SV_EXP ;
	BRnzp LOOP ;
BACK LD R0, SV_EXP ;
	JSR PUSH ;
	LD R7, SV_R7 ;
	RET	
	
;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACk_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R3
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET


POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP	.FILL x4000	;


.END
