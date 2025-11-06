/*  Computational Methods Assignment
    @author :       John Hoarau, Clémence-Philomène Hinot
    @date :         16/10/2025
    @file :         CrankNicholson_Scheme.h
    @description:   Header for the Crank-Nicholson implicit scheme.
*/

#ifndef CRANKNICHOLSON_SCHEME_H
#define CRANKNICHOLSON_SCHEME_H


/****** Libraries and other inclusions ******/
#include "Scheme.h"
#include "ProblemDefinition.h" // Nécessaire pour le constructeur
#include <vector>


/****** Declaration of class CrankNicholson_Scheme ******/

class CrankNicholson_Scheme : public Scheme
{
    private:
        double r_; // stability (r = D*dt / dx^2)
        int num_internal_nodes_; // number of internal nodes (N-2)

        // Coefficients for the Tridiagonal Matrix System (A * T^n+1 = RHS)
        std::vector<double> a_; // sub-diagonal
        std::vector<double> b_; // main diagonal
        std::vector<double> c_; // super-diagonal

        std::vector<double> d_; // Vector 'd' (RHS)

        std::vector<double> T_solution_; // Temporary vector to store the solution from Thomas algorithm

        void setup_thomas_coefficients(); // Method to setup coefficients a_, b_, c_ for Thomas algorithm

        void setup_rhs_vector(const std::vector<double>& T_current, double T_sur); // Method to setup RHS vector 'd_'

        void solve_thomas_algorithm(); // Method to solve the tridiagonal system using Thomas algorithm

    public:
        CrankNicholson_Scheme(const ProblemDefinition& problem);  // class constructor with parameters


        void solve_step(std::vector<double>& T_current, double T_sur); // Method to perform one time step of the Crank-Nicholson scheme

};

#endif // CRANKNICHOLSON_SCHEME_H