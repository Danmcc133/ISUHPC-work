// Gaussian elimination with partial pivoting
// Polynomial Interpolation
// Leat Square FItting
// Today's Assignment: polynomial_interpolation(x,f,n+1), as well as least squares 
// by solving normal equations
// f(x) = sin(2pi x), x = 0, 0.05,...,0.95,1 (21 points) P_n
// least fitting: m=5 (polynomial of degree 5) P_m
// visualize results in python (plot f, P_n, P_m in one figure) 
// Update git, submit source code/screenshots
// use sample code from slides
// Don't print, just show final results

#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct {
    int rows;
    int cols;
    double **data;
} Matrix;


Matrix create_matrix(int rows, int cols) {
    Matrix mat;
    mat.rows = rows;
    mat.cols = cols;
    mat.data = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++) {
        mat.data[i] = (double *)malloc(cols * sizeof(double));
    }
    return mat;
}


void gaussian_elimination(Matrix A) {
    int n = A.rows;
    for (int i = 0; i < n; i++) {
        // This is the "partial pivoting" step
        for (int k = i + 1; k < n; k++) {
            if (fabs(A.data[i][i]) < fabs(A.data[k][i])) {
                for (int j = 0; j <= n; j++) {
                    double temp = A.data[i][j];
                    A.data[i][j] = A.data[k][j];
                    A.data[k][j] = temp;
                }
            }
        }
        // This is the "forward elimination" step
        for (int k = i + 1; k < n; k++) {
            double t = A.data[k][i] / A.data[i][i];
            for (int j = 0; j <= n; j++) {
                A.data[k][j] -= t * A.data[i][j];
            }
        }
    }
    // This is the "backwards substitution" step
    for (int i = n - 1; i >= 0; i--) {
        A.data[i][n] /= A.data[i][i];
        for (int j = i - 1; j >= 0; j--) {
            A.data[j][n] -= A.data[j][i] * A.data[i][n];
        }
    }
}

void polynomial_interpolation(double x[], double y[], double coeff[], int n) {
    // This function produces the coefficients of the interpolating polynomial
    // The inputs are the interpolation points, function values and the number of interpolation points
    // The output is the vector of interpolation coefficients
    for (int i = 0; i < n; i++) {
        coeff[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        double term = y[i];
        for (int j = 0; j < n; j++) {
            if (i != j) {
                term /= (x[i] - x[j]);
            }
        }
        for (int j = 0; j < n; j++) {
            double prod = term;
            for (int k = 0; k < n; k++) {
                if (k != i && k != j) {
                    prod *= (x[j] - x[k]);
                }
            }
            coeff[j] += prod;
        }
    }
}

void least_squares_fit(double x[], double y[], double coeff[], int n, int degree) {
    // This function creates the "Least Squares Fit" using the "gaussian_elimination" function
    // The inputs are the data points, the function values, the number of data points,
    // and the degree of the associated polynomial
    // The output is a vector of polynomial coefficients
    Matrix A = create_matrix(degree + 1, degree + 2);
    double X[2 * degree + 1];
    for (int i = 0; i <= 2 * degree; i++) {
        X[i] = 0;
        for (int j = 0; j < n; j++) {
            X[i] += pow(x[j], i);
        }
    }
    for (int i = 0; i <= degree; i++) {
        for (int j = 0; j <= degree; j++) {
            A.data[i][j] = X[i + j];
        }
        A.data[i][degree + 1] = 0;
        for (int j = 0; j < n; j++) {
            A.data[i][degree + 1] += y[j] * pow(x[j], i);
        }
    }
    gaussian_elimination(A);
    for (int i = 0; i <= degree; i++) {
        coeff[i] = A.data[i][degree + 1];
    }
}

int main() {
    // The main function uses polynomial interpolation and least squares fitting to approximate f(x)=sin(2pi x)
    // It then copies this data to two different files so that the python script can run it
    const int N = 21;
    const int degree = 5;
    double x[N], y[N];
    double coeff_interp[N], coeff_ls[degree + 1];

    // This generates the "interpolation points"
    for (int i = 0; i < N; i++) {
        x[i] = i * 0.05;
        y[i] = sin(2*M_PI*x[i]);
    }
    
    polynomial_interpolation(x, y, coeff_interp, N);

    least_squares_fit(x, y, coeff_ls, N, degree);

    FILE *f_interp = fopen("coeff_interp.txt", "w");
    FILE *f_ls = fopen("coeff_ls.txt", "w");

    for (int i = 0; i < N; i++) {
        fprintf(f_interp, "%lf\n", coeff_interp[i]);
    }

    for (int i = 0; i <= degree; i++) {
        fprintf(f_ls, "%lf\n", coeff_ls[i]);
    }

    fclose(f_interp);
    fclose(f_ls);

    return 0;
}