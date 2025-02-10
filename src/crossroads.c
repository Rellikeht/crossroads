#include "crossroads.h"
#include <stdio.h>

Car empty_car = {.id = -1, .destination = -1};

void add(Road *road, bool left, Car car) {
  Car *lane;
  int_t *last;
  if (left) {
    lane = road->left_lane;
    last = &road->left_last;
  } else {
    lane = road->main_lane;
    last = &road->main_last;
  }
  lane[*last] = car;
  *last = (*last + 1) % ROAD_LENGTH;
}

Car del(Road *road, bool left) {
  Car *lane, result;
  int_t *first;
  if (left) {
    lane = road->left_lane;
    first = &road->left_first;
  } else {
    lane = road->main_lane;
    first = &road->main_first;
  }
  result = lane[*first];
  lane[*first] = empty_car;
  *first = (*first + 1) % ROAD_LENGTH;
  return result;
}

int_t cars_amount(Road *road, bool left) {
  if (left) {
    if (road->left_first <= road->left_last) {
      return road->left_last - road->left_first;
    }
    return ROAD_LENGTH - road->left_first + road->left_last;
  }
  if (road->main_first <= road->main_last) {
    return road->main_last - road->main_first;
  }
  return ROAD_LENGTH - road->main_first + road->main_last;
}

int max_val_ind(int_t *nums, size_t size) {
  int_t max = nums[0];
  int ind = 0;
  for (size_t i = 1; i < size; i++) {
    if (nums[i] > max) {
      ind = i;
      max = nums[i];
    }
  }
  return ind;
}

bool change_lights(
    Road roads[4], bool *north_south, bool *left_turn, int wait_time
) {
  // cars wating on lane groups that can move simultaneously
  int_t ns_main = cars_amount(&roads[NORTH], false) +
                  cars_amount(&roads[SOUTH], false);
  int_t ew_main = cars_amount(&roads[EAST], false) +
                  cars_amount(&roads[WEST], false);
  int_t ns_left = cars_amount(&roads[NORTH], true) +
                  cars_amount(&roads[SOUTH], true);
  int_t ew_left = cars_amount(&roads[EAST], true) +
                  cars_amount(&roads[WEST], true);

  // if there aren't any cars waiting do nothing
  if (!(ns_main || ew_main || ns_left || ew_left)) {
    return false;
  }

  // set amount of cars on current lane and set
  // appropriate counter to zero to simplify calculations
  int_t cur_lane = 0;
  if (north_south) {
    if (left_turn) {
      cur_lane = ns_left;
      ns_left = 0;
    } else {
      cur_lane = ns_main;
      ns_main = 0;
    }
  } else {
    if (left_turn) {
      cur_lane = ew_left;
      ew_left = 0;
    } else {
      cur_lane = ew_main;
      ew_main = 0;
    }
  }

  switch (2 * (*north_south) + *left_turn) {
  case 0:
    *north_south = false;
    *left_turn = true;
    break;
  case 1:
    *north_south = true;
    *left_turn = false;
    break;
  case 2:
    *north_south = true;
    *left_turn = true;
    break;
  case 3:
    *north_south = false;
    *left_turn = false;
    break;
  }
  return true;
}

void move_cars(Road roads[4], bool north_south, bool left_turn) {
  bool moved = false;
  if (north_south) {
    if (cars_amount(&roads[NORTH], left_turn)) {
      Car car = del(&roads[NORTH], left_turn);
      printf("%i", car.id);
      moved = true;
    }
    if (cars_amount(&roads[SOUTH], left_turn)) {
      Car car = del(&roads[SOUTH], left_turn);
      if (moved) {
        printf(" ");
      }
      printf("%i", car.id);
    }

  } else {
    if (cars_amount(&roads[EAST], left_turn)) {
      Car car = del(&roads[EAST], left_turn);
      printf("%i", car.id);
      moved = true;
    }
    if (cars_amount(&roads[WEST], left_turn)) {
      Car car = del(&roads[WEST], left_turn);
      if (moved) {
        printf(" ");
      }
      printf("%i", car.id);
    }
  }
  printf("\n");
}

void simulate() {
  Road roads[4] = {0};
  bool north_south = true, left_turn = false;
  int wait_time = 0;

  while (!feof(stdin)) {
    int command = 0;
    scanf("%i", &command);

    if (command == ADD_COMMAND) {
      Car newCar = {0};
      int position = 0;
      scanf("%i %i %i", &newCar.id, &position, &newCar.destination);
      add(&roads[position],
          position - newCar.destination == LEFT_TURN,
          newCar);
      continue;
    }

    move_cars(roads, north_south, left_turn);
    if (!change_lights(
            roads, &north_south, &left_turn, wait_time
        )) {
      wait_time++;
    }
  }
}
