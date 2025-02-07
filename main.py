import json
import subprocess as sp
from sys import argv, stdin, stdout


def simulate(commands: dict, output):
    pass


if len(argv) < 2:
    input_commands = json.load(stdin)
else:
    with open(argv[1], "r") as handle:
        input_commands = json.load(handle)
input_commands = input_commands["commands"]

if len(argv) < 3:
    simulate(input_commands, stdout)
else:
    with open(argv[2], "w") as handle:
        simulate(input_commands, handle)
