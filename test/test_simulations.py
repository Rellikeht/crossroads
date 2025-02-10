#!/usr/bin/env python
from simulation_test import simulation_test
from sys import argv

SIMULATIONS_AMOUNT = int(argv[1]) if len(argv) > 1 else 100
COMMANDS_AMOUNT = int(argv[2]) if len(argv) > 2 else 1000
successes = 0
last_car_step, steps_to_go = 0, 0

for i in range(SIMULATIONS_AMOUNT):
    print(f"Simulation {i}:")
    try:
        result = simulation_test(COMMANDS_AMOUNT)
        last_car_step += result[0]
        steps_to_go += result[1]
        print("Success")
        successes += 1
    except AssertionError:
        print("Failure")
    print()

avg_additional_steps = (steps_to_go - last_car_step) / SIMULATIONS_AMOUNT
print(f"Successful simulations: {successes}")
print(
    f"Average steps needed to fully finish simulation: {avg_additional_steps}"
)
