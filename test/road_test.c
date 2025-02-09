#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TESTS       1000
#define MAX_OP_SIZE 1000

#include "../src/crossroads.h"

Road queue = {0};
int element_amounts[TESTS] = {0};
long long element_sum = 0, max_sum = 0;
Car test_car = {0};

void lane_add_test(bool left) {
  for (int i = 0; i < TESTS; i++) {
    for (int j = 0; j < element_amounts[i]; j++) {
      add(&queue, left, test_car);
    }
    element_sum += element_amounts[i];

    assert(cars_amount(&queue, left) == element_sum);
    if (left) {
      assert(queue.left_first == 0);
      assert(queue.left_last == element_sum);
    } else {
      assert(queue.main_first == 0);
      assert(queue.main_last == element_sum);
    }
  }
}

void lane_del_test(bool left) {
  for (int i = 0; i < TESTS; i++) {
    for (int j = 0; j < element_amounts[i]; j++) {
      del(&queue, left);
    }
    element_sum -= element_amounts[i];

    assert(cars_amount(&queue, left) == element_sum);
    if (left) {
      assert(queue.left_first == max_sum - element_sum);
      assert(queue.left_last == max_sum);
    } else {
      assert(queue.main_first == max_sum - element_sum);
      assert(queue.main_last == max_sum);
    }
  }
}

int main(void) {
  srand(time(NULL));

  for (int i = 0; i < TESTS; i++) {
    element_amounts[i] = rand() % MAX_OP_SIZE;
    max_sum += element_amounts[i];
  }

  lane_add_test(true);
  assert(element_sum == max_sum);
  lane_del_test(true);
  assert(element_sum == 0);
  lane_add_test(false);
  assert(element_sum == max_sum);
  lane_del_test(false);
  assert(element_sum == 0);

  printf("Lanes work properly\n");
  return 0;
}
