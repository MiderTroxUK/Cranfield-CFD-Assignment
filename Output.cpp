/*  Computational Methods Assignment
    @author :       Clémence-Philomène Hinot & Copilot
    @date :         16/10/2025
    @file :         Output.cpp
*/

/******* Inclusion of classes ******/
#include "Output.h"

/****** Libraries and other inclusions ******/
#include <cstdio> // for popen and pclose so use the gnuplot
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

/****** Methods for class ProblemDefinition ******/

// default class contructor
Output::Output()
{
    this->filename = "";
}

// class constructor with parameters
Output::Output(string filename)
{
    this->filename = filename;
}

// methods to get attributes
string Output::Get_filename() const
{
    return this->filename;
}

// methods to set attributes
void Output::Set_filename(string value_filename)
{
    this->filename = filename;
}

// method to generate an output file
void Output::Generate_File(const vector<vector<double>>& solution, string methodName, double dx, double dt, double tMax, int N)
{
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
    string dataFilename = methodName + ".csv";
    ofstream file(dataFilename);
    if (!file.is_open()) {
        cout << "Error: Cannot open file " << dataFilename << endl;
        return;
    }

    // header
    file << "x(cm)  ";
    for (double t : required_times) {
        file << "," << "T(t=" << t << ") ";
    }
    file << "\n";
    
    // data rows
    int size_x = solution.size();
    for (int i = 0; i < size_x; i++) {
        file << x_coordinates[i] << "  ";
        for (int idx : indices) {
            file << "," << solution[i][idx];
        }
        file << "\n";
    }

    file.close();
    cout << "Gnuplot data exported to " << dataFilename << endl;
}

// method to visualise the solution
void Output::Generate_Diagram(const vector<vector<double>>& solution, string methodName, double dx, double dt, double tMax, int N) {
    // ------ Initialisation ------
    
    int size_x_coord = solution.size();
    int size_t_coord = solution[0].size();

    vector<double> required_times = {0.0, 0.1, 0.2, 0.3, 0.4, 0.5}; // these are the required times specified in the Assignement

    // ------ Gnuplot script ------

    
    FILE* gp = popen("gnuplot -persistent", "w");
    if (!gp) {
        std::cerr << "Error: gnuplot is not available.\n";
        return;
    }

    // Gnuplot settings
    fprintf(gp, "set title '%s'\n", methodName.c_str());
    fprintf(gp, "set xlabel 'Position x (cm)'\n");
    fprintf(gp, "set ylabel 'Temperature (°C)'\n");
    fprintf(gp, "set grid\n");
    fprintf(gp, "set key outside right\n");
    fprintf(gp, "plot ");

    
    // Plot commands for each time curve
    for (size_t i = 0; i < required_times.size(); i++) {
        if (i > 0) fprintf(gp, ", ");
        fprintf(gp, "'-' with lines title 't=%.1f hr'", required_times[i]);
    }
    fprintf(gp, "\n");

    // Send data for each curve
    for (double t : required_times) {
        int idx = static_cast<int>(round(t / dt));
        if (idx >= size_t_coord) continue; // Bounds check
        for (int i = 0; i < size_x_coord; i++) {
            double x = i * dx; // dx in cm
            if (x > 31.0) break; // Stop at 31 cm
            fprintf(gp, "%f %f\n", x, solution[i][idx]);
        }
        fprintf(gp, "e\n");
    }

    pclose(gp);
    std::cout << "Analytical solution plot generated successfully.\n";
}