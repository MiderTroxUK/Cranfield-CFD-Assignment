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

    double tMax = 0.5;

    // Fourier Number 
    int N = 100;

    // List of time steps to test
    vector<double> dt_values = {0.1, 0.05, 0.025, 0.01};

    cout << "\n================================================================" << endl;
    cout << "   STARTING MULTI-DT SIMULATION SERIES" << endl;
    cout << "   dt values: 0.1, 0.05, 0.025, 0.01" << endl;
    cout << "================================================================" << endl;

    /****** Main Loop over dt ******/
    for (double dt : dt_values) {
        
        cout << "\n################################################################" << endl;
        cout << "   RUNNING SIMULATION WITH dt = " << dt << " (N = " << N << ")" << endl;
        cout << "################################################################" << endl;

        /****** Schemes ******/

        // Analytical Solution
        ProblemDefinition wallProblem(L, dx, tMax, dt, N, Tin, Tsur, D);
        vector<vector<double>> analyticSolution = wallProblem.Analytic_Solution();

        // Laasonen
        Laasonen_Scheme laasonen(wallProblem);
        vector<vector<double>> laasonenSolution = laasonen.Solve(); 

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
        // Note: Files will be overwritten (feature, not bug, for this check)

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
        int space_points = analyticSolution.size();
        
        // Safety check for maximum available time index
        int max_time_idx = 0;
        if (space_points > 0) {
            max_time_idx = analyticSolution[0].size() - 1;
        }

        double tolerance = 0.05; // 5% Relative Error Tolerance
        vector<double> check_times = {0.0, 0.1, 0.2, 0.3, 0.4, 0.5};

        cout << "\n   >>> VERIFICATION for dt = " << dt << " <<<" << endl;

        for (double current_t : check_times) {
            
            // Calculate index: round(t / dt)
            int time_index = (int)round(current_t / dt);

            cout << "\n   --- Time t = " << current_t << " (Index: " << time_index << ") ---" << endl;

            if (time_index > max_time_idx) {
                cout << "   WARNING: Time index " << time_index << " exceeds available data (" << max_time_idx << "). Skipping." << endl;
                continue;
            }

            // Helper to extract column for CURRENT time_index
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

            // Helper to print results
            auto verify_and_print = [&](const vector<double>& T_num, string name) {
                double l2_norm = verif.Calculation_L2_Norm(T_num, T_analytic, dx);
                double rel_error = verif.Calculation_Relative_Error(T_num, T_analytic, dx);
                
                cout << "   [" << name << "]" << endl;
                
                if (std::isnan(rel_error) || std::isinf(rel_error))
                     cout << "      -> Relative Error: INF/NaN" << endl;
                else if (rel_error < 0)
                     cout << "      -> Relative Error: Error (Analytic Norm=0)" << endl;
                else
                     cout << "      -> Relative Error: " << (rel_error * 100.0) << " %" << endl;

                bool stable = verif.Verify_Stability(rel_error, tolerance);

                if (stable) {
                    cout << "      -> Status: STABLE" << endl;
                } else {
                    if (std::isnan(rel_error) || std::isinf(rel_error)) {
                        cout << "      -> Status: UNSTABLE (Exploded)" << endl;
                    } else if (rel_error < 0) {
                        cout << "      -> Status: UNDEFINED" << endl;
                    } else {
                        cout << "      -> Status: UNSTABLE/INACCURATE" << endl;
                    }
                }
            };

            // Dufort-Frankel
            verify_and_print(extract_column(duforFrankelSolution), "Dufort-Frankel");

            // Richardson
            verify_and_print(extract_column(richardsonSolution), "Richardson");

            // Laasonen
            verify_and_print(extract_column(laasonenSolution), "Laasonen");

            // Crank-Nicholson
            verify_and_print(extract_column(crankNicholsonSolution), "Crank-Nicholson");
        }
    }

    // Proper way to finish main()
    return 0;
}