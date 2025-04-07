# my_radar

A highly efficient radar simulation handling planes and control towers.

## Build

To compile the binary:

    make
    # or
    make re

The compiled binary will be called:

    my_radar

## Usage

To run the program:

    ./my_radar <input_file>

To show the help message:

    ./my_radar -h

## Description

- Planes travel from point A to point B with a defined speed.
- Some planes have a delay before they take off.
- If two planes collide, they are deleted.
- If a collision happens within a control tower's range, it's prevented.
- The program can efficiently handle up to **10,000 planes**.

## Disclaimer

You need to have the csfml library installed to run this.

There is a slight mem leak so be careful
