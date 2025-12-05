/*  Computational Methods Assignment
    @author :       John Hoarau
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
         * @brief Verifies the stability of a numerical scheme.
         * 
         * Checks if the given scheme is stable under the current conditions (CFL number).
         * Prints a message indicating the stability status.
         * 
         * @param CFL The CFL number.
         * @param schemeName The name of the scheme (e.g., "Richardson", "Laasonen").
         * @return true if stable, false otherwise.
         */
        bool Verify_Stability(double CFL, string schemeName);

        /**
         * @brief Calculates the L2 Norm (Root Mean Square Error) between numerical and analytical solutions.
         * 
         * @param numerical Vector containing the numerical solution.
         * @param analytical Vector containing the analytical solution.
         * @return The calculated L2 Norm. Returns -1.0 if vector sizes do not match.
         */
        double Calculation_Norm(const vector<double>& numerical, const vector<double>& analytical);
};

/****** End of the prevention for mulitple definition ******/
#endif