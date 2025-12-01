/*  Computational Methods Assignment
    @author :       Clémence-Philomène Hinot
    @date :         16/10/2025
    @file :         Richardson_Scheme.cpp
    @description:   ...
*/

/******* Inclusion of classes ******/
#include "Richardson_Scheme.h"
#include "ProblemDefinition.h"

/****** Libraries and other inclusions ******/
#include <vector>
#include <cmath>
using namespace std;

/****** Methods for class Richardson_Scheme ******/

// class constructor with parameters
Richardson_Scheme::Richardson_Scheme(const ProblemDefinition& problem)
: Scheme(problem.Get_dx(), problem.Get_N(), problem.Get_dt(), problem.Get_D()), problem(problem) // use the class "Scheme" and store the problem
{
    // CFL number
    this->r = this->Get_CFL();
}

// methods
vector<vector<double>> Richardson_Scheme::richardsonSolution(vector<vector<double>> laasonen) {
    // size of the solution matric
    int num_time_steps = static_cast<int>(this->problem.Get_tMax() / this->problem.Get_dt()) + 1;
    int num_space_points = static_cast<int>(this->problem.Get_thickness() / this->problem.Get_dx()) +1;
    
    // solution matrix with a size compose of time_index and space_index
    vector<vector<double>> solution(num_space_points, vector<double>(num_time_steps, 0.0));
    
    // vectors to store the different T
    vector<double> T_prev(num_space_points); // T_n-1
    vector<double> T_curr(num_space_points); // T_n
    vector<double> T_next(num_space_points); // T_n+1

    // Boundary conditions
    T_curr[0] = this->problem.Get_Tsur();
    T_curr[num_space_points-1] = this->problem.Get_Tsur();

    // Initialisation of T_curr   
    for(int i=1; i<num_space_points-1; i++) {
        T_curr[i] = this->problem.Get_Tin();
    }

    // Storage of the initial condition
    for(int i=0; i<num_space_points; i++) {
        solution[i][0] = T_curr[i];
    }

    // Initialisation of T_prev
    T_prev = T_curr;

    // Creation of the first time_step
    for(int i=0; i<num_space_points; i++) {
        T_curr[i] = laasonen[i][1];
        solution[i][1] = T_curr[i];
    }

    // Loop to obtain all the other time steps
    for (int t=2; t<num_time_steps; t++) { // time steps
        // loop to obtain the result for each x
        for (int i=1; i<num_space_points-1; i++) { // grid steps
            T_next[i] = T_prev[i] + 2.0 * this->r * (T_curr[i+1] - 2.0 * T_curr[i] + T_curr[i-1]);
        }

        // Storage of the current step
        for(int i=0; i<num_space_points; i++) {
            solution[i][t] = T_next[i];
        }

        // Update of the T_xxx
        T_prev = T_curr;
        T_curr = T_next;
    }

    return solution;
}