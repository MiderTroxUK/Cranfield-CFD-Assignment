/*  Computational Methods Assignment
    @author :       John Hoarau, Clémence-Philomène Hinot
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

class Laasonen_Scheme : public Scheme
{
    private:
        double r_; 
        int num_internal_nodes_;

        // Vectors for the tridiagonal system (Matrix A)
        std::vector<double> a_; // sub-diagonal
        std::vector<double> b_; // main diagonal
        std::vector<double> c_; // super-diagonal

        // Vector for the RHS
        std::vector<double> d_;

        // Solution vector
        std::vector<double> T_solution_;

        /**
         * @brief Sets up the constant coefficients of the tridiagonal matrix.
         * Laasonen: a = -r, b = 1+2r, c = -r
         */
        void setup_thomas_coefficients();

        /**
         * @brief Computes the RHS vector 'd'.
         * Laasonen RHS is simpler: d_i = T_current_i (plus boundary terms)
         */
        void setup_rhs_vector(const std::vector<double>& T_current, double T_sur);

        /**
         * @brief Solves the tridiagonal system using Thomas algorithm.
         */
        void solve_thomas_algorithm();   

    public:
        Laasonen_Scheme(const ProblemDefinition& problem);

        void solve_step(std::vector<double>& T_current, double T_sur);
};


/****** End of the prevention for mulitple definition ******/
#endif // LAASONEN_SCHEME_H