#!/usr/bin/env python

from subprocess import run
from os import path
from random import randint

SCRIPT_PATH = path.dirname(path.realpath(__file__))


commands = ""
# TODO generate commands
commands = "\n".join(commands)
process = run(
    f"{SCRIPT_PATH}/build/simulation",
    input=commands,
    encoding="ascii",
    capture_output=True,
)
if len(process.stderr) > 0:
    print(process.stderr, end="")
process.check_returncode()

output = process.stdout.splitlines()
# TODO check output
