#include <stdbool.h>

#ifndef ROAD_LENGTH
#define ROAD_LENGTH 4096
#endif

#define MOVE_COMMAND 1
#define LEFT_TURN    -1
#define NORTH        0
#define EAST         1
#define SOUTH        2
#define WEST         3

typedef struct {
  int id, destination;
} Car;

typedef struct {
  Car main_lane[ROAD_LENGTH], left_lane[ROAD_LENGTH];
  int main_first, left_first;
  int main_last, left_last;
} Road;

void add(Road *road, bool left, Car car);

Car del(Road *road, bool left);

int cars_amount(Road *road, bool left);

void simulate();
