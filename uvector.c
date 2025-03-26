#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>

// Structure to pass data to threads
typedef struct {
    int start;
    int end;
    int k;
    double *x;
    double *u;
} ThreadData;

// Function to generate random numbers between 0 and 1
void generate_random_vector(double *vector, int n) {
    for (int i = 0; i < n; i++) {
        vector[i] = (double)rand() / RAND_MAX;
    }
}

// Function to compute u_i = 1 + x_i + (x_i)^2 + ... + (x_i)^k
void *compute_u(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    for (int i = data->start; i < data->end; i++) {
        data->u[i] = 1;
        double x_power = data->x[i];
        for (int j = 1; j <= data->k; j++) {
            data->u[i] += x_power;
            x_power *= data->x[i];
        }
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s #threads N k\n", argv[0]);
        return 1;
    }

    int num_threads = atoi(argv[1]);
    int N = atoi(argv[2]);
    int k = atoi(argv[3]);

    // Allocate memory for vectors x and u
    double *x = (double *)malloc(N * sizeof(double));
    double *u = (double *)malloc(N * sizeof(double));

    // Seed the random number generator
    srand(time(NULL));

    // Generate random vector x
    generate_random_vector(x, N);

    // Create threads
    pthread_t threads[num_threads];
    ThreadData thread_data[num_threads];

    // Calculate the workload for each thread
    int chunk_size = N / num_threads;
    for (int i = 0; i < num_threads; i++) {
        thread_data[i].start = i * chunk_size;
        thread_data[i].end = (i == num_threads - 1) ? N : (i + 1) * chunk_size;
        thread_data[i].k = k;
        thread_data[i].x = x;
        thread_data[i].u = u;
        pthread_create(&threads[i], NULL, compute_u, &thread_data[i]);
    }

    // Wait for threads to finish
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    // Free allocated memory
    free(x);
    free(u);

    return 0;
}