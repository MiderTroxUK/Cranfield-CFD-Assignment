/*  Computational Methods Assignment
    @author :       Clémence-Philomène Hinot
    @date :         27/11/2025
    @file :         DufortFrankel_Scheme.cpp
    @description:   ...
*/

/******* Inclusion of classes ******/
#include "DufortFrankel_Scheme.h"
#include "ProblemDefinition.h"

/****** Libraries and other inclusions ******/
#include <cmath>
#include <vector>
using namespace std;

/****** Methods for class DufortFrankel_Scheme ******/

// class constructor with parameters
// to do
DufortFrankel_Scheme::DufortFrankel_Scheme(double dx, double dt, double t_max, int N, double D, double T_in, double T_sur)
    : Scheme(dx, N, dt, D) // use of the Scheme class
{
    // no additional initialization needed
}

vector<vector<double>> DufortFrankel_Scheme::dfSolution(double dx, double dt, double t_max, int N, double D, double T_in, double T_sur) {
    // size of the solution matric
    int num_time_steps = static_cast<int>(t_max / dt) + 1;
    
    // solution matrix with a size compose of time_index and space_index
    vector<vector<double>> solution(num_time_steps, vector<double>(N, 0.0));
    
    // CFL number
    double r = this->Get_CFL();
    
    // vectors to store the different T
    vector<double> T_prev(N); // T_n-1
    vector<double> T_curr(N); // T_n
    vector<double> T_next(N); // T_n+1

    // Boundary conditions
    T_curr[0] = T_sur;
    T_curr[N-1] = T_sur;
    T_next[0] = T_sur;
    T_next[N-1] = T_sur;

    // Initialisation of T_curr   
    for(int i=1; i<N-1; i++) {
        T_curr[i] = T_in;
    }

    // Storage of the initial condition
    solution[0] = T_curr;

    // Initialisation of T_prev
    T_prev = solution[0];

    // Creation of the first time_step
    ProblemDefinition initialisation(0, 0.31, dx, t_max, dt, N, T_in, T_sur, D);
    vector<vector<double>> analytic = initialisation.Analytic_Solution(); // use of the analytical soluton
    T_curr = analytic[1];

    // Storage of the first time step
    solution[1] = T_curr;

    // Loop to obtain all the other time steps
    for (int t=2; t<num_time_steps; t++) { // time steps
        // loop to obtain the result for each x
        for (int i=1; i<N-1; i++) { // grid steps
            T_next[i] = ((1-2*r)/(1+2*r)) * T_prev[i] + (2*r/(1+2*r)) * (T_curr[i-1] + T_curr[i+1]);
        }

        // Storage of the current step
        solution[t] = T_next;

        // Update of the T_xxx
        T_prev = T_curr;
        T_curr = T_next;
    }

    return solution;
}