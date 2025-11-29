/*  Computational Methods Assignment
    @author :       Clémence-Philomène Hinot
    @date :         25/11/2025
    @file :         DufortFrankel_Scheme.h
    @description:   ...
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

class DufortFrankel_Scheme : public Scheme
{
    private:
        double r = 0.0; // CFL number
        ProblemDefinition problem;
    public:
        // class constructor with parameter
        DufortFrankel_Scheme(const ProblemDefinition& problem);

        // methods
        vector<vector<double>> dfSolution();
};

/****** End of the prevention for mulitple definition ******/
#endif