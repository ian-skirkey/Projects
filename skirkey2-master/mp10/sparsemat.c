#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>

/* This program implements linked lists to represent sparse matrices given in text files, sorting them in row major order, as well as interfacing with them in other ways such as removing nodes, or adding nodes in the proper locations. There are also functions which add or multiply two sparse matrices together. */



sp_tuples * load_tuples(char* input_file)
{

int row, col ;		//allocate memory for a new matrix
double val ;
sp_tuples * tuples = (sp_tuples*)malloc(sizeof(struct sp_tuples)) ;
sp_tuples_node * node, * head ;
tuples->nz = 0 ;
head = NULL ;


FILE * infile = fopen(input_file, "r") ;	//Open the input file for reading

fscanf(infile, "%d %d", &tuples->m, &tuples->n) ;	//read rowsize and colsize values

fscanf(infile, "%d %d %lf", &row, &col, &val) ;		//read the first node

node = (sp_tuples_node*)malloc(sizeof(struct sp_tuples_node)) ;	//allocate memory for the node
		node->next = head ;	//set the node up as the head of a new list
		head = node ;
		node->value = val ;
		node->row = row ;
		node->col = col ;
		tuples->nz++ ;
		tuples->tuples_head = head ;

while (fscanf(infile, "%d %d %lf", &row, &col, &val) != EOF) {	//Iterate while the file has not yet ended
	/*if (val != 0) {
		node = (sp_tuples_node*)malloc(sizeof(struct sp_tuples_node)) ;
		node->next = head ;
		head = node ;
		node->value = val ;
		node->row = row ;
		node->col = col ;
		tuples->nz++ ;
		
	} */
	
	set_tuples(tuples, row, col, val) ;	//insert new nodes in order
}
//tuples->tuples_head = head ;
fclose(infile) ;

    return tuples;
}

void sort_tuples(sp_tuples * tuples) {

int i ;
sp_tuples_node *current, *max, *last, *maxlast, *nxthead, *head ;
nxthead = NULL ;
head = tuples->tuples_head ;

for (i = 0; i < tuples->nz; i++) {	//Iterate through all nodes
	max = head ;
	maxlast = NULL;
	last = NULL ;
	current = head  ;
	
	while (current != NULL) {
	
	if(max->row * tuples->m + max->col < current->row * tuples->m + current->col) {
		maxlast = last ;
		max = current ; 	//Find the node with the largest index and make it the head of the list
	}
	last = current ;
	current = current->next ;
	}
	
	if (maxlast != NULL) {
		maxlast->next = max->next ;
	}
	if (max == head) {
		head = head->next ;
	}
	max->next = nxthead ;
	nxthead = max ;	
}

tuples->tuples_head = nxthead ;

return ;

}
	



double gv_tuples(sp_tuples * mat_t,int row,int col)
{
sp_tuples_node * current ;
current = mat_t->tuples_head ;

while (current != NULL) {	// Iterate through nodes and return value of node at row col				
	if (current->row == row && current->col == col) {	 
		return current->value ;
	}
	current = current->next ;
}
    return 0;
}
sp_tuples_node * gp_tuples(sp_tuples * mat_t,int row,int col)

{
sp_tuples_node * current ;
current = mat_t->tuples_head ;

while (current != NULL) {
	if (current->row == row && current->col == col) {
		return current ;
	}
	current = current->next ;
}
    return 0;
}


void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{

sp_tuples_node * current = mat_t->tuples_head ;
sp_tuples_node * last = NULL ;
sp_tuples_node * node ;
int flag = 0;

while (current != NULL && flag == 0) {
	if (current->col >= col && current->row >= row && flag == 0) {
		node = (sp_tuples_node*)malloc(sizeof(struct sp_tuples_node)) ;
		node->value = value ;
		node->row = row ;
		node->col = col ;
		if (last ==  NULL) {
			node->next = current ;
			mat_t->tuples_head =  node ;
		}
		if (last != NULL) {
		last->next = node ;
		node->next = current ;
		}
		mat_t->nz++ ;	
		flag = 1 ;
	}
	
	if ( row == current->row && col == current->col) {
		if (value != 0) {
			node->next = current->next ;
			free(current);
			current = node->next ;
			last = node ;
			mat_t->nz-- ;
			continue ;
		}
		if (value == 0) {
			last->next = current->next ;
			free(node) ;
			free(current) ;
			current = last->next ;
			mat_t->nz-- ;
			mat_t->nz-- ;
			continue ;
		}
	}
	last = current ;
	current = current->next ;
}

if (flag == 0 && value != 0) {
	sp_tuples_node * node = (sp_tuples_node*)malloc(sizeof(struct sp_tuples_node)) ;
	node->value = value ;
	node->row = row ;
	node->col = col ;
	last->next = node ;
	node->next = NULL ;
	mat_t->nz++;
}

    return;
}



void save_tuples(char * file_name, sp_tuples * mat_t)
{
FILE * outfile = fopen(file_name, "w") ;
fprintf(outfile, "%d %d\n", mat_t->m, mat_t->n) ;

sp_tuples_node * current = mat_t->tuples_head ;

while (current != NULL) {
	
	fprintf(outfile, "%d %d %lf\n", current->row, current->col, current->value) ;
	current = current->next ;
}
fclose(outfile) ;
	return;
}



sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){

if (matA->m != matB->m || matA->n != matB->n || matB == NULL || matA == NULL) {
	return NULL ;
}

sp_tuples * C = (sp_tuples*)malloc(sizeof(struct sp_tuples)) ;
C->m = matB->m ;
C->n = matB->n ;
C->nz = 0 ;
sp_tuples_node * currentA = matA->tuples_head ;
sp_tuples_node * currentB = matB->tuples_head ;
sp_tuples_node * head = NULL ;
sp_tuples_node * node, * target ;

while (currentA != NULL) {
	node = (sp_tuples_node*)malloc(sizeof(struct sp_tuples_node)) ;
	node->next = head ;
	head = node ;
	node->value = currentA->value ;
	node->row = currentA->row ;
	node->col = currentA->col ;
	C->nz++ ;
	currentA = currentA->next ;
}
C->tuples_head = head ;

while (currentB != NULL) {
	target = gp_tuples(C, currentB->row, currentB->col) ;
	if (target != 0) {
		target->value += currentB->value ;
	}
	if (target == 0) {
		node = (sp_tuples_node*)malloc(sizeof(struct sp_tuples_node)) ;
		node->next = head ;
		head = node ;
		node->value = currentB->value ;
		node->row = currentB->row ;
		node->col = currentB->col ;
		C->nz++ ;	
	}
	currentB = currentB->next ;
}
C->tuples_head = head ;
sort_tuples(C) ;

	return C;
}



sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){ 
    return 0;

}


	
void destroy_tuples(sp_tuples * mat_t){
	
	if (mat_t != NULL) {
		sp_tuples_node * current, *last ;
		
		current = mat_t->tuples_head ;
		last = NULL ;
		
		while (current != NULL) {
			last = current ;
			current = current->next ;
			free(last) ;
		}
		free(mat_t->tuples_head) ;
		free(mat_t) ;
	} 
    return;
}  






