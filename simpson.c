#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

// This is the function to be integrated
double function(double x) {
    return 1.0 + exp(x); // This can be changed as necessary
}

// This is here to pass data to the thread function
typedef struct {
    double a, b, h;
    int start, end, n;
    double* result;
} ThreadData;

// This is a "thread" function to compute the sum
void* compute_sum(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    double x;
    *data->result = 0.0;

    for (int i = data->start; i <= data->end; i++) {
        x = data->a + i * data->h;
        if (i == 0 || i == data->n) {
            *data->result += function(x);
        } else if (i % 2 == 0) {
            *data->result += 2 * function(x);
        } else {
            *data->result += 4 * function(x);
        }
    }

    pthread_exit(0);
}

int main(int argc, char* argv[]) {
    if (argc != 5) {
        printf("Usage: %s <number of threads> <a> <b> <n>\n", argv[0]);
        return 1;
    }

    int num_threads = atoi(argv[1]);
    double a = atof(argv[2]);
    double b = atof(argv[3]);
    int n = atoi(argv[4]);

    // This double checks input
    if (num_threads <= 0 || n <= 0 || a >= b || n % 2 != 0) {
        printf("Invalid input. Ensure n is even and greater than 0.\n");
        return 1;
    }

    double h = (b - a) / n;
    pthread_t threads[num_threads];
    ThreadData data[num_threads];
    double results[num_threads];

    // This creates threads to compute sums
    for (int i = 0; i < num_threads; i++) {
        data[i].a = a;
        data[i].b = b;
        data[i].h = h;
        data[i].n = n;
        data[i].start = i * (n / num_threads);
        data[i].end = (i + 1) * (n / num_threads) - 1;
        if (i == num_threads - 1) {
            data[i].end = n;
        }
        data[i].result = &results[i];
        pthread_create(&threads[i], NULL, compute_sum, &data[i]);
    }

    // This joins threads and accumulates the total sum
    double total_sum = 0.0;
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
        total_sum += results[i];
    }

    double result = (h / 3.0) * total_sum;
    printf("Result: %f\n", result);

    return 0;
}