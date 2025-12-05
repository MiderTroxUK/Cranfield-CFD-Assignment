/*  Computational Methods Assignment
    @author :       John Hoarau, Clémence-Philomène Hinot
    @date :         16/10/2025
    @file :         Output.h
*/

/****** Prevention for mulitple definition ******/
#ifndef OUTPUT_H
#define OUTPUT_H

/****** Libraries and other inclusions ******/
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/****** Declaration of class Output ******/
/**
 * @class Output
 * @brief Handles data export and visualization.
 * 
 * This class provides methods to export simulation results to CSV files and generate plots using Gnuplot.
 */
class Output
{
    private:
        string filename; ///< Base filename for output

    public:
        /**
         * @brief Default constructor.
         */
        Output();

        /**
         * @brief Parameterized constructor.
         * @param filename Base filename for output
         */
        Output(string filename);

        // Getters
        string Get_filename() const;    ///< Get filename

        // Setters
        void Set_filename(string value_filename);   ///< Set filename

        /**
         * @brief Generates a CSV file containing the simulation results.
         * 
         * The file format is compatible with Gnuplot and other plotting tools.
         * It includes columns for position and temperature at selected time steps.
         * 
         * @param solution The 2D vector containing the solution [space][time]
         * @param methodName The name of the numerical method (used for filename)
         * @param dx Spatial grid spacing
         * @param dt Time step size
         * @param tMax Maximum simulation time
         * @param N Number of time steps
         */
        void Generate_File(const vector<vector<double>>& solution, string methodName, double dx, double dt, double tMax, int N);

        /**
         * @brief Generates a plot of the solution using Gnuplot.
         * 
         * This method pipes commands to a Gnuplot process to visualize the temperature profiles.
         * 
         * @param solution The 2D vector containing the solution [space][time]
         * @param methodName The name of the numerical method (used for plot title)
         * @param dx Spatial grid spacing
         * @param dt Time step size
         * @param tMax Maximum simulation time
         * @param N Number of time steps
         */
        void Generate_Diagram(const vector<vector<double>>& solution, string methodName, double dx, double dt, double tMax, int N);
};

/****** End of the prevention for mulitple definition ******/
#endif