#include <stdbool.h>
#define ROAD_LENGTH 1024
#define LEFT_TURN   -1

typedef struct {
  int id, destination;
} Car;

typedef struct {
  Car main_lane[ROAD_LENGTH], left_lane[ROAD_LENGTH];
  int main_first, left_first;
  int main_last, left_last;
} Road;

void add(Road *road, bool left, Car car);

void simulate();
