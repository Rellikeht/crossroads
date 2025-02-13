/*
 * Randomized tests for lanes of a road (queues)
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TESTS          100
#define MAX_BATCH_SIZE 1000

#include "../src/crossroads.h"

Road queue = {0};
long long element_amounts[TESTS] = {0};
long long element_sum = 0, max_sum = 0;
Car test_car = {0};
long long take_id = 0;

void lane_add_test(bool left) {
  for (int i = 0; i < TESTS; i++) {
    for (int j = 0; j < element_amounts[i]; j++) {
      add(&queue, left, test_car);
      test_car.id++;
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
      Car car = del(&queue, left);
      assert(car.id == take_id);
      take_id++;
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

void lane_moving_test(bool left) {
  for (int i = 0; i < TESTS * MAX_BATCH_SIZE * 2; i++) {
    for (int j = 0; j < element_amounts[i % TESTS]; j++) {
      add(&queue, left, test_car);
      test_car.id++;
    }
    assert(cars_amount(&queue, left) == element_amounts[i % TESTS]);
    for (int j = 0; j < element_amounts[i % TESTS]; j++) {
      Car car = del(&queue, left);
      assert(car.id == take_id);
      take_id++;
    }
  }
}

int main(void) {
  srand(time(NULL));

  for (int i = 0; i < TESTS; i++) {
    element_amounts[i] = rand() % MAX_BATCH_SIZE;
    max_sum += element_amounts[i];
  }

  lane_add_test(true);
  assert(element_sum == max_sum);
  printf("Right lane adding works\n");
  fflush(stdout);

  lane_del_test(true);
  assert(element_sum == 0);
  printf("Right lane deleting works\n");
  fflush(stdout);

  lane_moving_test(true);
  assert(element_sum == 0);
  printf("Right lane moving works\n");
  fflush(stdout);

  lane_add_test(false);
  assert(element_sum == max_sum);
  printf("Left lane adding works\n");
  fflush(stdout);

  lane_del_test(false);
  assert(element_sum == 0);
  printf("Left lane deleting works\n");
  fflush(stdout);

  lane_moving_test(false);
  assert(element_sum == 0);
  printf("Left lane moving works\n");
  fflush(stdout);

  printf("Lanes work properly\n");
  return 0;
}
