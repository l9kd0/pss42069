# About this
This repository holds all source files used in the first project for course LINFO1252.

# How to run
Some of the following commands also work in sub directories. (e.g. `make`)


## Compile
- `make` : creates executables in all subdirectories.

- `make clean` : deletes all executables, images and csv files in sub directories.

- `make remake` : runs a make clean then a make in the philosophy, proco and reawri directories.

## Analysis
 - `make test` : runs all tests and generates data in the /data/ folder.

  **It may take a while.**.

 - `./analysis.sh [proco/philosophy/tatas/btatas/reawri/tas]` : runs specifics tests for the provided target, generates related csv files.

 **WARN: run make before running the command above.**

 - `python3 graphs.py` : plots graphs only if the data/ folder is filled with full testing data. The .png format is used.
