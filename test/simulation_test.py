#!/usr/bin/env python

from subprocess import run
from os import path
from random import randint
from sys import argv
from functools import reduce

SCRIPT_PATH = path.dirname(path.realpath(__file__))


def simulation_test(amount=1000):
    commands = []
    id = 0
    last_car_step = 0
    step = 0

    # just random commands
    for _ in range(amount):
        if randint(0, 1) == 0:
            commands.append("0")
            step += 1
            continue
        commands.append(f"1 {id} {randint(0, 3)} {randint(0, 3)}")
        id += 1
        last_car_step = step

    # simple heuristic to make sure all cars have enouth time to drive through
    ADDITIONAL = 2 * id + 1
    for _ in range(ADDITIONAL):
        commands.append("0")

    process = run(
        f"{SCRIPT_PATH}/build/simulation",
        input="\n".join(commands),
        encoding="ascii",
        capture_output=True,
    )
    if len(process.stderr) > 0:
        print(process.stderr, end="")
    process.check_returncode()

    # number of steps made has to be number of steps commanded
    output = process.stdout.splitlines()
    assert len(output) == ADDITIONAL + amount - id

    steps_to_go = 0
    for i in range(len(output)):
        if len(output[i]) > 0:
            steps_to_go = i
    print(
        f"Last car drove in at {last_car_step} step, "
        + f"last car left at {steps_to_go} step"
    )
    assert last_car_step <= steps_to_go

    # all cars must drive through
    car_output = list(
        map(
            lambda s: list(map(int, s.split(" "))),
            filter(lambda s: len(s) > 0, output),
        )
    )
    cars_left = sorted(reduce(list.__add__, car_output))
    print(f"Cars left: {len(cars_left)} of total {id}")
    assert cars_left == list(range(id))
    return (last_car_step, steps_to_go)


if __name__ == "__main__":
    COMMANDS_AMOUNT = int(argv[1]) if len(argv) > 1 else 1000
    simulation_test(COMMANDS_AMOUNT)
