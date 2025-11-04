/*  Computational Methods Assignment
    @author :       John Hoarau, Clémence-Philomène Hinot
    @date :         16/10/2025
    @file :         main.cpp
    @description:   ...
*/

/******* Inclusion of classes ******/
#include "ProblemDefinition.h"
#include "Scheme.h"
#include "DufortFrankel_Scheme.h"
#include "Richardson_Scheme.h"
#include "Laasonen_Scheme.h"
#include "CrankNicholson_Scheme.h"
#include "Verification.h"
#include "Output.h"

/****** Libraries and other inclusions ******/
#include <iostream>
using namespace std;

/****** Main function ******/
int main() 
{
    // TO DO

    /*** DEBUG ***/

    // debug for ProblemDefinition class
    /*cout << "debug | Declaration of the object wallProblem" << endl;
    double Tin = 38.0;
    double Tsur = 149.0;
    double D = 155e-6;
    double L = 0.31;
    double xMin = 0.0;
    double dx = 0.05;
    double tMax = 0.1;
    double dt = 0.01;
    int N = 100;
    ProblemDefinition wallProblem(xMin, L, dx, tMax, dt, N, Tin, Tsur, D);
    cout << "debug | Storage of the analytic solution" << endl;
    vector<vector<double>> solution = wallProblem.Analytic_Solution();
    int size_x = static_cast<int>(wallProblem.Get_thickness() / wallProblem.Get_dx()) + 1;
    int size_t = static_cast<int>(wallProblem.Get_tMax() / wallProblem.Get_dt()) + 1;
    for(int i=0; i<size_x; i++) {
        for(int j=0; j<size_t; j++) {
            cout << "debug | analytic solution (index i = " << i << ", index j = " << j << "): " << solution[i][j] << endl;
        }
    }*/

    // Proper way to finish main()
    return 0;
}