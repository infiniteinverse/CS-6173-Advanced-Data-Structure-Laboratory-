# Advanced Data Structures Laboratory (CS6173)

This repository contains coursework, assignments, and reusable data structure implementations for CS6173. The project supports both C++ and Java codebases.

## Repository Structure

```text
.
├── Assignments/          # Lab assignments and drivers
│   ├── Assignment_1/     # Strassen's Algorithm (Multi-core CPU)
│   ├── Assignment_2/     # Monte Carlo Pi, Primality, Randomized QuickSort
|   ├──
│   └── Assignment_3/
├── include/              # C++ headers (generation, numerical, sorting)
├── java/                 # Java implementations (Simplified flat structure)
│   ├── generation/       # Data generation utilities
│   ├── numerical/        # Numerical algorithms
│   ├── sorting/          # Sorting algorithms
│   └── tests/            # Java test runners
└── DEVLOG.md             # Running development log
```

## Build & Run Instructions

### Java Environment
Java implementations use a flat package structure and compile without external build tools.
```bash
cd java
mkdir -p build
javac -d build generation/*.java sorting/*.java tests/*.java
java -cp build tests.MainTest
```

### C++ Environment
C++ assignments (like the Assignment 1 multi-core execution) are configured using CMake. Ensure your Intel Compilers are correctly integrated with the Visual Studio IDE (VS Code is not sufficient for the Intel toolchain installation).
```bash
mkdir build
cd build
cmake ..
cmake --build .
```
