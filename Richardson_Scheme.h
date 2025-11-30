/*  Computational Methods Assignment
    @author :       John Hoarau, Clémence-Philomène Hinot
    @date :         16/10/2025
    @file :         Richardson_Scheme.h
    @description:   ...
*/

/****** Prevention for mulitple definition ******/
#ifndef RICHARDSON_SCHEME_H
#define RICHARDSON_SCHEME_H

/****** Libraries and other inclusions ******/
#include "Scheme.h"
#include "ProblemDefinition.h"
#include <iostream>
#include <vector>
using namespace std;

/****** Declaration of class Richardson_Scheme ******/

/**
 * @class Richardson_Scheme
 * @brief Implements the Richardson explicit numerical scheme.
 * 
 * The Richardson scheme is a second-order accurate explicit method in both time and space.
 * However, it is unconditionally unstable for the 1D diffusion equation.
 */
class Richardson_Scheme : public Scheme
{
    private:
        double r = 0.0;             ///< CFL number
        ProblemDefinition problem;  ///< Problem definition object
    public:
        /**
         * @brief Constructor.
         * @param problem The problem definition containing physical parameters.
         */
        Richardson_Scheme(const ProblemDefinition& problem);

        /**
         * @brief Solves the heat equation using the Richardson scheme.
         * @return A 2D vector containing the temperature distribution over time and space.
         */
        vector<vector<double>> richardsonSolution();
};

/****** End of the prevention for mulitple definition ******/
#endif