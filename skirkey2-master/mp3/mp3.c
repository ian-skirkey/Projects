/*This program calculates and prints each digit
in a row of Pascal's Triangle which is determined by a user
input value using a general mathematical algorithm to
determine the kth digit of the nth row in the triangle*/

int main()
{
    double n;	//defining variables with types fit to hold the values of the operations
    unsigned long coef = 1;
    printf("Enter the row index : ");	//print prompt to user
    scanf("%lf", &n) ;			//read user input
    for(double k = 0; k <= n; k++) {	//loop mathematical algorithm until final digit in the row is reached
        if (k == 0) {
            printf("1 ");
        }
        else{
        coef = coef * ((n + 1 - k)/k) ;
        printf("%lu ", coef) ;
        }
    }
    

    return 0;			//halt
}
