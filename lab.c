#include <stdio.h>
#include <math.h>

int factorial(int N) {
    int fact = 1, i;

    for (i = 1; i <= N; i++) {
        fact *= i;
    }

    return fact;
}


int ex(){
    double num = 3.0;
    double res;
    res = exp(num);
    printf("e raised to the power of %.2lf is %.2lf", num, res);
    return(0);
}


int natlog(){
    double num = 3.0;
    double res;
    res = log(num);
    printf("The natural log of %.2f is %.2f\n ", num, res);
    return(0);
}



int main(){
    int N = 5;
    int fact = factorial(N);
    printf("Factorial of %d is %d", N, fact);
    ex();
    natlog();
    
    return(0);
}
