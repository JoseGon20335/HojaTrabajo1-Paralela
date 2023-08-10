#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define LOWER_LIMIT 1
#define UPPER_LIMIT 40
#define NUM_TRAPEZOIDS 10e6

double function_to_integrate(double x);

double trapezoidal_integration(double a, double b, int n, double* global_sum);

int main(int argc, char *argv[]) {
  double total_sum = 0;
  double result;
  double a = LOWER_LIMIT, b = UPPER_LIMIT;
  int n = NUM_TRAPEZOIDS;
  int num_threads;
  
  if (argc > 1) {
    a = strtol(argv[1], NULL, 10);
    b = strtol(argv[2], NULL, 10);
    num_threads = strtol(argv[3], NULL, 10);
  }
  
  double start_time = omp_get_wtime();
  
  #pragma omp parallel num_threads(num_threads) reduction(+: total_sum)
  result = trapezoidal_integration(a, b, n, &total_sum);

  double end_time = omp_get_wtime();
  double elapsed_time = end_time - start_time;
  
  printf("Using %d trapezoids, our approximation \n", n);
  printf("of the integral from %f to %f is = %.10f\n", a, b, total_sum);
  printf("Execution time: %.10f seconds\n", elapsed_time);
  
  return 0;
}

double trapezoidal_integration(double a, double b, int n, double* global_sum) {
  double integral, dx, x, local_sum;
  double local_lower, local_upper;
  int i, local_n;

  int thread_ID = omp_get_thread_num();
  int num_threads = omp_get_num_threads();
  
  dx = (b - a) / n;

  local_n = n / num_threads;
  local_lower = a + thread_ID * local_n * dx;
  local_upper = local_lower + local_n * dx;

  local_sum = (function_to_integrate(local_lower) + function_to_integrate(local_upper)) / 2.0;
  
  for (i = 1; i <= local_n - 1; i++) {
    x = local_lower + i * dx;
    local_sum += function_to_integrate(x);
  }
  
  local_sum = local_sum * dx;
  *global_sum += local_sum;
}

double function_to_integrate(double x) {
  double result;
  result = x * x;
  return result;
}