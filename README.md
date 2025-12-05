# 1D Heat Equation Solver - Cranfield Assignment

This project is an object-oriented C++ implementation for solving the one-dimensional heat equation using various finite difference methods, as part of the Cranfield University "Computational Methods & C++" assignment.

## Problem Description

The project aims to compute the temperature distribution over time within a 31cm thick wall.

- **Governing Equation:** \f$\frac{\partial T}{\partial t}=D\frac{\partial^{2}T}{\partial x^{2}}\f$
- **Physical Properties:**
    - Wall Thickness (\f$L\f$): 31 cm
    - Thermal Diffusivity (\f$D\f$): 93 cm²/hr
    - Uniform Initial Temperature (\f$T_{in}\f$): 38°C
    - Maintained Surface Temperature (\f$T_{sur}\f$): 149°C
- **Numerical Methods to Implement:**
  1.  DuFort-Frankel (Explicit)
  2.  Richardson (Explicit)
  3.  Laasonen (Implicit)
  4.  Crank-Nicholson (Implicit)

## Software Architecture (UML)

The software design allows for modularity and extensibility. Below is the UML class diagram representing the project structure.

![UML Class Diagram](https://kroki.io/mermaid/svg/eNrtV19v0zAQf9-n8MumlrV74BEhJFgYPIyC1onXyHXc1ZoTV7ZTdRrbZ-ecOIkT29kKDPFAH9r0_v3ufHe-C-FYqYThG4nzIwSf42N0RTnWTBRqw7aqIi7JhuYUvf0xn6NziYvbBSMbwZUo0prlSSXlWkh9YWQpjwldYgwmaNTIFaBgmQ1gqq-gF-js7B36JsWK0zyha1YwEwZ6g0pF60BCbqFXABXSIiLfClX9q5QH7j6N5vn_bKgmFR-woujc5KiiEPPUHNF9RTKfeSZKMImyfUdihUYLX0J7pMSjyJZyWkNNph6lRZyhCmmGWoT2MXHUPlGdZvvJ1PL6jAXQwcpAWkekkwB9WZu3wDvMSzrtcxcT42eIA0AjekmMaVw5v7jsO_Nw1GQuoZLtaFYnj7rpC5eun02Z9rNZlHkKv1QWmKeFyKhyBHaUaCEfa9VHhOOsVZxF4qwszrpOleClKV1HRlFdblO9ETlWKRF0vWaE0UIrp5askNyotDY5IXDpQJJ69k8AgJRSgnJbWQBZSteQ4DvaoGF-IyTTm9wt2-ChWzyvIU_Qtia5tWAgINnWub6Pj51c7YrSdDs5KA5bOXWJBK-p-5FGnfuXig2h8yxk9JATyNZLm-dJ-BAQtxfk6Cn1Ah1eqf-74EW7YHDc_2z9-4Pzd4vfs3hI7LJV_pMdAEPiM-VbKgMzwo9ofNpbkv6C96MzP7wVXLPCp0FmfPsbRm4LareR8BZx6vnuVqDPHJruNol9-2ji6m0Y_Z0D_O-ewe_DNxADEGFF95Dg1gKuRMSNYzH0JvY_uvFUMY3wx_ee-L5kQhxRrOIcc6sN9le2rvdw7d9pRtK2E58_bL6Weltqt5OUlqy4QWvGaYFz53RrUbdwLWWgMaivhgxO1YL9qFq2tVIFlwZtFVRiTdML4PXnwSDKE9SMnZmFRDmFEZAtwGKolZz9vO6qqpVC2Pat8O_B95L1HfZnmJY4cvnB5t257Mq6OevRO8Wnlvg2X4YTqcPK9F261HjFONN3jRyVUnT3jxYczrIgdIpWQnBnHcWclPVbdnr5Ol0ImUfGPuw7AEUwn6GwALYdYSTa8_bjcRHrF3wY0x-Nty8H_PAT2EEWoA==)

Detailed caller and collaboration graphs are available in the generated Doxygen documentation (see `docs/html/index.html`).

**Key Classes:**

- **`ProblemDefinition`**: Encapsulates all physical and numerical parameters of the problem (diffusivity, dimensions, grid spacing, etc.).
- **`Scheme` (Base Class)**: An abstract base class defining the common interface (`Solve()`) for all numerical methods.
- **`DufortFrankel_Scheme`, `Richardson_Scheme`, `Laasonen_Scheme`, `CrankNicholson_Scheme`**: Concrete implementations of each numerical scheme, inheriting from `Scheme`.
- **`Output`**: Handles data export to CSV files for analysis.
- **`Verification`**: Provides utilities for verifying stability (L2 Norm, Relative Error calculation) and comparing numerical results against the analytical solution.

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
