#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

double function(double x) {
    return exp(-x * x); // This function can be changed as needed, although its a great example for numerical integration
}

// This is the adaptive quadrature function
double adaptquad(double (*f)(double), double a, double b, double tol, int depth) {
    double mid = (a + b) / 2.0;
    double h = (b - a) / 2.0;
    double fa = f(a);
    double fb = f(b);
    double fm = f(mid);
    double I1 = h * (fa + fb);
    double I2 = h / 2.0 * (fa + 2.0 * fm + fb);

    if (fabs(I2 - I1) < tol || depth > 20) {
        return I2 + (I2 - I1) / 15.0;
    } else {
        double left, right;
        #pragma omp parallel sections
        {
            #pragma omp section
            left = adaptquad(f, a, mid, tol / 2.0, depth + 1);
            #pragma omp section
            right = adaptquad(f, mid, b, tol / 2.0, depth + 1);
        }
        return left + right;
    }
}

int main() {
    // a and b are the integration limits and can be changed as needed
    double a = 0.0;
    double b = 1.0;
    double tol = 1e-6; // This can be changed as needed
    int thread_counts[] = {1, 2, 4, 8, 16};
    int num_tests = sizeof(thread_counts) / sizeof(thread_counts[0]);

    for (int i = 0; i < num_tests; i++) {
        int num_threads = thread_counts[i];
        omp_set_num_threads(num_threads);
        double start_time = omp_get_wtime();

        double result;
        #pragma omp parallel
        {
            #pragma omp single
            result = adaptquad(function, a, b, tol, 0);
        }

        double end_time = omp_get_wtime();
        printf("Threads: %d, Result: %.10f, Time: %.6f seconds\n", num_threads, result, end_time - start_time);
    }

    return 0;
}