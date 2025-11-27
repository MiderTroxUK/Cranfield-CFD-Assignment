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
#include <iostream>
#include <vector>
using namespace std;

/****** Declaration of class Richardson_Scheme ******/

class Richardson_Scheme : public Scheme
{
    private:
        // TO DO if it's necessary
    public:
        // class constructor with parameter
        Richardson_Scheme(double dx, double dt, double t_max, int N, double D, double T_in, double T_sur);

        // methods
        vector<vector<double>> richardsonSolution(double dx, double dt, double t_max, int N, double D, double T_in, double T_sur);
};

/****** End of the prevention for mulitple definition ******/
#endif