#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LOWER_LIMIT 1
#define UPPER_LIMIT 40
#define NUM_TRAPEZOIDS 10e6

double function_to_integrate(double x);
double trapezoidal_integration(double a, double b, int n);

int main(int argc, char* argv[]) {
  double result;
  double a = LOWER_LIMIT, b = UPPER_LIMIT;
  int n = NUM_TRAPEZOIDS;

  if (argc > 1) {
    a = strtol(argv[1], NULL, 10);
    b = strtol(argv[2], NULL, 10);
    n = strtol(argv[3], NULL, 10);
  }

  clock_t start_time = clock();
  result = trapezoidal_integration(a, b, n);
  clock_t end_time = clock();

  double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

  printf("Using n = %d trapezoids, our approximation \n", n);
  printf("of the integral from %f to %f is = %.10f\n", a, b, result);
  printf("Sequential Time: %.6f seconds\n", elapsed_time);

  return 0;
}

double trapezoidal_integration(double a, double b, int n) {
  double integral, dx;
  int k;

  dx = (b - a) / n;
  integral = (function_to_integrate(a) + function_to_integrate(b)) / 2.0;

  for (k = 1; k <= n - 1; k++) {
    integral += function_to_integrate(a + k * dx);
  }
  
  integral = integral * dx;

  return integral;
}

double function_to_integrate(double x) {
  double result;
  result = x * x;
  return result;
}