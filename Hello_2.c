#include <omp.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

void openmp_hello(void);

int main(int argc, char *argv[]) {

  int thread_count = strtol(argv[1], NULL, 10);

  #pragma omp parallel num_threads(thread_count)
  openmp_hello();

  return 0;
}

void openmp_hello(void) {
  int thread_num = omp_get_thread_num();

  if(thread_num%2==0){
    printf("Hilo %d\n", thread_num);
  }
  else{
    printf("Happy %d\n", thread_num);
  }
}