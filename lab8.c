#include <stdio.h>
#include <math.h>

int factorial(int N) { // This is the factorial function from the previous assignment
    int fact = 1, i;

    for (i = 1; i <= N; i++) {
        fact *= i;
    }

    return fact;
}

double expo(double x, double epsilon) { // This calculates e^x for some value of x using a Taylor Series
    double taylor = 1.0; 
    double sum = taylor; 
    int i = 1;

    while (taylor > epsilon) { // When a Taylor Series term has size less then the "tolerance" given, the function will stop calculating terms
        taylor = (taylor * x) / factorial(i); // This uses the previously created factorial function
        sum += taylor;           
        i++;
    }

    return sum;
}

int main() {
    int n = 51;
    double start = 0.0;
    double end = 1.0;
    double epsilon = 1e-7;
    double step = (end - start) / (n - 1);
    double array[n];
    double expo_array[n];

    for (int i = 0; i < n; i++) { // This generates an evenly spaced array from 0 to 1
        array[i] = start + i * step;
    }

    for (int i = 0; i < n; i++) {
        expo_array[i] = expo(array[i], epsilon); // This applies my exponential function to the array generated just above
    }

    FILE *file = fopen("expo_data_c.txt", "w");

    fprintf(file, "x e^x\n");
    
    for (int i = 0; i < n; i++) {
        fprintf(file, "%f %f\n", array[i], expo_array[i]); //This creates a text file with both the array and the array applied to my exponential function
    }

    fclose(file);

    return 0;
}