#!/usr/bin/env python
from simulation_test import simulation_test
from sys import argv

SIMULATIONS_AMOUNT = int(argv[1]) if len(argv) > 1 else 100
COMMANDS_AMOUNT = int(argv[2]) if len(argv) > 2 else 1000
successes = 0

for i in range(SIMULATIONS_AMOUNT):
    print(f"Simulation {i}:")
    try:
        simulation_test(COMMANDS_AMOUNT)
        print("Success")
        successes += 1
    except AssertionError:
        print("Failure")
    print()

print(f"Successful simulations: {successes}")
