/*  Computational Methods Assignment
    @author :       John Hoarau, Clémence-Philomène Hinot
    @date :         16/10/2025
    @file :         Output.cpp
    @description:   ...
*/

/******* Inclusion of classes ******/
#include "Output.h"

/****** Libraries and other inclusions ******/
#include <string>
#include <vector>
#include <fstream>
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
}

// method to visualise the solution
void Generate_Diagram(const vector<vector<double>>& solution, string methodName, double dx, double dt, double tMax, int N) {
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
        
        script << "'" << methodName << "' using 1:" << col 
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