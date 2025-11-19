# SecretNumberDilemma

A C++ implementation of a Constraint Satisfaction Problem (CSP) solver for the Secret Number Dilemma puzzle.

## Overview

This project implements a CSP solver with the following components:
- **Variable**: Represents a CSP variable with a domain of values (1-100)
- **Constraints**: Various constraint types to restrict variable domains
  - `AllDifferenceConstraint`: Ensures all variables have different values
  - `BinaryConstraint`: Defines constraints between two variables

## Building the Project

### Prerequisites
- CMake 3.20 or higher
- C++23 compatible compiler (GCC 13.3.0+ or equivalent)

### Build Instructions

```bash
mkdir build
cd build
cmake ..
make
```

This will create two executables:
- `bin/SecretNumberDilemma` - Main application
- `bin/SecretNumberDilemma_tests` - Test suite

## Running

### Main Application
```bash
./bin/SecretNumberDilemma
```

### Tests
```bash
./bin/SecretNumberDilemma_tests
```

## Project Structure

```
.
├── include/secretNumberDilemma/  # Header files
│   ├── csp/                      # CSP solver components
│   └── tests/                    # Test headers
├── src/                          # Source files
│   ├── csp/                      # CSP implementation
│   └── main.cpp                  # Main application
└── tests/                        # Test implementations
```