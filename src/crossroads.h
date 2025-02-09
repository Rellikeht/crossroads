#include <stdbool.h>

#ifndef ROAD_LENGTH
#define ROAD_LENGTH 4096
#endif
#ifndef int_t
#define int_t int
#endif

#define MOVE_COMMAND 1
#define LEFT_TURN    -1
#define NORTH        0
#define EAST         1
#define SOUTH        2
#define WEST         3

typedef struct {
  int_t id;
  int destination;
} Car;

typedef struct {
  Car main_lane[ROAD_LENGTH], left_lane[ROAD_LENGTH];
  int_t main_first, left_first;
  int_t main_last, left_last;
} Road;

void add(Road *road, bool left, Car car);

Car del(Road *road, bool left);

int_t cars_amount(Road *road, bool left);

void simulate();
