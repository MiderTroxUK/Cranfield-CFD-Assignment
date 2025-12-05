/*  Computational Methods Assignment
    @author :       John Hoarau, Github copilot
    @date :         16/10/2025
    @file :         Verification.h
    @description:   Header for verification functions and utilities.
*/

/****** Prevention for mulitple definition ******/
#ifndef VERIFICATION_H
#define VERIFICATION_H

/****** Libraries and other inclusions ******/
#include <iostream>
#include <vector>
#include <string> // Added for string type
using namespace std;

/****** Declaration of class Verification ******/
/**
 * @class Verification
 * @brief Provides methods for verifying numerical results and conditions.
 * 
 * This class includes utilities to check the stability of numerical schemes and calculate error norms
 * (e.g., L2 norm) by comparing numerical results with analytical solutions.
 */
class Verification
{
    private:
        double CFL; ///< Courant-Friedrichs-Lewy number
    public:
        /**
         * @brief Default constructor.
         */
        Verification();

        /**
         * @brief Parameterized constructor.
         * @param CFL The CFL number to check.
         */
        Verification(double CFL);

        // Getters
        double Get_CFL() const;     ///< Get CFL number

        // Setters
        void Set_CFL(double value); ///< Set CFL number

        /**
         * @brief Verifies the stability of a numerical scheme based on error and tolerance.
         * 
         * @param error The calculated error (e.g., L2 Norm).
         * @param tolerance The acceptable error threshold.
         * @return true if stable (error <= tolerance and not NaN/Inf), false otherwise.
         */
        bool Verify_Stability(double error, double tolerance);

        /**
         * @brief Calculates the L2 Norm (Discrete Integral) between numerical and analytical solutions.
         * 
         * Formula: sqrt( sum( (num[i] - ana[i])^2 ) * dx )
         * 
         * @param numerical Vector containing the numerical solution.
         * @param analytical Vector containing the analytical solution.
         * @param dx The spatial grid spacing.
         * @return The calculated L2 Norm. Returns -1.0 if vector sizes do not match.
         */
        double Calculation_L2_Norm(const vector<double>& numerical, const vector<double>& analytical, double dx);

        /**
         * @brief Calculates the Relative L2 Error.
         * 
         * Formula: L2_Norm(num - ana) / L2_Norm(ana)
         * 
         * @param numerical Vector containing the numerical solution.
         * @param analytical Vector containing the analytical solution.
         * @param dx The spatial grid spacing.
         * @return The calculated Relative Error. Returns -1.0 if vector sizes do not match or analytical norm is 0.
         */
        double Calculation_Relative_Error(const vector<double>& numerical, const vector<double>& analytical, double dx);
};

/****** End of the prevention for mulitple definition ******/
#endif