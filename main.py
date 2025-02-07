import subprocess as sp
from json import load, dump
from sys import argv, stdin, stdout


def parse_commands(commands: list[dict[str, str]]) -> list[str]:
    return []  # TODO


def parse_output(output: str) -> list[str]:
    return []  # TODO


def simulate(commands: list[dict[str, str]], out_file):
    output: list[dict[str, list[str]]] = []
    dump(output, out_file)


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
