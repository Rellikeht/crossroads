#include <stdbool.h>
#include <stddef.h>

#ifndef ROAD_LENGTH
#define ROAD_LENGTH 4096
#endif
#ifndef int_t
#define int_t int
#endif

#define STEP_COMMAND 0
#define ADD_COMMAND  1
#define LEFT_TURN    -1
#define NORTH        0
#define EAST         1
#define SOUTH        2
#define WEST         3

#define MIN_PASS_TIME 1

/*
 * Just a car with given destination
 */
typedef struct {
  int_t id;
  int destination;
} Car;

/*
 * Structure for representing road, each lane is separate queue
 * implemented as cyclic buffer
 */
typedef struct {
  Car main_lane[ROAD_LENGTH], left_lane[ROAD_LENGTH];
  int_t main_first, left_first; // first car on each lane
  int_t main_last, left_last;   // last car on each lane
} Road;

/*
 * Add car to main or left lane
 */
void add(Road *road, bool left, Car car);

/*
 * Remove car from main or left lane
 */
Car del(Road *road, bool left);

/*
 * Return amount of cars wating on main or left lane of given road
 */
int_t cars_amount(Road *road, bool left);

/*
 * Move cars on appropriate lanes
 */
void move_cars(Road roads[4], bool north_south, bool left_turn);

/*
 * Index of maximum value in array
 */
int max_val_ind(int_t *nums, size_t size);

/* Run simulation */
void simulate();
