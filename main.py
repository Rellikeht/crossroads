#!/usr/bin/env python

from subprocess import run
from json import load, dumps
from sys import argv, stdin, stdout
from os import path

SCRIPT_PATH = path.dirname(path.realpath(__file__))
DIRECTIONS = {"north": 0, "east": 1, "south": 2, "west": 3}


def parse_commands(commands):
    """
    Change input commands to data readable by main program
    """
    output = []
    for command in commands:
        if command["type"] == "step":
            output.append("0")
            continue
        id = int(command["vehicleId"][7:])
        start = DIRECTIONS[command["startRoad"]]
        end = DIRECTIONS[command["endRoad"]]
        output.append(f"1 {id} {start} {end}")
    return output


def parse_output(output):
    """
    Change output of main program to json
    """
    parsed = []
    for line in output:
        parsed.append(
            {
                "leftVehicles": []
                if len(line) == 0
                else list(
                    map(lambda id: "vehicle" + str(id), line.split(" "))
                )
            }
        )
    return parsed


def simulate(commands, out_file):
    """
    Run simulation
    """
    process = run(
        f"make -C {SCRIPT_PATH}/src exe".split(" "),
        capture_output=True,
    )
    if len(process.stderr) > 0:
        print(process.stderr, end="")
    process.check_returncode()

    commands = "\n".join(parse_commands(commands))
    process = run(
        f"{SCRIPT_PATH}/src/build/main",
        input=commands,
        encoding="ascii",
        capture_output=True,
    )
    if len(process.stderr) > 0:
        print(process.stderr, end="")
    process.check_returncode()

    output = parse_output(process.stdout.splitlines())
    out_file.write(dumps({"stepStatuses": output}, indent=2))
    out_file.write("\n")


if len(argv) < 2:
    input_commands = load(stdin)
else:
    with open(argv[1], "r") as handle:
        input_commands = load(handle)
input_commands = input_commands["commands"]

if len(argv) < 3:
    simulate(input_commands, stdout)
else:
    with open(argv[2], "w") as handle:
        simulate(input_commands, handle)
