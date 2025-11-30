/* Computational Methods Assignment
    @author :       John Hoarau
    @date :         06/11/2025
    @file :         CrankNicholson_Scheme.cpp
    @description:   Implementation of the CrankNicholson_Scheme class.
*/

/******* Inclusion of classes ******/
#include "CrankNicholson_Scheme.h"
#include "ProblemDefinition.h"

/****** Libraries and other inclusions ******/
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

/****** Methods for class CrankNicholson_Scheme ******/

CrankNicholson_Scheme::CrankNicholson_Scheme(const ProblemDefinition& problem)
    // Call the base class 'Scheme' constructor
    : Scheme(problem.Get_dx(), problem.Get_N(), problem.Get_dt(), problem.Get_D()) 
{
    // Calculate the 'r' parameter
    this->r_ = (Get_D() * Get_dt()) / (Get_dx() * Get_dx());
    
    // FIX: Calculate spatial nodes based on geometry, NOT time steps (N)
    int num_space_points = static_cast<int>(problem.Get_thickness() / problem.Get_dx()) + 1;

    // The tridiagonal system only applies to INTERNAL nodes
    this->num_internal_nodes_ = num_space_points - 2;

    // Resize vectors to fit the internal nodes
    if (num_internal_nodes_ > 0) {
        a_.resize(num_internal_nodes_);
        b_.resize(num_internal_nodes_);
        c_.resize(num_internal_nodes_);
        d_.resize(num_internal_nodes_);
        T_solution_.resize(num_internal_nodes_);
        
        // Set up the (constant) matrix A coefficients
        setup_thomas_coefficients();
    } else {
        // Handle the case where there are no internal nodes (e.g., N=2)
        std::cerr << "ERROR: Number of spatial nodes must be > 2." << std::endl;
    }
}

void CrankNicholson_Scheme::setup_thomas_coefficients() {
    double val_a = -r_ / 2.0;
    double val_b = 1.0 + r_;
    double val_c = -r_ / 2.0;

    for (int i = 0; i < num_internal_nodes_; ++i) {
        a_[i] = val_a;
        b_[i] = val_b;
        c_[i] = val_c;
    }
}

// Sets up the RHS vector 'd_' based on the current temperature distribution and boundary conditions 
void CrankNicholson_Scheme::setup_rhs_vector(const std::vector<double>& T_current, double T_sur) { 
    
    // 1. Middle internal nodes (from i_int = 1 to N-4)
    // (corresponding to physical nodes j=2 to N-3)
    for (int i_int = 1; i_int < num_internal_nodes_ - 1; ++i_int) {
        int j_phys = i_int + 1; // Corresponding physical node
        d_[i_int] = (r_ / 2.0) * T_current[j_phys - 1] + 
                    (1.0 - r_) * T_current[j_phys] + 
                    (r_ / 2.0) * T_current[j_phys + 1];
    }

    // 2. Handle the first internal node (i_int = 0, j_phys = 1)
    if (num_internal_nodes_ > 0) {
        d_[0] = r_ * T_sur + 
                (1.0 - r_) * T_current[1] + 
                (r_ / 2.0) * T_current[2];
    }

    // 3. Handle the last internal node (i_int = N-3, j_phys = N-2)
    if (num_internal_nodes_ > 1) { 
        int i_last = num_internal_nodes_ - 1; 
        int j_last = i_last + 1;              
        
        d_[i_last] = (r_ / 2.0) * T_current[j_last - 1] + 
                     (1.0 - r_) * T_current[j_last] + 
                     r_ * T_sur;
    }
}


// Solves the tridiagonal system using the Thomas algorithm
void CrankNicholson_Scheme::solve_thomas_algorithm() {
    if (num_internal_nodes_ <= 0) return;

    // Create temporary copies for the elimination pass
    vector<double> c_prime = c_;
    vector<double> d_prime = d_; 

    // 1. Forward Elimination pass
    c_prime[0] = c_prime[0] / b_[0];
    d_prime[0] = d_prime[0] / b_[0];

    for (int i = 1; i < num_internal_nodes_; ++i) {
        double m = b_[i] - a_[i] * c_prime[i - 1];
        if (std::abs(m) < 1e-10) { 
             cerr << "ERROR: Thomas algorithm unstable (division by zero)." << endl;
             return;
        }
        c_prime[i] = c_prime[i] / m;
        d_prime[i] = (d_prime[i] - a_[i] * d_prime[i - 1]) / m;
    }

    // 2. Backward Substitution pass
    T_solution_[num_internal_nodes_ - 1] = d_prime[num_internal_nodes_ - 1];

    for (int i = num_internal_nodes_ - 2; i >= 0; --i) {
        T_solution_[i] = d_prime[i] - c_prime[i] * T_solution_[i + 1];
    }
}

// Performs one time step of the Crank-Nicholson scheme
void CrankNicholson_Scheme::solve_step(std::vector<double>& T_current, double T_sur) {
    if (num_internal_nodes_ <= 0) return; 

    setup_rhs_vector(T_current, T_sur);
    solve_thomas_algorithm();

    for (int i = 0; i < num_internal_nodes_; ++i) {
        T_current[i + 1] = T_solution_[i]; 
    }
}

vector<vector<double>> CrankNicholson_Scheme::Solve() {
    int num_time_steps = static_cast<int>(Get_N()) + 1; 
    // Calculate spatial points based on thickness and dx
    int num_space_points = static_cast<int>(31.0 / Get_dx()) + 1; 

    // Initialize solution matrix [space x time]
    vector<vector<double>> solution(num_space_points, vector<double>(num_time_steps, 0.0));

    // Current temperature profile
    vector<double> T_curr(num_space_points);

    // 1. Set Initial Conditions (t=0)
    for (int i = 0; i < num_space_points; ++i) {
        T_curr[i] = 38.0; // Tin
    }

    // Boundary Conditions
    T_curr[0] = 149.0; // Tsur
    T_curr[num_space_points - 1] = 149.0;

    // Store IC into solution column 0
    for (int i = 0; i < num_space_points; ++i) {
        solution[i][0] = T_curr[i];
    }

    // 2. Time Loop
    for (int t = 1; t < num_time_steps; ++t) {
        solve_step(T_curr, 149.0);

        for (int i = 0; i < num_space_points; ++i) {
            solution[i][t] = T_curr[i];
        }
    }

    return solution;
}