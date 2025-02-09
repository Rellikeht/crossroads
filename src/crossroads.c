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

bool change() {
  // TODO
  return true;
}

#define TAKE_CAR(road, left_turn)                                  \
  if (cars_amount(road, left_turn)) {                              \
    Car car = del(road, left_turn);                                \
    printf("%i\n", car.id);                                        \
    fprintf(stderr, "%i\n", car.id);                               \
  }

void move_cars(Road roads[4], bool north_south, bool left_turn) {
  if (north_south) {
    TAKE_CAR(&roads[NORTH], left_turn);
    TAKE_CAR(&roads[SOUTH], left_turn);
  } else {
    TAKE_CAR(&roads[EAST], left_turn);
    TAKE_CAR(&roads[WEST], left_turn);
  }
}

void simulate() {
  Road roads[4] = {0};
  bool north_south = true, left_turn = false;
  int wait_time = 0;

  while (!feof(stdin)) {
    int command = 0;
    scanf("%i", &command);

    if (command != MOVE_COMMAND) {
      Car newCar = {0};
      int position = 0;
      scanf("%i %i %i", &newCar.id, &position, &newCar.destination);
      add(&roads[position],
          newCar.destination - position == LEFT_TURN,
          newCar);
      continue;
    }

    move_cars(roads, north_south, left_turn);
    // TODO change lights

    wait_time++;
  }
}
