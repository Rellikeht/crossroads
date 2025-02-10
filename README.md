# crossroads

## AVSystem recruitment assignment

Simulation of an intelligent traffic light system, which adjusts
its operation according to traffic intensity.

## description

Project consists of:

- randomized tests (unit and integration)
- simulation code
- driver Python script

Main code was written in C, is fully interacitve and easily transferable
to embedded platforms.
Tests are written in both in Python and C.
Algorithm for choosing lanes is a simple heuristic that prioritizes
lanes with the most intense traffic (long waiting + most cars).

## running

Just run `python main.py [input file name] [output file name]` file,
it runs `make` automatically.
