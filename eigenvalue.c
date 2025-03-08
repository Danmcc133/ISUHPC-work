#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// This function generates a random 6x6 lower triangular matrix with 1's on the diagonal
// The output is a random matrix witht he above paramters
void matrixgen(double L[6][6]) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if (i < j) {
                L[i][j] = 0.0;
            } else if (i == j) {
                L[i][j] = 1.0;
            } else {
                L[i][j] = (double)rand() / RAND_MAX;
            }
        }
    }
}

// This function defines matrix multiplication between two 6x6 matrices
// The input is two 6x6 matrices
// The output is the product of the input matrices, also a 6x6 matrix
void matrixmult(double A[6][6], double B[6][6], double C[6][6]) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            C[i][j] = 0.0;
            for (int k = 0; k < 6; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// This is the Power Iteration method to find the largest eigenvalue
// The input is a 6x6 matrix and an initial guess for the eigenvector
// The output is the largest eigenvalue of the input matrix
double power(double A[6][6], double initialGuess[6]) {
    double b_k[6];
    for (int i = 0; i < 6; i++) b_k[i] = initialGuess[i];

    for (int iter = 0; iter < 100; iter++) {
        double b_k1[6] = {0};
        for (int i = 0; i < 6; i++) {
            // This step has the function repeatedy multiply a vector by the input matrix
            for (int j = 0; j < 6; j++) {
                b_k1[i] += A[i][j] * b_k[j]; 
            }
        }

        double norm = 0.0;
        for (int i = 0; i < 6; i++) norm += b_k1[i] * b_k1[i];
        norm = sqrt(norm);

        for (int i = 0; i < 6; i++) b_k[i] = b_k1[i] / norm; // This "normalizes" the vector
        if (norm < 1e-7) break; // This will have the function stop once the "tolerance" has been reached
        // This can be changed if a higher or lower tolerance s desired
    }

    double eigenvalue = 0.0;
    for (int i = 0; i < 6; i++) {
        // This produces an eigenvalue from the "Rayleigh-Quotient"
        double temp = 0.0;
        for (int j = 0; j < 6; j++) temp += A[i][j] * b_k[j];
        eigenvalue += b_k[i] * temp;
    }

    return eigenvalue;
}

// This is the Inverse Iteration method to find the eigenvalue closest to the initial guess mu
// The input is a 6x6 Matrix and an initial guess for the eigenvector
// The output is the eigenvalue closest to the initial guess mu
double inverse(double A[6][6], double initialGuess[6]) {
    double mu = 1e-5;  // This can (and should) be changed if the parameters for the matrix are changed
    double I[6][6] = {0};
    for (int i = 0; i < 6; i++) I[i][i] = 1.0;

    double B[6][6];
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            B[i][j] = A[i][j] - mu * I[i][j];
        }
    }

    double b_k[6];
    for (int i = 0; i < 6; i++) b_k[i] = initialGuess[i];

    for (int iter = 0; iter < 100; iter++) { 
        double b_k1[6] = {0};
        for (int i = 0; i < 6; i++) { 
            // This solves B * b_k1 = b_k by Gaussian elimination for b_k1
            b_k1[i] = b_k[i] / B[i][i];
            for (int j = i + 1; j < 6; j++) b_k[j] -= B[j][i] * b_k1[i];
        }

        double norm = 0.0;
        for (int i = 0; i < 6; i++) norm += b_k1[i] * b_k1[i];
        norm = sqrt(norm);

        for (int i = 0; i < 6; i++) b_k[i] = b_k1[i] / norm; // This normalizes the vector
        if (norm < 1e-7) break; // Once again, if the "tolerance" is met then the function will stop
    }

    double eigenvalue = 0.0;
    for (int i = 0; i < 6; i++) {
        // This produces an eigenvalue from the Rayleigh Quotient
        double temp = 0.0;
        for (int j = 0; j < 6; j++) temp += A[i][j] * b_k[j];
        eigenvalue += b_k[i] * temp;
    }

    return eigenvalue;
}

// This is the Rayleigh-Quotient Iteration method to find an eigenvalue
// The input is a 6x6 matrix and the initial guess for the eigenvector
// The output is the eigenvalue
double rayleigh(double A[6][6], double initialGuess[6]) {
    double b_k[6];
    for (int i = 0; i < 6; i++) b_k[i] = initialGuess[i];

    double mu = 0.0;  // This is the initial guess for the eigenvalue and can be changed as necessary

    for (int iter = 0; iter < 100; iter++) {
        double b_k1[6] = {0}; // This solves (A - mu * I) * b_k1 = b_k by Gaussian elimination for b_k1
        for (int i = 0; i < 6; i++) {
            b_k1[i] = b_k[i] / (A[i][i] - mu);
            for (int j = i + 1; j < 6; j++) b_k[j] -= (A[j][i] - mu) * b_k1[i];
        }

        double norm = 0.0;
        for (int i = 0; i < 6; i++) norm += b_k1[i] * b_k1[i];
        norm = sqrt(norm);

        for (int i = 0; i < 6; i++) b_k[i] = b_k1[i] / norm; // This normalizes the vector
        mu = 0.0;
        for (int i = 0; i < 6; i++) {
            // This produces an eigenvalue from the Rayleigh-Quotient
            double temp = 0.0;
            for (int j = 0; j < 6; j++) temp += A[i][j] * b_k[j];
            mu += b_k[i] * temp;
        }
        if (norm < 1e-7) break; // This causes the function to stop if the "tolerance" is met
    }

    return mu;
}

int main() {
    // This is the main function of the script and uses the three methods to find eigenvalues
    // A 6x6 lower triangular matrix is generated, its transpose is calculated and then LL^T is calculated
    // The three eigenvalue functions will then work on A = LL^T
    // The output should be three distinct eigenvalues with the eigenvalue for power iteration being the largest
    srand(time(NULL));  // This is for the random matrix generation

    double L[6][6];
    double A[6][6];
    double initialGuess[6] = {1, 1, 1, 1, 1, 1};  // This is the initial guess for the eigenvector

    matrixgen(L); // This generates L

    double LT[6][6];  // This calculates the transpose of L
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++)
            LT[j][i] = L[i][j];

    matrixmult(L, LT, A); // This computes A = LL^T

    // This computes eigenvalues using the three different methods
    double ev_power = power(A, initialGuess);
    double ev_inverse = inverse(A, initialGuess);
    double ev_rayleigh = rayleigh(A, initialGuess);

    // This labels and prints the results to avoid any confusion
    printf("Eigenvalue (Power Iteration): %lf\n", ev_power);
    printf("Eigenvalue (Inverse Iteration): %lf\n", ev_inverse);
    printf("Eigenvalue (Rayleigh Quotient Iteration): %lf\n", ev_rayleigh);

    return 0;
}