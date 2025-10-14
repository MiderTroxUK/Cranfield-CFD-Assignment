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

### Branch Types

  * **`main`**: This is the production-ready branch. It must **always** contain a stable, working version of the code. No one should ever commit directly to `main`. Code is only merged from `develop` after a major milestone is completed and tested.
  * **`develop`**: This is the main integration branch. All completed features are merged into this branch. It represents the most up-to-date state of the project's development.
  * **`feature/*`**: All new work (e.g., implementing a class, fixing a bug) must be done on a dedicated feature branch. This isolates work-in-progress and keeps the `develop` branch stable.

### Step-by-Step Workflow

1.  **Start a New Task**: Assign a GitHub Issue to yourself.
2.  **Create a Feature Branch**: Always branch off from the latest version of `develop`.
    ```bash
    # Switch to develop and pull the latest changes
    git checkout develop
    git pull origin develop

    # Create your new feature branch
    git checkout -b feature/issue-2-problem-definitions
    ```
3.  **Implement and Commit**: Write your code on the feature branch. Make small, logical commits with clear messages.
    ```bash
    git add.
    git commit -m "Feat: Implement Problem definitions class"
    ```
4.  **Push and Create a Pull Request (PR)**: When your feature is complete and tested locally, push it to the remote repository.
    ```bash
    git push origin feature/issue-2-problem-definitions
    ```
    Then, go to GitHub and open a Pull Request to merge your feature branch into `develop`. In the PR description, link the issue it resolves (e.g., "Closes \#2").
5.  **Code Review and Merge**: At least one other team member must review and approve the Pull Request. After approval, the PR can be merged into `develop`. The feature branch should be deleted after the merge.

    

## Group Members

- Clémence-Philomène Hinot
- John Hoarau
