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

class Richardson_Scheme : public Scheme
{
    private:
        double r = 0.0; // CFL number
    public:
        // class constructor with parameter
        Richardson_Scheme(const ProblemDefinition& problem);

        // methods
        vector<vector<double>> richardsonSolution(double dx, double L, double dt, double t_max, int N, double D, double T_in, double T_sur);
};

/****** End of the prevention for mulitple definition ******/
#endif