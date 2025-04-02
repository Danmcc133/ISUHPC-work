#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

// This is a function to normalize vector using 2-norm
void normalize_2norm(double *v, double *v_normalized, int N, int num_threads) {
    double norm = 0.0;
    #pragma omp parallel for reduction(+:norm) num_threads(num_threads)
    for (int i = 0; i < N; i++) {
        norm += v[i] * v[i];
    }
    norm = sqrt(norm);

    #pragma omp parallel for num_threads(num_threads)
    for (int i = 0; i < N; i++) {
        v_normalized[i] = v[i] / norm;
    }
}

// This is a function to normalize vector using max norm
void normalize_max_norm(double *u, double *u_normalized, int N, int num_threads) {
    double max_val = 0.0;
    #pragma omp parallel for reduction(max:max_val) num_threads(num_threads)
    for (int i = 0; i < N; i++) {
        if (u[i] > max_val) {
            max_val = u[i];
        }
    }

    #pragma omp parallel for num_threads(num_threads)
    for (int i = 0; i < N; i++) {
        u_normalized[i] = u[i] / max_val;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number_of_threads>\n", argv[0]);
        return 1;
    }

    int num_threads = atoi(argv[1]);
    int N = 1000000; // This is the length of the vectors u and v, can be chamged as necessary
    double *v = (double *)malloc(N * sizeof(double));
    double *v_normalized = (double *)malloc(N * sizeof(double));
    double *u = (double *)malloc(N * sizeof(double));
    double *u_normalized = (double *)malloc(N * sizeof(double));

    // This initializes the vectors, this can be changed if needed
    for (int i = 0; i < N; i++) {
        v[i] = 1.0;
        u[i] = i + 1;
    }

    normalize_2norm(v, v_normalized, N, num_threads);
    normalize_max_norm(u, u_normalized, N, num_threads);

    // This outputs the first and last entries of the normalized vectors
    printf("2-norm normalized vector: first entry = %f, last entry = %f\n", v_normalized[0], v_normalized[N-1]);
    printf("Max-norm normalized vector: first entry = %f, last entry = %f\n", u_normalized[0], u_normalized[N-1]);

    // This frees the allocated memory
    free(v);
    free(v_normalized);
    free(u);
    free(u_normalized);

    return 0;
}