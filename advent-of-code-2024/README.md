# Advent of Code 2024

## Overview

This directory contains solutions for Advent of Code 2024, implemented in C.

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
  - [Requirements](#requirements)
  - [Setup](#setup)
  - [Operator Guide](#operator-guide)
  - [Testing](#testing)
- [Known Issues/Bugs](#known-issuesbugs)
- [Repository Structure](#repository-structure)

## Usage

### Requirements

- **Hardware**: Any machine capable of running C programs.
- **Operating System**: Recommended Ubuntu 22.04.
- **Software**: 
  - `git` for cloning the repository
  - Dependencies installed via `setup.sh` script

### Setup

1. Install `git` (if not already installed):
   ```sh
   sudo apt install git
   ```
1. Clone the repository:
    ```sh
    git clone <repository_url>
    cd advent-of-code-2024/
    ```
1. Install necessary dependencies:
   ```sh
   ./setup.sh
   ```

### Operator Guide

To compile the project, use:

```sh
make all
```

Run all challenges:

```sh
make run
```

Run a specific day (e.g. Day 1):

```sh
make run day_1
```

To remove compiled files and reset the build directory:

```sh
make clean
```

Note: `day_0` added into code. This is an example from a previous Advent of Code challenge to help format the repo.

### Testing

The project includes a basic testing suite to validate solutions against example inputs:

```sh
make test
```

Unit tests are automatically executed on each push to the main branch via GitHub Actions.  The unittests are setup to give a pipeline fail if any unittest does not pass.

## Known Issues/Bugs

No known issues or bugs at this time. Please submit any issues via GitHub.

## Repository Structure

```
data-structures/
│
├── include/
│   ├── day_1.h
│   ├── day_2.h
│   ├── day_X.
|
├── src/
│   ├── main.c
│   ├── day_1.c
│   ├── day_2.c
│   ├── day_X.c
|
├── data/
│   ├── example_1.txt
│   ├── actual_1.txt
│   ├── example_2.txt
│   ├── actual_2.txt
│   ├── example_X.txt
│   ├── actual_X.txt
│
├── tests/
│
└── README.md
```
