/*  Computational Methods Assignment
    @author :       John Hoarau
    @date :         27/11/2025
    @file :         Laasonen_Scheme.h
    @description:   Header for the Laasonen implicit scheme.
*/

/****** Prevention for mulitple definition ******/
#ifndef LAASONEN_SCHEME_H
#define LAASONEN_SCHEME_H

/****** Libraries and other inclusions ******/
#include "Scheme.h"
#include "ProblemDefinition.h"
#include <iostream>
using namespace std;

/****** Declaration of class Laasonen_Scheme ******/

/**
 * @class Laasonen_Scheme
 * @brief Implements the Laasonen implicit numerical scheme.
 * 
 * The Laasonen scheme is a fully implicit method (backward in time, central in space).
 * It is unconditionally stable and first-order accurate in time, second-order in space.
 * It requires solving a tridiagonal system of linear equations at each time step.
 */
class Laasonen_Scheme : public Scheme
{
    private:
        double r_;                  ///< CFL number
        int num_internal_nodes_;    ///< Number of internal nodes (N-1)

        // Vectors for the tridiagonal system (Matrix A)
        std::vector<double> a_; ///< Sub-diagonal elements
        std::vector<double> b_; ///< Main diagonal elements
        std::vector<double> c_; ///< Super-diagonal elements

        // Vector for the RHS
        std::vector<double> d_; ///< Right-hand side vector

        // Solution vector
        std::vector<double> T_solution_; ///< Temporary storage for solution

        /**
         * @brief Sets up the constant coefficients of the tridiagonal matrix.
         * Laasonen: a = -r, b = 1+2r, c = -r
         */
        void setup_thomas_coefficients();

        /**
         * @brief Computes the RHS vector 'd'.
         * Laasonen RHS is simpler: d_i = T_current_i (plus boundary terms)
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
        Laasonen_Scheme(const ProblemDefinition& problem);
        
        /**
         * @brief Solves the heat equation using the Laasonen scheme.
         * @return A 2D vector containing the temperature distribution over time and space.
         */
        vector<vector<double>> Solve();

        /**
         * @brief Performs a single time step of the Laasonen scheme.
         * @param T_current The current temperature distribution (input/output).
         * @param T_sur The surface temperature (boundary condition).
         */
        void solve_step(std::vector<double>& T_current, double T_sur);
};


/****** End of the prevention for mulitple definition ******/
#endif // LAASONEN_SCHEME_H