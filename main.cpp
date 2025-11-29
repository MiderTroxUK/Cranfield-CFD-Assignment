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
#include <fstream>
#include <cmath>
using namespace std;

/****** Main function ******/
int main() 
{
    /****** Problem Parameters ******/

    // Temperatures
    double Tin = 38.0; // initial uniform temperature
    double Tsur = 149.0; // surface temperature (on the two sides) suddenly increased an maintained

    // Diffusivity of the material
    double D = 93.0; // 93 cm^2/h

    // Wall parameters
    double L = 31.0; // thickness in cm

    // Space griding
    double dx = 0.05; // cm

    // Time gridind
    double dt = 0.01; // Be careful, in step 3 w will have to investigate the step size with 0.01, 0.025, 0.05, and 0.1
    double tMax = 0.5;

    // Number of steps
    int N = tMax / dt;

    /****** Schemes ******/

    // Analytical Solution
    ProblemDefinition wallProblem(L, dx, tMax, dt, N, Tin, Tsur, D);
    vector<vector<double>> analyticSolution = wallProblem.Analytic_Solution();

    // Dufort-Frankel
    DufortFrankel_Scheme dufortFrankel(wallProblem);
    //dufortFrankel.dfSolution();

    // Richardson
    Richardson_Scheme richardson(wallProblem);
    //richardson.richardsonSolution();

    // Laasonen
    Laasonen_Scheme laasonen(wallProblem);

    // Crank-Nicholson
    CrankNicholson_Scheme crankNicholson(wallProblem);

    /****** .csv file & diagram ******/
    Output visualisation;

    // Analytical Solutions
    visualisation.Generate_File(analyticSolution, "AnalyticSolution", dx, dt, tMax, N);
    visualisation.Generate_Diagram(analyticSolution, "AnalyticSolution", dx, dt, tMax, N);

    // Dufort-Frankel

    // Richardson

    // Laasonen

    // Crank-Nicholson

    // Proper way to finish main()
    return 0;
}