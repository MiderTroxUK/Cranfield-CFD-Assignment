/*  Computational Methods Assignment
    @author :       Clémence-Philomène Hinot
    @date :         25/11/2025
    @file :         DufortFrankel_Scheme.h
    @description:   Header for the Dufort-Frankel Scheme
*/

/****** Prevention for mulitple definition ******/
#ifndef DUFORTFRANKEL_SCHEME_H
#define DUFORTFRANKEL_SCHEME_H

/****** Libraries and other inclusions ******/
#include "Scheme.h"
#include "ProblemDefinition.h"
#include <iostream>
#include <vector>
using namespace std;

/****** Declaration of class DufortFrankel_Scheme ******/

/**
 * @class DufortFrankel_Scheme
 * @brief Implements the Dufort-Frankel explicit numerical scheme.
 * 
 * The Dufort-Frankel scheme is an unconditionally stable explicit method.
 * It is a modification of the Richardson scheme to improve stability.
 */
class DufortFrankel_Scheme : public Scheme
{
    private:
        double r = 0.0;             ///< CFL number
        ProblemDefinition problem;  ///< Problem definition object
    public:
        /**
         * @brief Constructor.
         * @param problem The problem definition containing physical parameters.
         */
        DufortFrankel_Scheme(const ProblemDefinition& problem);

        /**
         * @brief Solves the heat equation using the Dufort-Frankel scheme.
         * @return A 2D vector containing the temperature distribution over time and space.
         */
        vector<vector<double>> dfSolution(vector<vector<double>> laasonen);
};

/****** End of the prevention for mulitple definition ******/
#endif