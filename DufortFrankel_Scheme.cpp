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
DufortFrankel_Scheme::DufortFrankel_Scheme(const ProblemDefinition& problem)
    : Scheme(problem.Get_dx(), problem.Get_N(), problem.Get_dt(), problem.Get_D()) // use of the Scheme class
{
    this->dx = this->Get_dx();
    this->L = problem.Get_thickness();
    this->dt = this->Get_dt();
    this->tMax = problem.Get_tMax();
    this->N = this->Get_N();
    this->D = this->Get_D();
    this->T_in = problem.Get_Tin();
    this->T_sur = problem.Get_Tsur();
    this->r = this->Get_CFL();
}

vector<vector<double>> DufortFrankel_Scheme::dfSolution() {
    // solution matrix with a size compose of time_index and space_index
    vector<vector<double>> solution(this->N, vector<double>(this->N, 0.0)); 
    
    // vectors to store the different T
    vector<double> T_prev(this->N); // T_n-1
    vector<double> T_curr(this->N); // T_n
    vector<double> T_next(this->N); // T_n+1

    // Boundary conditions
    T_curr[0] = this->T_sur;
    T_curr[N-1] = this->T_sur;

    // Initialisation of T_curr   
    for(int i=1; i<this->N-1; i++) {
        T_curr[i] = this->T_in;
    }

    // Storage of the initial condition
    solution[0] = T_curr;

    // Initialisation of T_prev
    T_prev = solution[0];

    // Creation of the first time_step
    //ProblemDefinition initialisation(0.31, this->dx, this->tMax, this->dt, this->N, this->T_in, this->T_sur, this->D);
    //vector<vector<double>> analytic = initialisation.Analytic_Solution(); // use of the analytical soluton
    //T_curr = analytic[1];

    // Storage of the first time step
    //solution[1] = T_curr;

    // Loop to obtain all the other time steps
    for (int t=1; t<this->N; t++) { // time steps
        // loop to obtain the result for each x
        for (int i=1; i<this->N-1; i++) { // grid steps
            T_next[i] = ((1-2*this->r)/(1+2*r)) * T_prev[i] + (2*this->r/(1+2*this->r)) * (T_curr[i-1] + T_curr[i+1]);
        }

        // Storage of the current step
        solution[t] = T_next;

        // Update of the T_xxx
        T_prev = T_curr;
        T_curr = T_next;

        // boundary conditions
        T_next[0] = T_sur;
        T_next[N-1] = T_sur;
    }

    return solution;
}