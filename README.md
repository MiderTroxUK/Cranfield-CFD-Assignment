# 1D Heat Equation Solver - Cranfield Assignment

This project is an object-oriented C++ implementation for solving the one-dimensional heat equation using various finite difference methods, as part of the Cranfield University "Computational Methods & C++" assignment.

## Problem Description

The project aims to compute the temperature distribution over time within a 31cm thick wall.

- **Governing Equation:** $\frac{\partial T}{\partial t}=D\frac{\partial^{2}T}{\partial x^{2}}$
- **Physical Properties:**
    - Wall Thickness ($L$): 31 cm
    - Thermal Diffusivity ($D$): 93 cm²/hr
    - Uniform Initial Temperature ($T_{in}$): 38°C
    - Maintained Surface Temperature ($T_{sur}$): 149°C
- **Numerical Methods to Implement:**
  1.  DuFort-Frankel (Explicit)
  2.  Richardson (Explicit)
  3.  Laasonen (Implicit)
  4.  Crank-Nicholson (Implicit)

## Software Architecture (UML)

The software design is based on the following UML class diagram, which separates responsibilities into distinct modules:

*UML*


- **Problem definitions:** Encapsulates all physical and numerical parameters of the problem.
- **Scheme (Mother Class):** An abstract base class defining the common interface for all numerical methods.
- **DuFortFrankel, Richardson, Laasonen, CrankNicholson:** Concrete implementations of each numerical scheme, inheriting from `Scheme`.
- **Output:** Manages writing results to output files for analysis and visualization.
- **Verif:** A class dedicated to verifying stability (e.g., CFL criterion) and calculating the analytical solution for validation.

## Build and Run Instructions

1.  **Prerequisites:** A C++ compiler (supporting C++17 or higher), such as g++.
2.  **Clone the repository:**
    ```bash
    git clone <your-repo-url>
    cd <your-repo-name>
    ```
3.  **Compile the project:**
    ```bash
    g++ -std=c++17 -o solver main.cpp problem_definitions.cpp scheme.cpp output.cpp verif.cpp #... and other.cpp files
    ```
4.  **Run the program:**
    ```bash
   ./solver
    ```

## Group Members

- Clémence-Philomène Hinot
- John Hoarau
