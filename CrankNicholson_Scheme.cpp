/*  Computational Methods Assignment
    @author :       John Hoarau, Clémence-Philomène Hinot
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
    
    // The tridiagonal system only applies to INTERNAL nodes
    this->num_internal_nodes_ = Get_N() - 2;

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
        std::cerr << "ERROR: Number of nodes (N) must be > 2." << std::endl;
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
    // The equation is: (1+r)T(1,n+1) - (r/2)T(2,n+1) = (r/2)T(0,n) + (1-r)T(1,n) + (r/2)T(2,n) + (r/2)T(0,n+1)
    // Since T(0,n) = T(0,n+1) = T_sur, the RHS becomes:
    // d[0] = r*T_sur + (1-r)*T(1,n) + (r/2)*T(2,n)
    if (num_internal_nodes_ > 0) {
        d_[0] = r_ * T_sur + 
                (1.0 - r_) * T_current[1] + 
                (r_ / 2.0) * T_current[2];
    }

    // 3. Handle the last internal node (i_int = N-3, j_phys = N-2)
    // The equation is: -(r/2)T(N-3,n+1) + (1+r)T(N-2,n+1) = (r/2)T(N-3,n) + (1-r)T(N-2,n) + (r/2)T(N-1,n) + (r/2)T(N-1,n+1)
    // Since T(N-1,n) = T(N-1,n+1) = T_sur, the RHS becomes:
    // d[N-3] = (r/2)*T(N-3,n) + (1-r)*T(N-2,n) + r*T_sur
    if (num_internal_nodes_ > 1) { // Ensure at least 2 internal nodes
        int i_last = num_internal_nodes_ - 1; // index of last internal node
        int j_last = i_last + 1;              // physical index (N-2)
        
        d_[i_last] = (r_ / 2.0) * T_current[j_last - 1] + 
                     (1.0 - r_) * T_current[j_last] + 
                     r_ * T_sur;
    }
}


// Solves the tridiagonal system using the Thomas algorithm
void CrankNicholson_Scheme::solve_thomas_algorithm() {
    if (num_internal_nodes_ <= 0) return;

    // Create temporary copies for the elimination pass
    // (We don't want to modify c_ which is constant, but d_ is our RHS)
    vector<double> c_prime = c_;
    vector<double> d_prime = d_; // d_ is already our RHS, we use it for d_prime

    // 1. Forward Elimination pass
    // Normalize first row
    c_prime[0] = c_prime[0] / b_[0];
    d_prime[0] = d_prime[0] / b_[0];

    // Update subsequent rows
    for (int i = 1; i < num_internal_nodes_; ++i) {
        double m = b_[i] - a_[i] * c_prime[i - 1];
        if (std::abs(m) < 1e-10) { // Avoid division by zero
             cerr << "ERROR: Thomas algorithm unstable (division by zero)." << endl;
             return;
        }
        c_prime[i] = c_prime[i] / m;
        d_prime[i] = (d_prime[i] - a_[i] * d_prime[i - 1]) / m;
    }

    // 2. Backward Substitution pass
    // Last element is the solution
    T_solution_[num_internal_nodes_ - 1] = d_prime[num_internal_nodes_ - 1];

    // Back-substitute to find the others
    for (int i = num_internal_nodes_ - 2; i >= 0; --i) {
        T_solution_[i] = d_prime[i] - c_prime[i] * T_solution_[i + 1];
    }
}

// Performs one time step of the Crank-Nicholson scheme
void CrankNicholson_Scheme::solve_step(std::vector<double>& T_current, double T_sur) {
    if (num_internal_nodes_ <= 0) return; // Do nothing if grid is too small

    // 1. Set up the RHS vector (d_) using T_current values (time 'n')
    setup_rhs_vector(T_current, T_sur);

    // 2. Solve the tridiagonal system for T_solution_ (time 'n+1')
    solve_thomas_algorithm();

    // 3. Update the T_current vector with the new solution
    // (Only internal nodes are updated; boundaries remain T_sur)
    for (int i = 0; i < num_internal_nodes_; ++i) {
        T_current[i + 1] = T_solution_[i]; // i+1 because T_current has N elements
    }
}