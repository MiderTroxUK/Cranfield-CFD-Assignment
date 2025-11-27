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
#include <iostream>
#include <vector>
using namespace std;

/****** Declaration of class DufortFrankel_Scheme ******/

class DufortFrankel_Scheme : public Scheme
{
    private:
        // TO DO if it's necessary
    public:
        // class constructor with parameter
        DufortFrankel_Scheme(double dx, double dt, double t_max, int N, double D, double T_in, double T_sur);

        // methods
        vector<vector<double>> dfSolution(double dx, double dt, double t_max, int N, double D, double T_in, double T_sur);
};

/****** End of the prevention for mulitple definition ******/
#endif