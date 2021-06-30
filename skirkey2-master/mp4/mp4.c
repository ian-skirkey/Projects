/* This program takes two user input integers and finds all of the
semiprime numbers between and including the two inputs using
functions to check if a number is prime, as well as check if a number is
a factor of another and if the quotient of two numbers is prime.
*/
#include <stdio.h>

int main()
{
    int num1, num2 ;
    printf("Input two numbers: "); //read user input and store in num1 and num2
    scanf("%d %d", &num1, &num2);
    print_semiprimes(num1, num2); // pass num1 and num2 into print_semiprimes function
    return 0;
}

int print_semiprimes(int a, int b) {
    int flag = 0;
        for(int n = a; n <= b; n++) {	//cycle through all numbers a-b and check if they are semiprimes
           for(int k = 2; k <= n-1; k++) {
               if(n%k == 0 && is_prime(k) == 1 && is_prime((n/k)) == 1) {
                   printf("%d ", n) ;
                   flag = 1 ; //at least one semiprime has been found so set flag to 1
		   break ; 	//don't print a semiprime more than once (on a different divisor check) 
               }
           } 
        }
        return flag ; //1 when at least one semiprime is found, 0 otherwise 
    }
    
    int is_prime(int number) {
        for(int i = 2; i <= number/2; ++i)   // checks whether number is prime (ret 1 = prime, 0 = not prime)
    {
        if(number%i == 0)
        {
         return 0;   
        }
    }
    return 1;
    }
