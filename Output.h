/*  Computational Methods Assignment
    @author :       John Hoarau, Clémence-Philomène Hinot
    @date :         16/10/2025
    @file :         Output.h
    @description:   ...
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
class Output
{
    private:
        string filename;

    public:
        // default class contructor
        Output();

        // class constructor with parameters
        Output(string filename);

        // methods to get attributes
        string Get_filename() const;

        // methods to set attributes
        void Set_filename(string value_filename);

        // method to generate an output file
        void Generate_File(const vector<vector<double>>& solution, string methodName, double dx, double dt, double tMax, int N);

        // method to visualise the solution
        void Generate_Diagram(const vector<vector<double>>& solution, string methodName, double dx, double dt, double tMax, int N);
};

/****** End of the prevention for mulitple definition ******/
#endif