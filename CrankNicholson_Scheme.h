/*  Computational Methods Assignment
    @author :       John Hoarau
    @date :         16/10/2025
    @file :         CrankNicholson_Scheme.h
    @description:   Header for the Crank-Nicholson implicit scheme.
*/

/****** Prevention for mulitple definition ******/
#ifndef CRANKNICHOLSON_SCHEME_H
#define CRANKNICHOLSON_SCHEME_H

/****** Libraries and other inclusions ******/
#include "Scheme.h"
#include "ProblemDefinition.h" // Nécessaire pour le constructeur
#include <vector>
#include <iostream>

using namespace std;

/****** Declaration of class CrankNicholson_Scheme ******/

/**
 * @class CrankNicholson_Scheme
 * @brief Implements the Crank-Nicholson implicit numerical scheme.
 * 
 * The Crank-Nicholson scheme is a semi-implicit method (average of forward and backward time steps).
 * It is unconditionally stable and second-order accurate in both time and space.
 * It requires solving a tridiagonal system of linear equations at each time step.
 */
class CrankNicholson_Scheme : public Scheme
{
    private:
        double r_;                  ///< CFL number
        int num_internal_nodes_;    ///< Number of internal nodes (N-1)

        // Coefficients for the Tridiagonal Matrix System (A * T^n+1 = RHS)
        std::vector<double> a_; ///< Sub-diagonal elements
        std::vector<double> b_; ///< Main diagonal elements
        std::vector<double> c_; ///< Super-diagonal elements

        std::vector<double> d_; ///< Right-hand side vector

        std::vector<double> T_solution_; ///< Temporary vector to store the solution from Thomas algorithm

        /**
         * @brief Sets up the constant coefficients of the tridiagonal matrix.
         * Crank-Nicholson: a = -r/2, b = 1+r, c = -r/2
         */
        void setup_thomas_coefficients();

        /**
         * @brief Computes the RHS vector 'd'.
         * Crank-Nicholson RHS involves T^n terms: d_i = (r/2)T_{i-1}^n + (1-r)T_i^n + (r/2)T_{i+1}^n
         * @param T_current The temperature distribution at the current time step.
         * @param T_sur The surface temperature (boundary condition).
         */
        void setup_rhs_vector(const std::vector<double>& T_current, double T_sur);

        /**
         * @brief Solves the tridiagonal system using Thomas algorithm.
         * Updates T_solution_ with the new temperature values.
         */
        void solve_thomas_algorithm();

    public:
        /**
         * @brief Constructor.
         * @param problem The problem definition containing physical parameters.
         */
        CrankNicholson_Scheme(const ProblemDefinition& problem);

        /**
         * @brief Solves the heat equation using the Crank-Nicholson scheme.
         * @return A 2D vector containing the temperature distribution over time and space.
         */
        vector<vector<double>> Solve();
        
        /**
         * @brief Performs a single time step of the Crank-Nicholson scheme.
         * @param T_current The current temperature distribution (input/output).
         * @param T_sur The surface temperature (boundary condition).
         */
        void solve_step(std::vector<double>& T_current, double T_sur);

};

#endif // CRANKNICHOLSON_SCHEME_H