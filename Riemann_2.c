#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LOWER_LIMIT 1
#define UPPER_LIMIT 40
#define NUM_TRAPEZOIDS 10e6

double func(double x);
double trapezoidal_integration(double lower, double upper, int num_segments);

int main(int argc, char *argv[]) {
  clock_t start_time;
  double result;
  double lower_limit = LOWER_LIMIT, upper_limit = UPPER_LIMIT;
  int num_segments = NUM_TRAPEZOIDS;
  double segment_width;
  
  if (argc > 1) {
    lower_limit = strtol(argv[1], NULL, 10);
    upper_limit = strtol(argv[2], NULL, 10);
  }
  
  start_time = clock();
  result = trapezoidal_integration(lower_limit, upper_limit, num_segments);
  start_time = clock() - start_time;
  
  double time_taken = ((double)start_time) / CLOCKS_PER_SEC;
  
  printf("Using %d trapezoids, our approximation \n", num_segments);
  printf("of the integral from %f to %f is = %.10f\n", lower_limit, upper_limit, result);
  printf("Execution time: %.10f seconds\n", time_taken);
  
  return 0;
}

double trapezoidal_integration(double lower, double upper, int num_segments) {
  double integral, segment_width;
  int i;
  
  segment_width = (upper - lower) / num_segments;
  
  integral = (func(lower) + func(upper)) / 2.0;
  
  for (i = 1; i <= num_segments - 1; i++) {
    integral += func(lower + i * segment_width);
  }
  
  integral = integral * segment_width;
  
  return integral;
}

double func(double x) {
  double result;
  result = x * x;
  return result;
}