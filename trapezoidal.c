#include <stdio.h>
#include <math.h>
#include <mpi.h>


double f(double x) {
    return x * x; // This is the function to be integrated f(x) = x^2, can be changed as necessary
}

double trapezoidal_rule(double a, double b, int n, double h) {
    double integral = (f(a) + f(b)) / 2.0;
    for (int i = 1; i <= n - 1; i++) {
        double x = a + i * h;
        integral += f(x);
    }
    integral *= h;
    return integral;
}

int main(int argc, char** argv) {
    int rank, size;
    double a = 0.0, b = 1.0; // These are the integration limits
    int n = 1024; // Thus can be changed as necessary
    double h, local_a, local_b, local_integral, total_integral;
    int local_n;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    h = (b - a) / n; // This is the step size
    local_n = n / size; // This is the number of trapezoids for each process

    // This defines "local intervals"
    local_a = a + rank * local_n * h;
    local_b = local_a + local_n * h;

    // This alculates a "local integral"
    local_integral = trapezoidal_rule(local_a, local_b, local_n, h);

    // This reduces all "local integrals" to the total integral
    MPI_Reduce(&local_integral, &total_integral, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("With n = %d trapezoids, the integral from %.2f to %.2f is %.15f\n", n, a, b, total_integral);
    }

    MPI_Finalize();
    return 0;
}