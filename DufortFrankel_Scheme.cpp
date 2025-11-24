/*  Computational Methods Assignment
    @author :       John Hoarau, Clémence-Philomène Hinot
    @date :         16/10/2025
    @file :         DufortFrankel_Scheme.cpp
    @description:   ...
*/

/******* Inclusion of classes ******/
#include "DufortFrankel_Scheme.h"

/****** Libraries and other inclusions ******/
#include <cmath>
#include <vector>
using namespace std;
#include "ProblemDefinition.h"

/****** Methods for class DufortFrankel_Scheme ******/

// default class contructor
DufortFrankel_Scheme::DufortFrankel_Scheme()
{
    // TO DO
}

// class constructor with parameters
// to do
DufortFrankel_Scheme::DufortFrankel_Scheme(double dx, double dt, double t_max, int N, double D, double T_in, double T_sur) {
    // CFL number
    double r = D * dt / pow(dx, 2);
    
    // vectors to store the different T
    vector<double> T_prev(N); // T_n-1
    vector<double> T_curr(N); // T_n
    vector<double> T_next(N); // T_n+1

    // Initialisation of T_prev
    T_curr[0] = T_sur;
    T_curr[N-1] = T_sur;
    for(int i=1; i<N-1; i++) {
        T_curr[i] = T_in;
    }
    T_prev = T_curr;

    // Initilisation of T_curr
    ProblemDefinition initialisation(0, 0.31, dx, t_max, dt, N, T_in, T_sur, D);
    vector<vector<double>> analytic = initialisation.Analytic_Solution();
    for (int i=0; i<N; i++) {
        T_curr[i] = analytic[1][i];
    }

    // Boundary conditions
    T_next[0] = T_sur;
    T_next[N-1] = T_sur;

    // Loop
    double ct = 0.0;
    while (ct < t_max) {
        // calculation of the next step
        for (int i=1; i<N-1; i++) {
            T_next[i] = ((1-2*r)/(1+2*r)) * T_prev[i] + (2*r/(1+2*r)) * (T_curr[i-1] + T_curr[i+1]);
        }
        // storage of the solutions
        T_prev = T_curr;
        T_curr = T_next;
        // update of the counder
        ct += dt;
    }
}