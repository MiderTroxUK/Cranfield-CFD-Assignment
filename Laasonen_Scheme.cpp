/*  Computational Methods Assignment
    @author :       John Hoarau, Clémence-Philomène Hinot
    @date :         27/11/2025
    @file :         Laasonen_Scheme.cpp
    @description:   Implementation of the Laasonen implicit scheme.
*/

/******* Inclusion of classes ******/
#include "Laasonen_Scheme.h"
#include "ProblemDefinition.h"
#include <iostream>
#include <vector>
#include <cmath>

/****** Libraries and other inclusions ******/
using namespace std;

/****** Methods for class Laasonen_Scheme ******/

// Constructor
Laasonen_Scheme::Laasonen_Scheme(const ProblemDefinition& problem)
    : Scheme(problem.Get_dx(), problem.Get_N(), problem.Get_dt(), problem.Get_D()) 
{
    // Calculate 'r'
    this->r_ = (Get_D() * Get_dt()) / (Get_dx() * Get_dx());
    
    this->num_internal_nodes_ = Get_N() - 2;

    if (num_internal_nodes_ > 0) {
        a_.resize(num_internal_nodes_);
        b_.resize(num_internal_nodes_);
        c_.resize(num_internal_nodes_);
        d_.resize(num_internal_nodes_);
        T_solution_.resize(num_internal_nodes_);
        
        setup_thomas_coefficients();
    } else {
        std::cerr << "ERROR: Number of nodes (N) must be > 2." << std::endl;
    }
}

// 1. Matrix Coefficients (Different from Crank-Nicholson)
void Laasonen_Scheme::setup_thomas_coefficients() {
    // Equation: -r*T(i-1) + (1 + 2r)*T(i) - r*T(i+1) = T_old(i)
    
    double val_a = -r_;
    double val_b = 1.0 + 2.0 * r_; // Note the 2.0 here
    double val_c = -r_;

    for (int i = 0; i < num_internal_nodes_; ++i) {
        a_[i] = val_a;
        b_[i] = val_b;
        c_[i] = val_c;
    }
}

// 2. RHS Vector (Different from Crank-Nicholson)
void Laasonen_Scheme::setup_rhs_vector(const std::vector<double>& T_current, double T_sur) {
    
    // General case for internal nodes: RHS is just the old temperature
    // d[i] = T_current[i_physical]
    for (int i_int = 0; i_int < num_internal_nodes_; ++i_int) {
        int j_phys = i_int + 1;
        d_[i_int] = T_current[j_phys];
    }

    // Boundary Conditions adjustment
    // The term -r*T(i-1) moves to RHS and becomes +r*T_sur for the first node
    if (num_internal_nodes_ > 0) {
        d_[0] += r_ * T_sur;
    }

    // The term -r*T(i+1) moves to RHS and becomes +r*T_sur for the last node
    if (num_internal_nodes_ > 1) {
        d_[num_internal_nodes_ - 1] += r_ * T_sur;
    }
}

// 3. Solver (Identical to Crank-Nicholson)
void Laasonen_Scheme::solve_thomas_algorithm() {
    if (num_internal_nodes_ <= 0) return;

    vector<double> c_prime = c_;
    vector<double> d_prime = d_; 

    // Forward Elimination
    c_prime[0] = c_prime[0] / b_[0];
    d_prime[0] = d_prime[0] / b_[0];

    for (int i = 1; i < num_internal_nodes_; ++i) {
        double m = b_[i] - a_[i] * c_prime[i - 1];
        if (std::abs(m) < 1e-10) return; // Stability check
        
        c_prime[i] = c_prime[i] / m;
        d_prime[i] = (d_prime[i] - a_[i] * d_prime[i - 1]) / m;
    }

    // Backward Substitution
    T_solution_[num_internal_nodes_ - 1] = d_prime[num_internal_nodes_ - 1];

    for (int i = num_internal_nodes_ - 2; i >= 0; --i) {
        T_solution_[i] = d_prime[i] - c_prime[i] * T_solution_[i + 1];
    }
}

// 4. Main Step function
void Laasonen_Scheme::solve_step(std::vector<double>& T_current, double T_sur) {
    if (num_internal_nodes_ <= 0) return;

    setup_rhs_vector(T_current, T_sur);
    solve_thomas_algorithm();

    for (int i = 0; i < num_internal_nodes_; ++i) {
        T_current[i + 1] = T_solution_[i];
    }
}