#include "Laasonen_Scheme.h"
#include "CrankNicholson_Scheme.h"
#include "DufortFrankel_Scheme.h"
#include "Richardson_Scheme.h"
#include "Verification.h"
#include "Output.h"

/****** Libraries and other inclusions ******/
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

/****** Main function ******/
/**
 * @brief Main entry point of the application.
 * @return 0 on successful execution.
 */
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

    // Laasonen
    Laasonen_Scheme laasonen(wallProblem);
    vector<vector<double>> laasonenSolution = laasonen.Solve(); // Now this works!

    // Crank-Nicholson
    CrankNicholson_Scheme crankNicholson(wallProblem);
    vector<vector<double>> crankNicholsonSolution = crankNicholson.Solve();

    // Dufort-Frankel
    DufortFrankel_Scheme dufortFrankel(wallProblem);
    vector<vector<double>> duforFrankelSolution = dufortFrankel.dfSolution(laasonenSolution);

    // Richardson
    Richardson_Scheme richardson(wallProblem);
    vector<vector<double>> richardsonSolution = richardson.richardsonSolution(laasonenSolution);

    /****** .csv file & diagram ******/
    Output visualisation;

    // Analytical Solutions
    visualisation.Generate_File(analyticSolution, "AnalyticSolution", dx, dt, tMax, N);
    visualisation.Generate_Diagram(analyticSolution, "AnalyticSolution", dx, dt, tMax, N);

    // Laasonen
    visualisation.Generate_File(laasonenSolution, "Laasonen", dx, dt, tMax, N);
    visualisation.Generate_Diagram(laasonenSolution, "Laasonen", dx, dt, tMax, N);

    // Crank-Nicholson
    visualisation.Generate_File(crankNicholsonSolution, "CrankNicholson", dx, dt, tMax, N);
    visualisation.Generate_Diagram(crankNicholsonSolution, "CrankNicholson", dx, dt, tMax, N);

    // Dufort-Frankel
    visualisation.Generate_File(duforFrankelSolution, "DufortFrankel", dx, dt, tMax, N);
    visualisation.Generate_Diagram(duforFrankelSolution, "DufortFrankel", dx, dt, tMax, N);

    // Richardson
    visualisation.Generate_File(richardsonSolution, "Richardson", dx, dt, tMax, N);
    visualisation.Generate_Diagram(richardsonSolution, "Richardson", dx, dt, tMax, N);

    /****** Verification ******/
    Verification verif;
    int time_index = N; // Index for t = tMax
    int space_points = analyticSolution.size();

    // Helper to extract column
    auto extract_column = [&](const vector<vector<double>>& sol) {
        vector<double> col(space_points);
        for(int i=0; i<space_points; ++i) {
            if (static_cast<size_t>(time_index) < sol[i].size())
                col[i] = sol[i][time_index];
            else
                col[i] = 0.0; 
        }
        return col;
    };

    vector<double> T_analytic = extract_column(analyticSolution);

    cout << "\n--- Verification Results (t = " << tMax << ") ---\n";

    // Dufort-Frankel
    vector<double> T_df = extract_column(duforFrankelSolution);
    double norm_df = verif.Calculation_Norm(T_df, T_analytic);
    cout << "Dufort-Frankel L2 Norm: " << norm_df << endl;
    verif.Verify_Stability(dufortFrankel.Get_CFL(), norm_df, "DufortFrankel");

    // Richardson
    vector<double> T_rich = extract_column(richardsonSolution);
    double norm_rich = verif.Calculation_Norm(T_rich, T_analytic);
    cout << "Richardson L2 Norm: " << norm_rich << endl;
    verif.Verify_Stability(richardson.Get_CFL(), norm_rich, "Richardson");

    // Laasonen
    vector<double> T_laas = extract_column(laasonenSolution);
    double norm_laas = verif.Calculation_Norm(T_laas, T_analytic);
    cout << "Laasonen L2 Norm: " << norm_laas << endl;
    verif.Verify_Stability(laasonen.Get_CFL(), norm_laas, "Laasonen");

    // Crank-Nicholson
    vector<double> T_cn = extract_column(crankNicholsonSolution);
    double norm_cn = verif.Calculation_Norm(T_cn, T_analytic);
    cout << "Crank-Nicholson L2 Norm: " << norm_cn << endl;
    verif.Verify_Stability(crankNicholson.Get_CFL(), norm_cn, "CrankNicholson");

    // Proper way to finish main()
    return 0;
}