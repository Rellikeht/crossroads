#include "crossroads.h"
#include <stdio.h>

void add(Road *road, bool left, Car car) {
  Car *lane;
  int *last;
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

bool change() {
  // TODO
  return true;
}

void simulate() {
  Road roads[4] = {0};
  bool north_south = true, left_turn = false;
  int wait_time = 0;

  while (!feof(stdin)) {
    int command = 0;

    scanf("%i", &command);
    if (command != 0) {
      Car newCar = {0};
      int position = 0;
      scanf("%i %i %i", &newCar.id, &position, &newCar.destination);
      add(&roads[position],
          newCar.destination - position == LEFT_TURN,
          newCar);
      continue;
    }

    // TODO simulate !!
  }
}
