/*
 * TODO randomized tests for whole simulation
 */

#include "../src/crossroads.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_CARS 10000

int main(void) {
  srand(time(NULL));
  int cars_amount = rand() % MAX_CARS;
  int steps_amount = 2 * cars_amount + 1;

  printf("Simulation tests will get here soon!\n");
  return 0;
}
