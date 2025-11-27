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

/****** Methods prototypes ******/
void Visualisation(const std::vector<std::vector<double>>& solution, string methodName, double dx, double dt, double tMax, double L, int N);

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
    } */

    // debug for Visualisation Method
    /*Visualisation(solution, "AnalyticSolution", dx, dt, tMax, L, N);*/

    // Proper way to finish main()
    return 0;
}

/****** Visualisation Method ******/

void Visualisation(const std::vector<std::vector<double>>& solution, string methodName, double dx, double dt, double tMax, double L, int N) {
    // ------ Initialisation ------
    
    // calculate x coordinates
    vector<double> x_coordinates(N);
    for (int i=0; i<N; i++) {
        x_coordinates[i] = i * dx;
    }

    // get time indices
    vector<int> indices;
    vector<double> required_times = {0.0, 0.1, 0.2, 0.3, 0.4, 0.5}; // these are the required times specified in the Assignement
    int index = 0;
    for (double t : required_times) { // for all the t in the range required_times
        if (t <= 0.5) {
            index = static_cast<int>(round(t / dt));
            indices.push_back(index);
        }
    }

    // ------ Data exportation ------

    // export the solution to a gnuplot format
    string dataFilename = methodName + ".dat";
    ofstream file(dataFilename);
    if (!file.is_open()) {
        cout << "Error: Cannot open file " << dataFilename << endl;
        return;
    }

    // header
    file << "# x(cm)  ";
    for (double t : required_times) {
        file << "T(t=" << t << ")  ";
    }
    file << "\n";
    
    // data rows
    int size_x = solution.size();
    for (int i = 0; i < size_x; i++) {
        file << x_coordinates[i] << "  ";
        for (int idx : indices) {
            file << solution[i][idx] << "  ";
        }
        file << "\n";
    }

    file.close();
    cout << "Gnuplot data exported to " << dataFilename << endl;

    // ------ Gnuplot visualisation ------

    string scriptFilename = methodName + ".gp";
    ofstream script(scriptFilename);

    if (!script.is_open()) {
        cout << "Error: Cannot create gnuplot script " << scriptFilename << endl;
        return;
    }

    // gnuplot script
    script << "# Gnuplot script for temperature distribution\n";
    script << "set terminal png size 1200,800\n";
    script << "set output '" << methodName << ".png'\n";
    script << "set title '" << methodName << "'\n";
    script << "set xlabel 'Position x (cm)'\n";
    script << "set ylabel 'Temperature (°C)'\n";
    script << "set grid\n";
    script << "set key outside right\n\n";


    // Plot command
    script << "plot ";
    for (size_t i = 0; i < indices.size(); i++) {
        if (i > 0) script << ", \\\n     ";
        
        int col = i + 2;  // Column 1 is x, columns 2+ are temperatures
        double time_val = required_times[i];
        
        script << "'" << dataFilename << "' using 1:" << col 
               << " with linespoints title 't=" << time_val << " hrs'";
    }
    script << "\n";
    
    script.close();
    
    cout << "Gnuplot script created: " << scriptFilename << endl;
    
    
    // ------ Execute Gnuplot ------

    string command = "gnuplot " + scriptFilename;
    int result = system(command.c_str());
    if (result != 0) {
        cout << "Error: Gnuplot execution failed." << endl;
    } else { 
        cout << "Plot generated successfully: " << methodName << ".png" << endl;
    }

}